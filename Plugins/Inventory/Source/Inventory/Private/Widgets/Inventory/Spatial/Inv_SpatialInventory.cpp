#include "Widgets/Inventory/Spatial/Inv_SpatialInventory.h"
#include "Inventory.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"
#include "Widgets/ItemDescription/Inv_ItemDescription.h"
#include "Blueprint/WidgetTree.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Widgets/Inventory/GridSlots/Inv_EquippedGridSlot.h"
#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"
#include "Widgets/Inventory/SlottedItems/Inv_EquippedSlottedItem.h"

void UInv_SpatialInventory::NativeOnInitialized()
{
	Super::OnInitialized();

	this->Button_Equippables->OnClicked.AddDynamic(this, &ThisClass::ShowEquippables);
	this->Button_Consumables->OnClicked.AddDynamic(this, &ThisClass::ShowConsumables);
	this->Button_Craftables->OnClicked.AddDynamic(this, &ThisClass::ShowCraftables);
	
	this->Grid_Equippables->SetOwningCanvasPanel(this->CanvasPanel);
	this->Grid_Consumables->SetOwningCanvasPanel(this->CanvasPanel);
	this->Grid_Craftables->SetOwningCanvasPanel(this->CanvasPanel);
	
	this->ShowEquippables();
	
	WidgetTree->ForEachWidget([this](UWidget* Widget)
	{
		if (UInv_EquippedGridSlot* Slot = Cast<UInv_EquippedGridSlot>(Widget); IsValid(Slot))
		{
			this->EquippedGridSlots.Add(Slot);
			Slot->EquippedSlotClicked.AddDynamic(this, &ThisClass::EquippedSlotClicked);
		}
	});
}

FInv_SlotAvailabilityResult UInv_SpatialInventory::HasRoomForItem(UInv_ItemComponent* Component) const
{
	switch (UInv_InventoryStatics::GetItemCategoryByItemComponent(Component))
	{
	case EInv_ItemCategory::Equippable:
		return this->Grid_Equippables->HasRoomForItem(Component);
	case EInv_ItemCategory::Consumable:
		return this->Grid_Consumables->HasRoomForItem(Component);
	case EInv_ItemCategory::Craftable:
		return this->Grid_Craftables->HasRoomForItem(Component);
	default:
		UE_LOG(LogInventory, Error, TEXT("Item Component does not have a valid Item Category"));
		return FInv_SlotAvailabilityResult();
	}
}

FReply UInv_SpatialInventory::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->ActiveGrid->DropItem();
	
	return FReply::Handled();
}

void UInv_SpatialInventory::OnItemHovered(UInv_InventoryItem* Item)
{
	const FInv_ItemManifest& Manifest = Item->GetItemManifest();
	UInv_ItemDescription* DescriptionWidget = this->GetItemDescription();
	DescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(this->DescriptionTimerHandle);
	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, &Manifest, DescriptionWidget]()
	{
		Manifest.AssimilateInventoryFragments(DescriptionWidget);
		this->GetItemDescription()->SetVisibility(ESlateVisibility::HitTestInvisible);
	});
	GetOwningPlayer()->GetWorldTimerManager().SetTimer(this->DescriptionTimerHandle, TimerDelegate, this->DescriptionTimerDelay, false);
}

void UInv_SpatialInventory::OnItemUnhovered()
{
	this->GetItemDescription()->SetVisibility(ESlateVisibility::Collapsed);
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(this->DescriptionTimerHandle);
}

bool UInv_SpatialInventory::HasHoverItem() const
{
	if (this->Grid_Equippables->HasHoverItem()) return true;
	if (this->Grid_Consumables->HasHoverItem()) return true;
	if (this->Grid_Craftables->HasHoverItem()) return true;
	
	return false;
}

void UInv_SpatialInventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!IsValid(this->ItemDescriptionWidget)) return;
	
	this->SetItemDescrptionSizeAndPosition(this->ItemDescriptionWidget, this->CanvasPanel);
}

UInv_HoverItem* UInv_SpatialInventory::GetHoverItem() const
{
	if (!this->ActiveGrid.IsValid()) return nullptr;
	
	return this->ActiveGrid->GetHoverItem();
}

float UInv_SpatialInventory::GetTileSize() const
{
	return this->Grid_Equippables->GetTileSize();
}

void UInv_SpatialInventory::ShowEquippables()
{
	this->SetActiveGrid(this->Grid_Equippables, this->Button_Equippables);
}

void UInv_SpatialInventory::ShowConsumables()
{
	this->SetActiveGrid(this->Grid_Consumables, this->Button_Consumables);
}

void UInv_SpatialInventory::ShowCraftables()
{
	this->SetActiveGrid(this->Grid_Craftables, this->Button_Craftables);
}

void UInv_SpatialInventory::EquippedSlotClicked(UInv_EquippedGridSlot* GridSlot, const FGameplayTag& EquipmentTypeTag)
{
	if (!this->CanEquipHoverItem(GridSlot, EquipmentTypeTag)) return;
	
	const float TileSize = this->Grid_Equippables->GetTileSize();
	UInv_HoverItem* HoverItem = this->GetHoverItem();
	UInv_EquippedSlottedItem* EquippedSlottedItem = GridSlot->OnItemEquipped(HoverItem->GetInventoryItem(), EquipmentTypeTag, TileSize);
	EquippedSlottedItem->OnItemClicked.AddDynamic(this, &UInv_SpatialInventory::EquippedSlottedItemClicked);
	
	this->Grid_Equippables->ClearHoverItem();
	
	UInv_InventoryComponent* InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	check(IsValid(InventoryComponent));
	
	InventoryComponent->Server_EquippedSlotClicked(HoverItem->GetInventoryItem(), nullptr);
}

void UInv_SpatialInventory::EquippedSlottedItemClicked(UInv_EquippedSlottedItem* SlottedItem)
{
	UInv_InventoryStatics::ItemUnhovered(GetOwningPlayer());
	
	if (IsValid(this->GetHoverItem()) && this->GetHoverItem()->IsStackable()) return;
	
	UInv_InventoryItem* ItemToEquip = IsValid(this->GetHoverItem()) ? this->GetHoverItem()->GetInventoryItem() : nullptr;
	UInv_InventoryItem* ItemToUnequip = SlottedItem->GetInventoryItem();
	
	UInv_EquippedGridSlot* GridSlot = this->FindSlotWithEquippedItem(ItemToUnequip);
	this->ClearSlotOfItem(GridSlot);
	this->RemoveEquippedSlottedItem(SlottedItem);
	this->Grid_Equippables->AssignHoverItem(ItemToUnequip);
	
	this->MakeEquippedSlottedItem(SlottedItem, GridSlot, ItemToEquip);
	this->BroadcastSlotClickedDelegates(ItemToEquip, ItemToUnequip);
}

void UInv_SpatialInventory::SetActiveGrid(UInv_InventoryGrid* Grid, UButton* Button)
{
	if (this->ActiveGrid.IsValid())
	{
		this->ActiveGrid->HideMouseCursor();
		this->ActiveGrid->OnHide();
	}
	this->ActiveGrid = Grid;
	if (this->ActiveGrid.IsValid()) this->ActiveGrid->ShowMouseCursor();
	
	this->DisableButton(Button);
	this->Switcher->SetActiveWidget(Grid);
}

void UInv_SpatialInventory::DisableButton(UButton* Button) const
{
	this->Button_Equippables->SetIsEnabled(true);
	this->Button_Consumables->SetIsEnabled(true);
	this->Button_Craftables->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

UInv_ItemDescription* UInv_SpatialInventory::GetItemDescription()
{
	if (!IsValid(this->ItemDescriptionWidget))
	{
		this->ItemDescriptionWidget = CreateWidget<UInv_ItemDescription>(this, this->ItemDescriptionClass);
		this->CanvasPanel->AddChild(this->ItemDescriptionWidget);
	}
	
	return this->ItemDescriptionWidget;
}

void UInv_SpatialInventory::SetItemDescrptionSizeAndPosition(UInv_ItemDescription* ItemDescription, UCanvasPanel* Canvas) const
{
	UCanvasPanelSlot* DescriptionSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this->ItemDescriptionWidget);
	if (!IsValid(DescriptionSlot)) return;
	
	const FVector2D Size = this->ItemDescriptionWidget->GetBoxSize();
	DescriptionSlot->SetSize(Size);
	
	FVector2D ClampedPos = UInv_WidgetUtils::GetClampedWidgetPosition(UInv_WidgetUtils::GetWidgetSize(Canvas), Size, UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer()));
	DescriptionSlot->SetPosition(ClampedPos);
}

bool UInv_SpatialInventory::CanEquipHoverItem(UInv_EquippedGridSlot* GridSlot, const FGameplayTag& EquipmentTypeTag) const
{
	if (!IsValid(GridSlot) || GridSlot->GetInventoryItem().IsValid()) return false;
	
	UInv_HoverItem* HoverItem = this->GetHoverItem();
	if (!IsValid(HoverItem)) return false;
	
	UInv_InventoryItem* HeldItem = HoverItem->GetInventoryItem();
	
	return this->HasHoverItem() && IsValid(HeldItem) && !HoverItem->IsStackable() 
	       && HeldItem->GetItemManifest().GetItemCategory() == EInv_ItemCategory::Equippable 
		   && HeldItem->GetItemManifest().GetItemType().MatchesTag(EquipmentTypeTag);
}

UInv_EquippedGridSlot* UInv_SpatialInventory::FindSlotWithEquippedItem(UInv_InventoryItem* EquippedItem) const
{
	const TObjectPtr<UInv_EquippedGridSlot>* FoundEquippedGridSlot = this->EquippedGridSlots.FindByPredicate([EquippedItem](const UInv_EquippedGridSlot* GridSlot)
	{
		return GridSlot->GetInventoryItem() == EquippedItem;
	});
	return FoundEquippedGridSlot ? *FoundEquippedGridSlot : nullptr;
}

void UInv_SpatialInventory::ClearSlotOfItem(UInv_EquippedGridSlot* GridSlot) const
{
	if (IsValid(GridSlot))
	{
		GridSlot->SetEquippedSlottedItem(nullptr);
		GridSlot->SetInventoryItem(nullptr);
	}
}

void UInv_SpatialInventory::RemoveEquippedSlottedItem(UInv_EquippedSlottedItem* Item)
{
	if (!IsValid(Item)) return;
	
	if (Item->OnItemClicked.IsAlreadyBound(this, &UInv_SpatialInventory::EquippedSlottedItemClicked))
	{
		Item->OnItemClicked.RemoveDynamic(this, &UInv_SpatialInventory::EquippedSlottedItemClicked);
	}
	Item->RemoveFromParent();
}

void UInv_SpatialInventory::MakeEquippedSlottedItem(UInv_EquippedSlottedItem* Item, UInv_EquippedGridSlot* GridSlot, UInv_InventoryItem* ItemToEquip)
{
	if (!IsValid(GridSlot)) return;
	
	UInv_EquippedSlottedItem* SlottedItem = GridSlot->OnItemEquipped(ItemToEquip, Item->GetEquipmentTypeTag(), this->Grid_Equippables->GetTileSize());
	if (IsValid(SlottedItem)) SlottedItem->OnItemClicked.AddDynamic(this, &UInv_SpatialInventory::EquippedSlottedItemClicked);
	GridSlot->SetEquippedSlottedItem(SlottedItem);
}

void UInv_SpatialInventory::BroadcastSlotClickedDelegates(UInv_InventoryItem* ItemToEquip, UInv_InventoryItem* ItemToUnequip) const
{
	UInv_InventoryComponent* IC = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	check(IsValid(IC));
	
	IC->Server_EquippedSlotClicked(ItemToEquip, ItemToUnequip);
	
	if (GetOwningPlayer()->GetNetMode() != ENetMode::NM_DedicatedServer)
	{
		IC->OnItemEquipped.Broadcast(ItemToEquip);
		IC->OnItemUnequipped.Broadcast(ItemToUnequip);
	}
}

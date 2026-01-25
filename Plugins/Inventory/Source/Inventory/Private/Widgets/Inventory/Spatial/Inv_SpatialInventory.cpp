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
#include "Items/Fragments/Inv_ItemFragment.h"
#include "Widgets/Inventory/GridSlots/Inv_EquippedGridSlot.h"
#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"
#include "Widgets/Inventory/SlottedItems/Inv_EquippedSlottedItem.h"

// initialize the spatial inventory (the one that contains the sub grids)
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

// checking room for item based of the type of requesting item component
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

// defer item dropping to the active grid
FReply UInv_SpatialInventory::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->ActiveGrid->DropItem();
	
	return FReply::Handled();
}

// show item description popup
void UInv_SpatialInventory::OnItemHovered(UInv_InventoryItem* Item)
{
	const FInv_ItemManifest& Manifest = Item->GetItemManifest();
	UInv_ItemDescription* DescriptionWidget = this->GetItemDescription();
	DescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(this->DescriptionTimerHandle);
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(this->EquippedDescriptionTimerHandle);
	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, Item, &Manifest, DescriptionWidget]()
	{
		this->GetItemDescription()->SetVisibility(ESlateVisibility::HitTestInvisible);
		Manifest.AssimilateInventoryFragments(DescriptionWidget);
		
		FTimerDelegate EquippedTimerDelegate;
		EquippedTimerDelegate.BindUObject(this, &UInv_SpatialInventory::ShowEquippedItemDescription, Item);
		GetOwningPlayer()->GetWorldTimerManager().SetTimer(this->EquippedDescriptionTimerHandle, EquippedTimerDelegate, this->EquippedDescriptionTimerDelay, false);
	});
	GetOwningPlayer()->GetWorldTimerManager().SetTimer(this->DescriptionTimerHandle, TimerDelegate, this->DescriptionTimerDelay, false);
}

// remove item description popup
void UInv_SpatialInventory::OnItemUnhovered()
{
	this->GetItemDescription()->SetVisibility(ESlateVisibility::Collapsed);
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(this->DescriptionTimerHandle);
	
	this->GetEquippedItemDescription()->SetVisibility(ESlateVisibility::Collapsed);
	GetOwningPlayer()->GetWorldTimerManager().ClearTimer(this->EquippedDescriptionTimerHandle);
}

// defer the check of hover item to the active grid
bool UInv_SpatialInventory::HasHoverItem() const
{
	if (this->Grid_Equippables->HasHoverItem()) return true;
	if (this->Grid_Consumables->HasHoverItem()) return true;
	if (this->Grid_Craftables->HasHoverItem()) return true;
	
	return false;
}

// update position of description popups when moving mouse
void UInv_SpatialInventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!IsValid(this->ItemDescriptionWidget)) return;
	
	this->SetItemDescrptionSizeAndPosition(this->ItemDescriptionWidget, this->CanvasPanel);
	this->SetEquippedItemDescrptionSizeAndPosition(this->ItemDescriptionWidget, this->EquippedItemDescriptionWidget, this->CanvasPanel);
}

// get the hover item from the active grid
UInv_HoverItem* UInv_SpatialInventory::GetHoverItem() const
{
	if (!this->ActiveGrid.IsValid()) return nullptr;
	
	return this->ActiveGrid->GetHoverItem();
}

// get the tilesize of the active grid
float UInv_SpatialInventory::GetTileSize() const
{
	return this->Grid_Equippables->GetTileSize();
}

// show equippables grid
void UInv_SpatialInventory::ShowEquippables()
{
	this->SetActiveGrid(this->Grid_Equippables, this->Button_Equippables);
}

// show consumables grid
void UInv_SpatialInventory::ShowConsumables()
{
	this->SetActiveGrid(this->Grid_Consumables, this->Button_Consumables);
}

// show craftables grid
void UInv_SpatialInventory::ShowCraftables()
{
	this->SetActiveGrid(this->Grid_Craftables, this->Button_Craftables);
}

// handle clicking on empty equipping slot
void UInv_SpatialInventory::EquippedSlotClicked(UInv_EquippedGridSlot* GridSlot, const FGameplayTag& EquipmentTypeTag)
{
	if (!this->CanEquipHoverItem(GridSlot, EquipmentTypeTag)) return;
	
	const float TileSize = this->Grid_Equippables->GetTileSize();
	UInv_HoverItem* HoverItem = this->GetHoverItem();
	UInv_EquippedSlottedItem* EquippedSlottedItem = GridSlot->OnItemEquipped(HoverItem->GetInventoryItem(), EquipmentTypeTag, TileSize);
	EquippedSlottedItem->OnItemClicked.AddDynamic(this, &UInv_SpatialInventory::EquippedSlottedItemClicked);
	
	UInv_InventoryComponent* InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	check(IsValid(InventoryComponent));
	
	InventoryComponent->Server_EquippedSlotClicked(HoverItem->GetInventoryItem(), nullptr);
	
	this->Grid_Equippables->ClearHoverItem();
}

// handle clicking on an already equipped slot
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

// show item description for equipped item
void UInv_SpatialInventory::ShowEquippedItemDescription(UInv_InventoryItem* Item)
{
	const FInv_ItemManifest& Manifest = Item->GetItemManifest();
	const FInv_EquipmentFragment* EquipmentFragment = Manifest.GetFragmentByType<FInv_EquipmentFragment>();
	if (!EquipmentFragment) return;
	
	const FGameplayTag HoveredEquipmentType = EquipmentFragment->GetEquipmentType();
	TObjectPtr<UInv_EquippedGridSlot>* EquippedGridSlot = this->EquippedGridSlots.FindByPredicate([Item](const UInv_EquippedGridSlot* GridSlot)
	{
		return GridSlot->GetInventoryItem() == Item;
	});
	
	if (EquippedGridSlot != nullptr) return; // Hovered item is already equipped
	
	TObjectPtr<UInv_EquippedGridSlot>* FoundEquippedGridSlot = this->EquippedGridSlots.FindByPredicate([HoveredEquipmentType](const UInv_EquippedGridSlot* GridSlot)
	{
		UInv_InventoryItem* InventoryItem = GridSlot->GetInventoryItem().Get();
		return IsValid(InventoryItem) ? InventoryItem->GetItemManifest().GetFragmentByType<FInv_EquipmentFragment>()->GetEquipmentType() == HoveredEquipmentType : false;
	});
	UInv_EquippedGridSlot* EquippedSlot = FoundEquippedGridSlot ? *FoundEquippedGridSlot : nullptr;
	if (!IsValid(EquippedSlot)) return;
	
	UInv_InventoryItem* EquippedItem = EquippedSlot->GetInventoryItem().Get();
	if (!IsValid(EquippedItem)) return;
	
	const FInv_ItemManifest& EquippedItemManifest = EquippedItem->GetItemManifest();
	UInv_ItemDescription* DescriptionWidget = this->GetEquippedItemDescription();
	UInv_ItemDescription* EquippedDescriptionWidget = this->GetEquippedItemDescription();
	EquippedDescriptionWidget->Collapse();
	DescriptionWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	EquippedItemManifest.AssimilateInventoryFragments(EquippedDescriptionWidget);
}

// set the active grid
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

// disable button of active grid
void UInv_SpatialInventory::DisableButton(UButton* Button) const
{
	this->Button_Equippables->SetIsEnabled(true);
	this->Button_Consumables->SetIsEnabled(true);
	this->Button_Craftables->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

// get item descripton widget
UInv_ItemDescription* UInv_SpatialInventory::GetItemDescription()
{
	if (!IsValid(this->ItemDescriptionWidget))
	{
		this->ItemDescriptionWidget = CreateWidget<UInv_ItemDescription>(this, this->ItemDescriptionClass);
		this->CanvasPanel->AddChild(this->ItemDescriptionWidget);
	}
	
	return this->ItemDescriptionWidget;
}

// get equipped item description widget
UInv_ItemDescription* UInv_SpatialInventory::GetEquippedItemDescription()
{
	if (!IsValid(this->EquippedItemDescriptionWidget))
	{
		this->EquippedItemDescriptionWidget = CreateWidget<UInv_ItemDescription>(this, this->EquippedItemDescriptionClass);
		this->CanvasPanel->AddChild(this->EquippedItemDescriptionWidget);
	}
	
	return this->EquippedItemDescriptionWidget;
}

// place popup on screen
void UInv_SpatialInventory::SetItemDescrptionSizeAndPosition(UInv_ItemDescription* ItemDescription, UCanvasPanel* Canvas) const
{
	UCanvasPanelSlot* DescriptionSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemDescription);
	if (!IsValid(DescriptionSlot)) return;
	
	const FVector2D Size = ItemDescription->GetBoxSize();
	DescriptionSlot->SetSize(Size);
	
	FVector2D ClampedPos = UInv_WidgetUtils::GetClampedWidgetPosition(UInv_WidgetUtils::GetWidgetSize(Canvas), Size, UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer()));
	DescriptionSlot->SetPosition(ClampedPos);
}

// place popup on screen
void UInv_SpatialInventory::SetEquippedItemDescrptionSizeAndPosition(UInv_ItemDescription* ItemDescription, UInv_ItemDescription* EquippedItemDescription, UCanvasPanel* Canvas) const
{
	UCanvasPanelSlot* DescriptionSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemDescription);
	UCanvasPanelSlot* EquippedDescriptionSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(EquippedItemDescription);
	if (!IsValid(DescriptionSlot) || !IsValid(EquippedDescriptionSlot)) return;
	
	const FVector2D Size = ItemDescription->GetBoxSize();
	const FVector2D EquippedSize = EquippedItemDescription->GetBoxSize();
	FVector2D ClampedPos = UInv_WidgetUtils::GetClampedWidgetPosition(UInv_WidgetUtils::GetWidgetSize(Canvas), Size, UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer()));
	ClampedPos.X -= EquippedSize.X;
	
	EquippedDescriptionSlot->SetPosition(ClampedPos);
	EquippedDescriptionSlot->SetSize(EquippedSize);
}

// check if the current hovered item can be equipped
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

// find the equipped slot for given item
UInv_EquippedGridSlot* UInv_SpatialInventory::FindSlotWithEquippedItem(UInv_InventoryItem* EquippedItem) const
{
	const TObjectPtr<UInv_EquippedGridSlot>* FoundEquippedGridSlot = this->EquippedGridSlots.FindByPredicate([EquippedItem](const UInv_EquippedGridSlot* GridSlot)
	{
		return GridSlot->GetInventoryItem() == EquippedItem;
	});
	return FoundEquippedGridSlot ? *FoundEquippedGridSlot : nullptr;
}

// empty equipped slot
void UInv_SpatialInventory::ClearSlotOfItem(UInv_EquippedGridSlot* GridSlot) const
{
	if (IsValid(GridSlot))
	{
		GridSlot->SetEquippedSlottedItem(nullptr);
		GridSlot->SetInventoryItem(nullptr);
	}
}

// remove item from equipped grid slot
void UInv_SpatialInventory::RemoveEquippedSlottedItem(UInv_EquippedSlottedItem* Item)
{
	if (!IsValid(Item)) return;
	
	if (Item->OnItemClicked.IsAlreadyBound(this, &UInv_SpatialInventory::EquippedSlottedItemClicked))
	{
		Item->OnItemClicked.RemoveDynamic(this, &UInv_SpatialInventory::EquippedSlottedItemClicked);
	}
	Item->RemoveFromParent();
}

// equip an item
void UInv_SpatialInventory::MakeEquippedSlottedItem(UInv_EquippedSlottedItem* Item, UInv_EquippedGridSlot* GridSlot, UInv_InventoryItem* ItemToEquip)
{
	if (!IsValid(GridSlot)) return;
	
	UInv_EquippedSlottedItem* SlottedItem = GridSlot->OnItemEquipped(ItemToEquip, Item->GetEquipmentTypeTag(), this->Grid_Equippables->GetTileSize());
	if (IsValid(SlottedItem)) SlottedItem->OnItemClicked.AddDynamic(this, &UInv_SpatialInventory::EquippedSlottedItemClicked);
	GridSlot->SetEquippedSlottedItem(SlottedItem);
}

// ask server to broadcast the item switch, multiplayer only
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
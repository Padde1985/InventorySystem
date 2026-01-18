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

void UInv_SpatialInventory::SetActiveGrid(UInv_InventoryGrid* Grid, UButton* Button)
{
	if (this->ActiveGrid.IsValid()) this->ActiveGrid->HideMouseCursor();
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

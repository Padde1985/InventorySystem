#include "Widgets/Inventory/Spatial/Inv_SpatialInventory.h"

#include "Inventory.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"

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

void UInv_SpatialInventory::DisableButton(UButton* Button)
{
	this->Button_Equippables->SetIsEnabled(true);
	this->Button_Consumables->SetIsEnabled(true);
	this->Button_Craftables->SetIsEnabled(true);
	Button->SetIsEnabled(false);
}

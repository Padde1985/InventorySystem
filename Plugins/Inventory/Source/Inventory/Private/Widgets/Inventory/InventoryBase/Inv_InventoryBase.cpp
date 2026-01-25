#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"

// placeholder for checking on slot availability
FInv_SlotAvailabilityResult UInv_InventoryBase::HasRoomForItem(UInv_ItemComponent* Component) const
{
	return FInv_SlotAvailabilityResult();
}

// placeholder for hover callback
void UInv_InventoryBase::OnItemHovered(UInv_InventoryItem* Item)
{
}

// placeholder for item unhovering
void UInv_InventoryBase::OnItemUnhovered()
{
}

// placeholder for checking if hover item is set
bool UInv_InventoryBase::HasHoverItem() const
{
	return false;
}

// placeholder for retrieving the hover item
UInv_HoverItem* UInv_InventoryBase::GetHoverItem() const
{
	return nullptr;
}

// placeholder for getting tile size (not the grid size)
float UInv_InventoryBase::GetTileSize() const
{
	return 0.f;
}
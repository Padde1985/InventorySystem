#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"

FInv_SlotAvailabilityResult UInv_InventoryBase::HasRoomForItem(UInv_ItemComponent* Component) const
{
	return FInv_SlotAvailabilityResult();
}

void UInv_InventoryBase::OnItemHovered(UInv_InventoryItem* Item)
{
}

void UInv_InventoryBase::OnItemUnhovered()
{
}

bool UInv_InventoryBase::HasHoverItem() const
{
	return false;
}

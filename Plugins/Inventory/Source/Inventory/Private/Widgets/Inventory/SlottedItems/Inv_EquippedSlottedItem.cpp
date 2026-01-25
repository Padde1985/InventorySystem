#include "Widgets/Inventory/SlottedItems/Inv_EquippedSlottedItem.h"

// set equipment type tag
void UInv_EquippedSlottedItem::SetEquipmentTypeTag(const FGameplayTag& Tag)
{
	this->EquipmentTypeTag = Tag;
}

// getter for equipment type tag
FGameplayTag UInv_EquippedSlottedItem::GetEquipmentTypeTag() const
{
	return this->EquipmentTypeTag;
}

// handle mouse click (left and right click)
FReply UInv_EquippedSlottedItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->OnItemClicked.Broadcast(this);
	
	return FReply::Handled();
}
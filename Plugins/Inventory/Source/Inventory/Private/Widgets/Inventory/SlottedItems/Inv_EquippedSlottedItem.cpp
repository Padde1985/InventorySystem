#include "Widgets/Inventory/SlottedItems/Inv_EquippedSlottedItem.h"

void UInv_EquippedSlottedItem::SetEquipmentTypeTag(const FGameplayTag& Tag)
{
	this->EquipmentTypeTag = Tag;
}

FGameplayTag UInv_EquippedSlottedItem::GetEquipmentTypeTag() const
{
	return this->EquipmentTypeTag;
}

FReply UInv_EquippedSlottedItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->OnItemClicked.Broadcast(this);
	
	return FReply::Handled();
}

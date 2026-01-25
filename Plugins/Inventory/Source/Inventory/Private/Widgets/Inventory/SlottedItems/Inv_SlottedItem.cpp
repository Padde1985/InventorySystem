#include "Widgets/Inventory/SlottedItems/Inv_SlottedItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"

// setter for stackable parameter
void UInv_SlottedItem::SetIsStackable(bool bStackable)
{
	this->bIsStackable = bStackable;
}

// getter for stackable parameter
bool UInv_SlottedItem::GetIsStackable() const
{
	return this->bIsStackable;
}

// set the image for the slotted item
void UInv_SlottedItem::SetImageBrush(const FSlateBrush& Brush) const
{
	this->Image_Icon->SetBrush(Brush);
}

// get the actual image icon
UImage* UInv_SlottedItem::GetImageIcon()
{
	return this->Image_Icon;
}

// set the grid index for the slotted item
void UInv_SlottedItem::SetGridIndex(int32 Index)
{
	this->GridIndex = Index;
}

// get the grid index
int32 UInv_SlottedItem::GetGridIndex() const
{
	return this->GridIndex;
}

// set the grid dimensions
void UInv_SlottedItem::SetGridDimensions(const FIntPoint& Dimensions)
{
	this->GridDimensions = Dimensions;
}

// getter for grid dimensions
FIntPoint UInv_SlottedItem::GetGridDimensions() const
{
	return this->GridDimensions;
}

// set inventory item
void UInv_SlottedItem::SetInventoryItem(UInv_InventoryItem* Item)
{
	this->InventoryItem = Item;
}

// get the inventory item
UInv_InventoryItem* UInv_SlottedItem::GetInventoryItem() const
{
	return this->InventoryItem.Get();
}

// set the stack count and show or hide the stack count on the item
void UInv_SlottedItem::UpdateStackCount(int32 StackCount) const
{
	if (StackCount > 0)
	{
		this->Text_StackCount->SetVisibility(ESlateVisibility::Visible);
		this->Text_StackCount->SetText(FText::AsNumber(StackCount));
	}
	else
	{
		this->Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

// handle mouse button click
FReply UInv_SlottedItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->OnSlottedItemClicked.Broadcast(this->GridIndex, InMouseEvent);
	
	return FReply::Handled();
}

// callback for hovering the item
void UInv_SlottedItem::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UInv_InventoryStatics::ItemHovered(GetOwningPlayer(), this->InventoryItem.Get());
}

// callback for unhovering an item
void UInv_SlottedItem::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	UInv_InventoryStatics::ItemUnhovered(GetOwningPlayer());
}
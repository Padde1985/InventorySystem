#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/Inv_InventoryItem.h"

// set image brush for the hover item (turns into mouse cursor)
void UInv_HoverItem::SetImageBrush(const FSlateBrush& Brush) const
{
	this->Image_Icon->SetBrush(Brush);
}

// update stackcount for hover item
void UInv_HoverItem::UpdateStackCount(int32 Count)
{
	this->StackCount = Count;
	
	if (Count > 0)
	{
		this->Text_StackCount->SetText(FText::AsNumber(Count));
		this->Text_StackCount->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		this->Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

// getter for item type
FGameplayTag UInv_HoverItem::GetItemType() const
{
	if (this->InventoryItem.IsValid())
	{
		return this->InventoryItem->GetItemManifest().GetItemType();
	}
	
	return FGameplayTag();
}

// getter for stackcount
int32 UInv_HoverItem::GetStackCount() const
{
	return this->StackCount;
}

// check if item is stackable
bool UInv_HoverItem::IsStackable() const
{
	return this->bIsStackable;
}

// setter for stackable parameter
void UInv_HoverItem::SetIsStackable(bool bStacks)
{
	this->bIsStackable = bStacks;
	if (!this->bIsStackable)
	{
		this->Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

// getter for previous grid index (in case hovering gets canceled and item has to be placed back into inventory)
int32 UInv_HoverItem::GetPreviousGridIndex() const
{
	return this->PreviousGridIndex;
}

// store previous grid prosition
void UInv_HoverItem::SetPreviousGridIndex(int32 Index)
{
	this->PreviousGridIndex = Index;
}

// getter for grid dimensions
FIntPoint UInv_HoverItem::GetGridDimension() const
{
	return this->GridDimensions;
}

// setter for grid dimensions
void UInv_HoverItem::SetGridDimensions(const FIntPoint& Dimension)
{
	this->GridDimensions = Dimension;
}

// getter for inventory item
UInv_InventoryItem* UInv_HoverItem::GetInventoryItem() const
{
	return this->InventoryItem.Get();
}

// setter for inventory item
void UInv_HoverItem::SetInventoryItem(UInv_InventoryItem* Item)
{
	this->InventoryItem = Item;
}
#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/Inv_InventoryItem.h"

void UInv_HoverItem::SetImageBrush(const FSlateBrush& Brush) const
{
	this->Image_Icon->SetBrush(Brush);
}

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

FGameplayTag UInv_HoverItem::GetItemType() const
{
	if (this->InventoryItem.IsValid())
	{
		return this->InventoryItem->GetItemManifest().GetItemType();
	}
	
	return FGameplayTag();
}

int32 UInv_HoverItem::GetStackCount() const
{
	return this->StackCount;
}

bool UInv_HoverItem::IsStackable() const
{
	return this->bIsStackable;
}

void UInv_HoverItem::SetIsStackable(bool bStacks)
{
	this->bIsStackable = bStacks;
	if (!this->bIsStackable)
	{
		this->Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

int32 UInv_HoverItem::GetPreviousGridIndex() const
{
	return this->PreviousGridIndex;
}

void UInv_HoverItem::SetPreviousGridIndex(int32 Index)
{
	this->PreviousGridIndex = Index;
}

FIntPoint UInv_HoverItem::GetGridDimension() const
{
	return this->GridDimensions;
}

void UInv_HoverItem::SetGridDimensions(const FIntPoint& Dimension)
{
	this->GridDimensions = Dimension;
}

UInv_InventoryItem* UInv_HoverItem::GetInventoryItem() const
{
	return this->InventoryItem.Get();
}

void UInv_HoverItem::SetInventoryItem(UInv_InventoryItem* Item)
{
	this->InventoryItem = Item;
}

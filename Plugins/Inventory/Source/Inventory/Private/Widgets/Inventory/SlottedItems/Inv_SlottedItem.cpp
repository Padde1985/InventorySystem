#include "Widgets/Inventory/SlottedItems/Inv_SlottedItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"

void UInv_SlottedItem::SetIsStackable(bool bStackable)
{
	this->bIsStackable = bStackable;
}

bool UInv_SlottedItem::GetIsStackable() const
{
	return this->bIsStackable;
}

void UInv_SlottedItem::SetImageBrush(const FSlateBrush& Brush) const
{
	this->Image_Icon->SetBrush(Brush);
}

UImage* UInv_SlottedItem::GetImageIcon()
{
	return this->Image_Icon;
}

void UInv_SlottedItem::SetGridIndex(int32 Index)
{
	this->GridIndex = Index;
}

int32 UInv_SlottedItem::GetGridIndex() const
{
	return this->GridIndex;
}

void UInv_SlottedItem::SetGridDimensions(const FIntPoint& Dimensions)
{
	this->GridDimensions = Dimensions;
}

FIntPoint UInv_SlottedItem::GetGridDimensions() const
{
	return this->GridDimensions;
}

void UInv_SlottedItem::SetInventoryItem(UInv_InventoryItem* Item)
{
	this->InventoryItem = Item;
}

UInv_InventoryItem* UInv_SlottedItem::GetInventoryItem() const
{
	return this->InventoryItem.Get();
}

void UInv_SlottedItem::UpdateStackCount(int32 StackCount)
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

FReply UInv_SlottedItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->OnSlottedItemClicked.Broadcast(this->GridIndex, InMouseEvent);
	
	return FReply::Handled();
}

void UInv_SlottedItem::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UInv_InventoryStatics::ItemHovered(GetOwningPlayer(), this->InventoryItem.Get());
}

void UInv_SlottedItem::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	UInv_InventoryStatics::ItemUnhovered(GetOwningPlayer());
}

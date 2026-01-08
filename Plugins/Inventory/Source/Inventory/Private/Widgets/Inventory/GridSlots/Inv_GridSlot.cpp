#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Components/Image.h"
#include "Items/Inv_InventoryItem.h"

void UInv_GridSlot::SetTileIndex(int32 InTileIndex)
{
	this->TileIndex = InTileIndex;
}

int32 UInv_GridSlot::GetTileIndex() const
{
	return this->TileIndex;
}

EInv_GridSlotState UInv_GridSlot::GetSlotState() const
{
	return this->State;
}

void UInv_GridSlot::SetUnoccupiedTexture()
{
	this->State = EInv_GridSlotState::Unoccupied;
	this->Image_GridSlot->SetBrush(this->Brush_Unoccupied);
}

void UInv_GridSlot::SetOccupiedTexture()
{
	this->State = EInv_GridSlotState::Occupied;
	this->Image_GridSlot->SetBrush(this->Brush_Occupied);
}

void UInv_GridSlot::SetSelectedTexture()
{
	this->State = EInv_GridSlotState::Selected;
	this->Image_GridSlot->SetBrush(this->Brush_Selected);
}

void UInv_GridSlot::SetGrayedOutTexture()
{
	this->State = EInv_GridSlotState::GrayedOut;
	this->Image_GridSlot->SetBrush(this->Brush_GrayedOut);
}

TWeakObjectPtr<UInv_InventoryItem> UInv_GridSlot::GetInventoryItem() const
{
	return this->InventoryItem;
}

void UInv_GridSlot::SetInventoryItem(UInv_InventoryItem* Item)
{
	this->InventoryItem = Item;
}

int32 UInv_GridSlot::GetStackCount() const
{
	return this->StackCount;
}

void UInv_GridSlot::SetStackCount(int32 InStackCount)
{
	this->StackCount = InStackCount;
}

int32 UInv_GridSlot::GetUpperLeftIndex() const
{
	return this->UpperLeftIndex;
}

void UInv_GridSlot::SetUpperLeftIndex(int32 InUpperLeftIndex)
{
	this->UpperLeftIndex = InUpperLeftIndex;
}

bool UInv_GridSlot::GetAvailable() const
{
	return this->bAvailable;
}

void UInv_GridSlot::SetAvailable(bool InAvailable)
{
	this->bAvailable = InAvailable;
}

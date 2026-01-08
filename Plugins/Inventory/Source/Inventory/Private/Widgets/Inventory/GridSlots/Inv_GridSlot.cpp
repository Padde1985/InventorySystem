#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Components/Image.h"

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

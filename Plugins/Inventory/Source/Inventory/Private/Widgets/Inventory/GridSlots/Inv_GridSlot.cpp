#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Components/Image.h"
#include "Items/Inv_InventoryItem.h"
#include "Widgets/ItemPopup/Inv_ItemPopup.h"

// setter for tile index (combination of row and column)
void UInv_GridSlot::SetTileIndex(int32 InTileIndex)
{
	this->TileIndex = InTileIndex;
}

// getter for tile index
int32 UInv_GridSlot::GetTileIndex() const
{
	return this->TileIndex;
}

// getter for slot state (available or blocked)
EInv_GridSlotState UInv_GridSlot::GetSlotState() const
{
	return this->State;
}

// set background image for available slots
void UInv_GridSlot::SetUnoccupiedTexture()
{
	this->State = EInv_GridSlotState::Unoccupied;
	this->Image_GridSlot->SetBrush(this->Brush_Unoccupied);
}

// set background image for blocked slots
void UInv_GridSlot::SetOccupiedTexture()
{
	this->State = EInv_GridSlotState::Occupied;
	this->Image_GridSlot->SetBrush(this->Brush_Occupied);
}

// set background image for a selected item (clicked item)
void UInv_GridSlot::SetSelectedTexture()
{
	this->State = EInv_GridSlotState::Selected;
	this->Image_GridSlot->SetBrush(this->Brush_Selected);
}

// set background image for grayed out items (overlapping when moving the hover item)
void UInv_GridSlot::SetGrayedOutTexture()
{
	this->State = EInv_GridSlotState::GrayedOut;
	this->Image_GridSlot->SetBrush(this->Brush_GrayedOut);
}

// getter for inventory item
TWeakObjectPtr<UInv_InventoryItem> UInv_GridSlot::GetInventoryItem() const
{
	return this->InventoryItem;
}

// setter for inventory item
void UInv_GridSlot::SetInventoryItem(UInv_InventoryItem* Item)
{
	this->InventoryItem = Item;
}

// get current stack count
int32 UInv_GridSlot::GetStackCount() const
{
	return this->StackCount;
}

// setter for stack count
void UInv_GridSlot::SetStackCount(int32 InStackCount)
{
	this->StackCount = InStackCount;
}

// get upper left index in case of multi slot items, all settings are stored on the upper left index of an item
int32 UInv_GridSlot::GetUpperLeftIndex() const
{
	return this->UpperLeftIndex;
}

// set tile index of rupper left index
void UInv_GridSlot::SetUpperLeftIndex(int32 InUpperLeftIndex)
{
	this->UpperLeftIndex = InUpperLeftIndex;
}

// check if slot is available
bool UInv_GridSlot::GetAvailable() const
{
	return this->bAvailable;
}

// set availability status
void UInv_GridSlot::SetAvailable(bool InAvailable)
{
	this->bAvailable = InAvailable;
}

// callback for hovering the slot
void UInv_GridSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	this->GridSlotHovered.Broadcast(this->TileIndex, InMouseEvent);
}

// callback for unhovering the slot
void UInv_GridSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	this->GridSlotUnhovered.Broadcast(this->TileIndex, InMouseEvent);
}

// callback for clicking on a slot
FReply UInv_GridSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->GridSLotClicked.Broadcast(this->TileIndex, InMouseEvent);
	
	return FReply::Handled();
}

// set item popup with description, image, etc
void UInv_GridSlot::SetItemPopup(UInv_ItemPopup* Popup)
{
	this->ItemPopup = Popup;
	this->ItemPopup->SetGridIndex(this->GetTileIndex());
	this->ItemPopup->OnNativeDestruct.AddUObject(this, &UInv_GridSlot::OnItemPopupDestruct);
}

// getter for item description popup
UInv_ItemPopup* UInv_GridSlot::GetItemPopup() const
{
	return this->ItemPopup.Get();
}

// destroy the item description popup
void UInv_GridSlot::OnItemPopupDestruct(UUserWidget* Menu)
{
	this->ItemPopup.Reset();
}
#include "Widgets/Inventory/GridSlots/Inv_EquippedGridSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Items/Fragments/Inv_FragmentTags.h"
#include "Items/Fragments/Inv_ItemFragment.h"
#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"
#include "Widgets/Inventory/SlottedItems/Inv_EquippedSlottedItem.h"

void UInv_EquippedGridSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!GetAvailable()) return;
	
	UInv_HoverItem* HoverItem  = UInv_InventoryStatics::GetHoverItem(GetOwningPlayer());
	if (!IsValid(HoverItem)) return;
	
	if (HoverItem->GetItemType().MatchesTag(this->EquipmentTypeTag))
	{
		SetOccupiedTexture();
		this->GrayedOutIcon->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInv_EquippedGridSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (!GetAvailable()) return;
	
	UInv_HoverItem* HoverItem  = UInv_InventoryStatics::GetHoverItem(GetOwningPlayer());
	if (!IsValid(HoverItem)) return;
	
	if (HoverItem->GetItemType().MatchesTag(this->EquipmentTypeTag))
	{
		SetUnoccupiedTexture();
		this->GrayedOutIcon->SetVisibility(ESlateVisibility::Visible);
	}
}

FReply UInv_EquippedGridSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->EquippedSlotClicked.Broadcast(this, this->EquipmentTypeTag);
	
	return FReply::Handled();
}

UInv_EquippedSlottedItem* UInv_EquippedGridSlot::OnItemEquipped(UInv_InventoryItem* Item, const FGameplayTag& EquipmentTag, const float TileSize)
{
	if (!EquipmentTag.MatchesTagExact(this->EquipmentTypeTag)) return nullptr;
	
	const FInv_GridFragment* GridFragment = UInv_InventoryStatics::GetFragment<FInv_GridFragment>(Item, FragmentTags::GridFragment);
	if (!GridFragment) return nullptr;
	
	const FIntPoint GridDimensions = GridFragment->GetGridSize();
	const float IconTileWidth = TileSize - GridFragment->GetGridPadding() * 2;
	const FVector2D DrawSize = GridDimensions * IconTileWidth;
	
	this->EquippedSlottedItem = CreateWidget<UInv_EquippedSlottedItem>(GetOwningPlayer(), this->EquippedSlottedItemClass);
	this->EquippedSlottedItem->SetInventoryItem(Item);
	this->EquippedSlottedItem->SetEquipmentTypeTag(EquipmentTag);
	this->EquippedSlottedItem->UpdateStackCount(0);
	SetInventoryItem(Item); // set inventory item on this class (the equipped grid slot)
	
	const FInv_ImageFragment* ImageFragment = UInv_InventoryStatics::GetFragment<FInv_ImageFragment>(Item, FragmentTags::IconFragment);
	if (!ImageFragment) return nullptr;
	
	FSlateBrush Brush;
	Brush.SetResourceObject(ImageFragment->GetIcon());
	Brush.DrawAs = ESlateBrushDrawType::Image;
	Brush.ImageSize = DrawSize;
	this->EquippedSlottedItem->SetImageBrush(Brush);
	this->Overlay->AddChild(this->EquippedSlottedItem);
	
	FGeometry OverlayGeometry = this->Overlay->GetCachedGeometry();
	FVector2f OverlayPos = OverlayGeometry.Position;
	FDeprecateSlateVector2D OverlaySize = OverlayGeometry.Size;
	const float LeftPadding = OverlaySize.X / 2.f - DrawSize.X / 2.f;
	const float TopPadding = OverlaySize.Y / 2.f - DrawSize.Y / 2.f;
	UOverlaySlot* OverlaySlot = UWidgetLayoutLibrary::SlotAsOverlaySlot(this->EquippedSlottedItem);
	OverlaySlot->SetPadding(FMargin(LeftPadding, TopPadding));
	
	return this->EquippedSlottedItem;
}

void UInv_EquippedGridSlot::SetEquippedSlottedItem(UInv_EquippedSlottedItem* Item)
{
	this->EquippedSlottedItem = Item;
}

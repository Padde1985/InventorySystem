#include "Items/Manifest/Inv_ItemManifest.h"
#include "Items/Inv_InventoryItem.h"

EInv_ItemCategory FInv_ItemManifest::GetItemCategory() const
{
	return this->ItemCategory;
}

UInv_InventoryItem* FInv_ItemManifest::Manifest(UObject* NewOuter)
{
	UInv_InventoryItem* Item = NewObject<UInv_InventoryItem>(NewOuter, UInv_InventoryItem::StaticClass());
	Item->SetItemManifest(*this);
	
	return Item;
}

FGameplayTag FInv_ItemManifest::GetItemType() const
{
	return this->ItemType;
}

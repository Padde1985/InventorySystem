#include "Items/Inv_InventoryItem.h"
#include "Items/Fragments/Inv_ItemFragment.h"
#include "Net/UnrealNetwork.h"

// replication of item manifest and stack count, only needed in multiplayer
void UInv_InventoryItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, ItemManifest);
	DOREPLIFETIME(ThisClass, TotalStackCount);
}

// setter for item manifest
void UInv_InventoryItem::SetItemManifest(const FInv_ItemManifest& Manifest)
{
	this->ItemManifest = FInstancedStruct::Make<FInv_ItemManifest>(Manifest);
}

// getter for item manifest
const FInv_ItemManifest& UInv_InventoryItem::GetItemManifest() const
{
	return this->ItemManifest.Get<FInv_ItemManifest>();
}

// getter for editable item manifest
FInv_ItemManifest& UInv_InventoryItem::GetItemManifestMutable()
{
	return this->ItemManifest.GetMutable<FInv_ItemManifest>();
}

// only needed in multiplayer
bool UInv_InventoryItem::IsSupportedForNetworking() const
{
	// enable the item to be added to a replicated subobject list on clients
	return true;
}

// check if item is stackable
bool UInv_InventoryItem::IsStackable() const
{
	const FInv_StackableFragment* Stackable = this->GetItemManifest().GetFragmentByType<FInv_StackableFragment>();
	
	return Stackable != nullptr;
}

// getter for stackcount
int32 UInv_InventoryItem::GetStackCount() const
{
	return this->TotalStackCount;
}

// setter for stack count
void UInv_InventoryItem::SetStackCount(int32 Count)
{
	this->TotalStackCount = Count;
}

// check if item is consumable
bool UInv_InventoryItem::IsConsumable() const
{
	return this->GetItemManifest().GetItemCategory() == EInv_ItemCategory::Consumable;
}
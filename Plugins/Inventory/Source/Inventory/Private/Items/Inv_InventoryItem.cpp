#include "Items/Inv_InventoryItem.h"

#include "Items/Fragments/Inv_ItemFragment.h"
#include "Net/UnrealNetwork.h"

void UInv_InventoryItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, ItemManifest);
	DOREPLIFETIME(ThisClass, TotalStackCount);
}

void UInv_InventoryItem::SetItemManifest(const FInv_ItemManifest& Manifest)
{
	this->ItemManifest = FInstancedStruct::Make<FInv_ItemManifest>(Manifest);
}

const FInv_ItemManifest& UInv_InventoryItem::GetItemManifest() const
{
	return this->ItemManifest.Get<FInv_ItemManifest>();
}

FInv_ItemManifest& UInv_InventoryItem::GetItemManifestMutable()
{
	return this->ItemManifest.GetMutable<FInv_ItemManifest>();
}

bool UInv_InventoryItem::IsSupportedForNetworking() const
{
	// enable the item to be added to a replicated subobject list on clients
	return true;
}

bool UInv_InventoryItem::IsStackable() const
{
	const FInv_StackableFragment* Stackable = this->GetItemManifest().GetFragmentByType<FInv_StackableFragment>();
	
	return Stackable != nullptr;
}

int32 UInv_InventoryItem::GetStackCount() const
{
	return this->TotalStackCount;
}

void UInv_InventoryItem::SetStackCount(int32 Count)
{
	this->TotalStackCount = Count;
}
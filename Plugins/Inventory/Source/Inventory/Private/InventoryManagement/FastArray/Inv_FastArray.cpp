#include "InventoryManagement/FastArray/Inv_FastArray.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"

/*
 * the whole fast array is only needed for multiplayer as is provides functionality for broadcasting from server to client and vice versa
 * Pre replicate, post replicate, etc.
 * For single player a map or TArray would suffice
 */

// get all inventory items 
TArray<UInv_InventoryItem*> FInv_InventoryFastArray::GetInventoryItems() const
{
	TArray<UInv_InventoryItem*> Results;
	Results.Reserve(this->Entries.Num());
	for (const FInv_InventoryEntry& Entry : this->Entries)
	{
		if (!IsValid(Entry.Item)) continue;
		Results.Add(Entry.Item);
	}
	return Results;
}

// broadcast removed items
void FInv_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(this->OwnerComponent);
	if (!IsValid(IC)) return;
	
	for (int32 Index : RemovedIndices)
	{
		IC->OnItemRemoved.Broadcast(this->Entries[Index].Item);
	}
}

// broadcast added items
void FInv_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(this->OwnerComponent);
	if (!IsValid(IC)) return;
	
	for (int32 Index : AddedIndices)
	{
		IC->OnItemAdded.Broadcast(this->Entries[Index].Item);
	}
}

// serializer function
bool FInv_InventoryFastArray::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
{
	return FastArrayDeltaSerialize<FInv_InventoryEntry, FInv_InventoryFastArray>(this->Entries, DeltaParams, *this);
}

// add new item to inventory via item component
UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(const UInv_ItemComponent* ItemComponent)
{
	check(this->OwnerComponent);
	AActor* OwningActor = this->OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(this->OwnerComponent);
	if (!IsValid(IC)) return nullptr;
	
	FInv_InventoryEntry& Entry = this->Entries.AddDefaulted_GetRef();
	Entry.Item = ItemComponent->GetItemManifest().Manifest(OwningActor);
	
	IC->AddRepSubObj(Entry.Item);
	MarkItemDirty(Entry);
	
	return Entry.Item;
}

// add new item to inventory
UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_InventoryItem* Item)
{
	check(this->OwnerComponent);
	AActor* OwningActor = this->OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	
	FInv_InventoryEntry& Entry = this->Entries.AddDefaulted_GetRef();
	Entry.Item = Item;
	
	MarkItemDirty(Entry);
	return Item;
}

// remove entry from inventory
void FInv_InventoryFastArray::RemoveEntry(UInv_InventoryItem* Item)
{
	for (TIndexedContainerIterator EntryIt = this->Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FInv_InventoryEntry& Entry = *EntryIt;
		if (Entry.Item == Item)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
			break;
		}
	}
}

// check if item already exists in array and return the item
UInv_InventoryItem* FInv_InventoryFastArray::FindFirstItemByType(const FGameplayTag& ItemType)
{
	FInv_InventoryEntry* FoundItem = this->Entries.FindByPredicate([ItemType](const FInv_InventoryEntry& Entry)
	{
		return IsValid(Entry.Item) && Entry.Item->GetItemManifest().GetItemType().MatchesTagExact(ItemType);
	});
	
	return FoundItem ? FoundItem->Item : nullptr;
}
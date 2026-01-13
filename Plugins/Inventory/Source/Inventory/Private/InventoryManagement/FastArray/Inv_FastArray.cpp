#include "InventoryManagement/FastArray/Inv_FastArray.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"

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

void FInv_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(this->OwnerComponent);
	if (!IsValid(IC)) return;
	
	for (int32 Index : RemovedIndices)
	{
		IC->OnItemRemoved.Broadcast(this->Entries[Index].Item);
	}
}

void FInv_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(this->OwnerComponent);
	if (!IsValid(IC)) return;
	
	for (int32 Index : AddedIndices)
	{
		IC->OnItemAdded.Broadcast(this->Entries[Index].Item);
	}
}

bool FInv_InventoryFastArray::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
{
	return FastArrayDeltaSerialize<FInv_InventoryEntry, FInv_InventoryFastArray>(this->Entries, DeltaParams, *this);
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_ItemComponent* ItemComponent)
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

UInv_InventoryItem* FInv_InventoryFastArray::FindFirstItemByType(const FGameplayTag& ItemType)
{
	FInv_InventoryEntry* FoundItem = this->Entries.FindByPredicate([ItemType](const FInv_InventoryEntry& Entry)
	{
		return IsValid(Entry.Item) && Entry.Item->GetItemManifest().GetItemType().MatchesTagExact(ItemType);
	});
	
	return FoundItem ? FoundItem->Item : nullptr;
}

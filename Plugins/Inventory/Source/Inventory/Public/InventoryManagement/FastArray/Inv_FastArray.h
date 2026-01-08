#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "Inv_FastArray.generated.h"

class UInv_ItemComponent;
class UInv_InventoryComponent;
class UInv_InventoryItem;

USTRUCT()
struct FInv_InventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
	FInv_InventoryEntry() {}
	
private:
	friend UInv_InventoryComponent;
	friend struct FInv_InventoryFastArray;
	
	UPROPERTY() TObjectPtr<UInv_InventoryItem> Item = nullptr;
};

USTRUCT()
struct FInv_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()
	
	FInv_InventoryFastArray() : OwnerComponent(nullptr) {}
	FInv_InventoryFastArray(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent) {}
	
	TArray<UInv_InventoryItem*> GetInventoryItems() const;
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams);
	UInv_InventoryItem* AddEntry(UInv_ItemComponent* ItemComponent);
	UInv_InventoryItem* AddEntry(UInv_InventoryItem* Item);
	void RemoveEntry(UInv_InventoryItem* Item);

private:
	friend UInv_InventoryComponent;
	
	UPROPERTY(NotReplicated) TObjectPtr<UActorComponent> OwnerComponent;
	UPROPERTY() TArray<FInv_InventoryEntry> Entries;
};

template<>
struct TStructOpsTypeTraits<FInv_InventoryFastArray> : public TStructOpsTypeTraitsBase2<FInv_InventoryFastArray>
{
	enum { WithNetDeltaSerializer = true };
};

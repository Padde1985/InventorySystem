#pragma once

#include "Inv_GridTypes.generated.h"

class UInv_InventoryItem;

UENUM(BlueprintType)
enum class EInv_ItemCategory : uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};

USTRUCT()
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()
	
	FInv_SlotAvailabilityResult() {}
	
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bIsStackable = false;
	int32 TotalRoomToFill = 0.f;
	int32 Remainder = 0.f;
	TArray<FInv_SlotAvailability> SlotAvailabilities;
};

USTRUCT()
struct FInv_SlotAvailability
{
	GENERATED_BODY()
	
	FInv_SlotAvailability() {}
	FInv_SlotAvailability(int32 ItemIndex, int32 Room, bool bHasItem) : Index(ItemIndex), AmountToFill(Room), bItemAtIndex(bHasItem) {}
	
	int32 Index = INDEX_NONE;
	int32 AmountToFill = 0.f;
	bool bItemAtIndex = false;
};

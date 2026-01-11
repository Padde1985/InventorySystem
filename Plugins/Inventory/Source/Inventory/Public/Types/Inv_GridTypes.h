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

UENUM(BlueprintType)
enum class EInv_TileQuadrant : uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	None
};

USTRUCT(BlueprintType)
struct FInv_TileParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory") FIntPoint TileCoordinates {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory") int32 TileIndex = INDEX_NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory") EInv_TileQuadrant TileQuadrant = EInv_TileQuadrant::None;
};

inline bool operator==(const FInv_TileParameters& A, const FInv_TileParameters& B)
{
	return A.TileCoordinates == B.TileCoordinates && A.TileIndex == B.TileIndex && A.TileQuadrant == B.TileQuadrant;
}

USTRUCT()
struct FInv_SpaceQueryResult
{
	GENERATED_BODY()

	bool bHasSpace = false; // True if queried space has no item
	TWeakObjectPtr<UInv_InventoryItem> ValidItem = nullptr; // item that can be swapped
	int32 UpperLeftIndex = INDEX_NONE; // index of thew swappable item
};

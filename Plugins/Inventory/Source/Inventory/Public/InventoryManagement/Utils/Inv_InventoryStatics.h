#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Items/Inv_InventoryItem.h"
#include "Widgets/Utils/Inv_WidgetUtils.h"
#include "Inv_InventoryStatics.generated.h"

class UInv_ItemComponent;
class UInv_InventoryComponent;

UCLASS()
class INVENTORY_API UInv_InventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Inventory") static UInv_InventoryComponent* GetInventoryComponent(const APlayerController* PlayerController);
	UFUNCTION(BlueprintCallable, Category="Inventory") static EInv_ItemCategory GetItemCategoryByItemComponent(UInv_ItemComponent* ItemComponent);
	template <typename FragmentType> static const FragmentType* GetFragment(UInv_InventoryItem* Item, const FGameplayTag& Tag);
	template <typename T, typename FuncT> static void ForEach2D(TArray<T>& Array, int32 Index, const FIntPoint& Range2D, int32 Columns, const FuncT& Func);
};

template <typename FragmentType>
const FragmentType* UInv_InventoryStatics::GetFragment(UInv_InventoryItem* Item, const FGameplayTag& Tag)
{
	if (!IsValid(Item)) return nullptr;
	
	const FInv_ItemManifest& Manifest = Item->GetItemManifest();
	
	return Manifest.GetFragmentByTag<FragmentType>(Tag);
}

template <typename T, typename FuncT>
void UInv_InventoryStatics::ForEach2D(TArray<T>& Array, int32 Index, const FIntPoint& Range2D, int32 Columns, const FuncT& Func)
{
	for (int32 i = 0; i < Range2D.Y; i++)
	{
		for (int32 j = 0; j < Range2D.X; j++)
		{
			const FIntPoint& Coordinates = UInv_WidgetUtils::GetPositionByIndex(Index, Columns) + FIntPoint(j, i);
			const int32 TileIndex = UInv_WidgetUtils::GetIndexByPosition(Coordinates, Columns);
			if (Array.IsValidIndex(TileIndex))
			{
				Func(Array[TileIndex]);
			}
		}
	}
}

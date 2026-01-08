#pragma once

#include "CoreMinimal.h"
#include "Types/Inv_GridTypes.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "Inv_ItemManifest.generated.h"

struct FInv_ItemFragment;
class UInv_InventoryItem;

USTRUCT(BlueprintType)
struct INVENTORY_API FInv_ItemManifest
{
	GENERATED_BODY()
	
	EInv_ItemCategory GetItemCategory() const;
	UInv_InventoryItem* Manifest(UObject* NewOuter);
	FGameplayTag GetItemType() const;
	template <typename T> requires std::derived_from<T, FInv_ItemFragment> const T* GetFragmentByTag(const FGameplayTag& FragmentTag) const;
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") EInv_ItemCategory ItemCategory = EInv_ItemCategory::None;
	UPROPERTY(EditAnywhere, Category = "Inventory") FGameplayTag ItemType;
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (ExcludeBaseStruct)) TArray<TInstancedStruct<FInv_ItemFragment>> Fragments;
};

// only types derived from FInv+ItemFragment are allowed
template <typename T> requires std::derived_from<T, FInv_ItemFragment>
const T* FInv_ItemManifest::GetFragmentByTag(const FGameplayTag& FragmentTag) const
{
	for (const TInstancedStruct<FInv_ItemFragment>& Fragment : this->Fragments)
	{
		if (const T* FragmentPtr = Fragment.GetPtr<T>())
		{
			if (!FragmentPtr->GetFragmentTag().MatchesTagExact(FragmentTag)) continue;
			
			return FragmentPtr;
		}
	}
	
	return nullptr;
}

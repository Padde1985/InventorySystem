#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_ItemFragment.generated.h"

USTRUCT(BlueprintType)
struct FInv_ItemFragment
{
	GENERATED_BODY()
	FInv_ItemFragment() {}
	// we have to define special member functions as, by defining a destructor, some functionality gets automatically disabled (rule of 5)
	FInv_ItemFragment(const FInv_ItemFragment&) = default;
	FInv_ItemFragment& operator=(const FInv_ItemFragment&) = default;
	FInv_ItemFragment(FInv_ItemFragment&&) = default;
	FInv_ItemFragment& operator=(FInv_ItemFragment&&) = default;
	//end of special functions
	virtual ~FInv_ItemFragment() {} // this one is the 5th special function
	
	FGameplayTag GetFragmentTag() const;
	void SetFragmentTag(FGameplayTag Tag);
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
};

USTRUCT(BlueprintType)
struct FInv_GridFragment : public FInv_ItemFragment
{
	GENERATED_BODY()
	
	FIntPoint GetGridSize() const;
	void SetGridSize(const FIntPoint& Size);
	float GetGridPadding() const;
	void SetGridPadding(float Padding);
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") FIntPoint GridSize{1, 1};
	UPROPERTY(EditAnywhere, Category = "Inventory") float GridPadding{0.f};
};

USTRUCT(BlueprintType)
struct FInv_ImageFragment : public FInv_ItemFragment
{
	GENERATED_BODY()
	
	UTexture2D* GetIcon() const;
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") TObjectPtr<UTexture2D> Icon{nullptr};
	UPROPERTY(EditAnywhere, Category = "Inventory") FVector2D IconDimensions{44.f, 44.f};
};

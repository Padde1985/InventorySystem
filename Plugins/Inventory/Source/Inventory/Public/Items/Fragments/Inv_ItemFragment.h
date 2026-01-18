#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "Inv_ItemFragment.generated.h"

class UInv_CompositeBase;
class APlayerController;

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
	virtual void Manifest();
private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Categories = "FragmentTags")) FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
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
struct FInv_InventoryItemFragment :  public FInv_ItemFragment
{
	GENERATED_BODY()
	
	virtual void Assimilate(UInv_CompositeBase* Composite) const;
	
protected:
	bool MatchesWidgetTag(const UInv_CompositeBase* Composite) const;
};

USTRUCT(BlueprintType)
struct FInv_ImageFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()
	
	UTexture2D* GetIcon() const;
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") TObjectPtr<UTexture2D> Icon{nullptr};
	UPROPERTY(EditAnywhere, Category = "Inventory") FVector2D IconDimensions{44.f, 44.f};
};

USTRUCT(BlueprintType)
struct FInv_StackableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()
	
	int32 GetMaxStackSize() const;
	int32 GetStackCount() const;
	void SetStackCount(int32 Count);
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 MaxStackSize = 1;
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 StackCount = 1;
};

USTRUCT(BlueprintType)
struct FInv_ConsumableFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()
	
	virtual void OnConsume(APlayerController* PC);
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	virtual void Manifest() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (ExcludeBaseStruct)) TArray<TInstancedStruct<FInv_ConsumeModifier>> ConsumeModifiers;
};

USTRUCT(BlueprintType)
struct FInv_LabeledNumberFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()
	
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	virtual void Manifest() override;
	float GetValue() const;
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") FText TextLabel = FText();
	UPROPERTY(VisibleAnywhere, Category = "Inventory") float Value = 0.f;
	UPROPERTY(EditAnywhere, Category = "Inventory") float Max = 0.f;
	UPROPERTY(EditAnywhere, Category = "Inventory") float Min = 0.f;
	UPROPERTY(EditAnywhere, Category = "Inventory") bool bCollapseLabel	= false;
	UPROPERTY(EditAnywhere, Category = "Inventory") bool bCollapseValue	= false;
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 MinFractionalDigits = 1;
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 MaxFractionalDigits = 1;
	
	bool bRandomizeOnManifest = true;
};

USTRUCT(BlueprintType)
struct FInv_ConsumeModifier : public FInv_LabeledNumberFragment
{
	GENERATED_BODY()
	
	virtual void OnConsume(APlayerController* PC);
};

USTRUCT(BlueprintType)
struct FInv_HealthPotionFragment : public FInv_ConsumeModifier
{
	GENERATED_BODY()
	
	 virtual void OnConsume(APlayerController* PC) override;
};

USTRUCT(BlueprintType)
struct FInv_ManaPotionFragment : public FInv_ConsumeModifier
{
	GENERATED_BODY()
	
	virtual void OnConsume(APlayerController* PC) override;
};

USTRUCT(BlueprintType)
struct FInv_TextFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()
	
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	FText GetText() const;
	void SetText(const FText& Text);
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") FText FragmentText;
};
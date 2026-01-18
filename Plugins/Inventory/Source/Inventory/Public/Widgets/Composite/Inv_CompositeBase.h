#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Inv_CompositeBase.generated.h"

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_CompositeBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FGameplayTag GetFragmentTag() const;
	void SetFragmentTag(const FGameplayTag& Tag);
	virtual void Collapse();
	void Expand();
	
	using FuncType = TFunction<void(UInv_CompositeBase*)>;
	virtual void ApplyFunction(FuncType Func);
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") FGameplayTag FragmentTag;
};
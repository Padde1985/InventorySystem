#pragma once

#include "CoreMinimal.h"
#include "Inv_Leaf.h"
#include "Inv_LeafLabeledValue.generated.h"

class UTextBlock;

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_LeafLabeledValue : public UInv_Leaf
{
	GENERATED_BODY()
	
public:
	void SetTextLabel(const FText& Text, bool bCollapse) const;
	void SetTextValue(const FText& Text, bool bCollapse) const;
	virtual void NativePreConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> TextLabel;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> TextValue;
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 FontSizeLabel = 12;
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 FontSizeValue = 18;
	
};

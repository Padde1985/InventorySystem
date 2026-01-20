#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_SlottedItem.h"
#include "Inv_EquippedSlottedItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquippedSlottedItemCLicked, UInv_EquippedSlottedItem*, SlottedItem);

UCLASS()
class INVENTORY_API UInv_EquippedSlottedItem : public UInv_SlottedItem
{
	GENERATED_BODY()
	
public:
	FEquippedSlottedItemCLicked OnItemClicked;
	
	void SetEquipmentTypeTag(const FGameplayTag& Tag);
	FGameplayTag GetEquipmentTypeTag() const;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
private:
	UPROPERTY() FGameplayTag EquipmentTypeTag;
};

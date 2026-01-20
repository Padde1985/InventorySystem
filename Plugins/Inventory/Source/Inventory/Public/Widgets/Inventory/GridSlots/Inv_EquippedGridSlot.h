#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_GridSlot.h"
#include "Inv_EquippedGridSlot.generated.h"

class UOverlay;
class UInv_EquippedSlottedItem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEquippedGridSlotClicked, UInv_EquippedGridSlot*, GridSlot, const FGameplayTag&, EquippmentTypeTag);

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_EquippedGridSlot : public UInv_GridSlot
{
	GENERATED_BODY()
	
public:
	FEquippedGridSlotClicked EquippedSlotClicked;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	UInv_EquippedSlottedItem* OnItemEquipped(UInv_InventoryItem* Item, const FGameplayTag& EquipmentTag, const float TileSize);
	void SetEquippedSlottedItem(UInv_EquippedSlottedItem* Item);
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (Categories = "GameItems.Equipment")) FGameplayTag EquipmentTypeTag;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> GrayedOutIcon;
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_EquippedSlottedItem> EquippedSlottedItemClass;
	UPROPERTY() TObjectPtr<UInv_EquippedSlottedItem> EquippedSlottedItem;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UOverlay> Overlay;
};

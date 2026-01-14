#pragma once

#include "CoreMinimal.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"
#include "Inv_SpatialInventory.generated.h"

class UInv_ItemDescription;
class UCanvasPanel;
class UInv_InventoryGrid;
class UWidgetSwitcher;
class UButton;

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_SpatialInventory : public UInv_InventoryBase
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual FInv_SlotAvailabilityResult HasRoomForItem(UInv_ItemComponent* Component) const override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void OnItemHovered(UInv_InventoryItem *Item) override;
	virtual void OnItemUnhovered() override;
	virtual bool HasHoverItem() const override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UInv_InventoryGrid> Grid_Equippables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UInv_InventoryGrid> Grid_Consumables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UInv_InventoryGrid> Grid_Craftables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UWidgetSwitcher> Switcher;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))	TObjectPtr<UButton> Button_Equippables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))	TObjectPtr<UButton> Button_Consumables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))	TObjectPtr<UButton> Button_Craftables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))	TObjectPtr<UCanvasPanel> CanvasPanel;
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_ItemDescription> ItemDescriptionClass;
	UPROPERTY() TObjectPtr<UInv_ItemDescription> ItemDescriptionWidget;
	UPROPERTY(EditAnywhere, Category = "Inventory") float DescriptionTimerDelay = 0.5f;
	
	TWeakObjectPtr<UInv_InventoryGrid> ActiveGrid;
	FTimerHandle DescriptionTimerHandle;

	UFUNCTION() void ShowEquippables();
	UFUNCTION() void ShowConsumables();
	UFUNCTION() void ShowCraftables();

	void SetActiveGrid(UInv_InventoryGrid* Grid, UButton* Button);
	void DisableButton(UButton* Button) const;
	UInv_ItemDescription* GetItemDescription();
	void SetItemDescrptionSizeAndPosition(UInv_ItemDescription* ItemDescription, UCanvasPanel* Canvas) const;
};

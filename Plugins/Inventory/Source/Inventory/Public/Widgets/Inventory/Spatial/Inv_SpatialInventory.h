#pragma once

#include "CoreMinimal.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"
#include "Inv_SpatialInventory.generated.h"

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

private:
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UInv_InventoryGrid> Grid_Equippables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UInv_InventoryGrid> Grid_Consumables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UInv_InventoryGrid> Grid_Craftables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UWidgetSwitcher> Switcher;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))	TObjectPtr<UButton> Button_Equippables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))	TObjectPtr<UButton> Button_Consumables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))	TObjectPtr<UButton> Button_Craftables;
	UPROPERTY(meta = (AllowPrivateAccess = "true", BindWidget))	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	TWeakObjectPtr<UInv_InventoryGrid> ActiveGrid;

	UFUNCTION() void ShowEquippables();
	UFUNCTION() void ShowConsumables();
	UFUNCTION() void ShowCraftables();

	void SetActiveGrid(UInv_InventoryGrid* Grid, UButton* Button);
	void DisableButton(UButton* Button);
};

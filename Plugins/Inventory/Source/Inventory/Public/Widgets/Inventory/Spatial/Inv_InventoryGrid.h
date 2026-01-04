#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryGrid.generated.h"

class UCanvasPanel;
class UInv_GridSlot;

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	EInv_ItemCtageory GetItemCtageory() const;
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true")) EInv_ItemCtageory ItemCategory;
	UPROPERTY() TArray<TObjectPtr<UInv_GridSlot>> GridSlots;
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 Rows;
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 Columns;
	UPROPERTY(EditAnywhere, Category = "Inventory") float TileSize;
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_GridSlot> GridSlotClass;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UCanvasPanel> CanvasPanel;
	
	void ConstructGrid();
};

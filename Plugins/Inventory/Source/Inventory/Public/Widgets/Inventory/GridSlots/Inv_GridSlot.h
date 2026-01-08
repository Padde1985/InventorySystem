#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_GridSlot.generated.h"

class UInv_InventoryItem;
class UImage;

UENUM(BlueprintType)
enum class EInv_GridSlotState : uint8
{
	Unoccupied,
	Occupied,
	Selected,
	GrayedOut
};

UCLASS(PrioritizeCategories="Inventory")
class INVENTORY_API UInv_GridSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetTileIndex(int32 InTileIndex);
	int32 GetTileIndex() const;
	EInv_GridSlotState GetSlotState() const;
	void SetUnoccupiedTexture();
	void SetOccupiedTexture();
	void SetSelectedTexture();
	void SetGrayedOutTexture();
	TWeakObjectPtr<UInv_InventoryItem> GetInventoryItem() const;
	void SetInventoryItem(UInv_InventoryItem* Item);
	int32 GetStackCount() const;
	void SetStackCount(int32 InStackCount);
	int32 GetUpperLeftIndex() const;
	void SetUpperLeftIndex(int32 InUpperLeftIndex);
	bool GetAvailable() const;
	void SetAvailable(bool InAvailable);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "", meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UImage> Image_GridSlot;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_Unoccupied;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_Occupied;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_Selected;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_GrayedOut;
	
	int32 TileIndex;
	EInv_GridSlotState State;
	int32 StackCount;
	int32 UpperLeftIndex = INDEX_NONE;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bAvailable = true;
};

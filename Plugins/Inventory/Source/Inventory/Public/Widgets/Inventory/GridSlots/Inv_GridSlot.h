#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_GridSlot.generated.h"

class UInv_ItemPopup;
class UInv_InventoryItem;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGridSLotEvents, int32, GridIndex, const FPointerEvent&, MouseEvent);

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
	FGridSLotEvents GridSLotClicked;
	FGridSLotEvents GridSlotHovered;
	FGridSLotEvents GridSlotUnhovered;
	
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
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void SetItemPopup(UInv_ItemPopup* Popup);
	UInv_ItemPopup* GetItemPopup() const;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "", meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UImage> Image_GridSlot;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_Unoccupied;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_Occupied;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_Selected;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_GrayedOut;
	
	int32 TileIndex = INDEX_NONE;
	EInv_GridSlotState State;
	int32 StackCount = 0;
	int32 UpperLeftIndex = INDEX_NONE;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bAvailable = true;
	TWeakObjectPtr<UInv_ItemPopup> ItemPopup;
	
	UFUNCTION() void OnItemPopupDestruct(UUserWidget* Menu);
};

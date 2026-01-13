#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryGrid.generated.h"

class UInv_ItemPopup;
enum class EInv_GridSlotState : uint8;
class UInv_HoverItem;
struct FInv_ImageFragment;
struct FInv_GridFragment;
class UInv_SlottedItem;
struct FInv_ItemManifest;
class UInv_ItemComponent;
class UInv_InventoryComponent;
class UCanvasPanel;
class UInv_GridSlot;
struct FGameplayTag;

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION() void AddItem(UInv_InventoryItem* InventoryItem);
	
	EInv_ItemCategory GetItemCategory() const;
	virtual void NativeOnInitialized() override;
	FInv_SlotAvailabilityResult HasRoomForItem(const UInv_ItemComponent* Component);
	void ShowMouseCursor();
	void HideMouseCursor();
	void SetOwningCanvasPanel(UCanvasPanel* Owner);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true")) EInv_ItemCategory ItemCategory;
	UPROPERTY() TArray<TObjectPtr<UInv_GridSlot>> GridSlots;
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 Rows;
	UPROPERTY(EditAnywhere, Category = "Inventory") int32 Columns;
	UPROPERTY(EditAnywhere, Category = "Inventory") float TileSize;
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_GridSlot> GridSlotClass;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UCanvasPanel> CanvasPanel;
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_SlottedItem> SlottedItemClass;
	UPROPERTY() TMap<int32, TObjectPtr<UInv_SlottedItem>> SlottedItems;
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_HoverItem> HoverItemClass;
	UPROPERTY() TObjectPtr<UInv_HoverItem> HoverItem;
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UUserWidget> VisibleCursorWidgetClass;
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UUserWidget> HiddenCursorWidgetClass;
	UPROPERTY() TObjectPtr<UUserWidget> VisibleCursorWidget;
	UPROPERTY() TObjectPtr<UUserWidget> HiddenCursorWidget;
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_ItemPopup> ItemPopupWidgetClass;
	UPROPERTY() TObjectPtr<UInv_ItemPopup> ItemPopupWidget;
	
	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	TWeakObjectPtr<UCanvasPanel> OwningCanvasPanel;
	FInv_TileParameters TileParameters;
	FInv_TileParameters LastTileParameters;
	int32 ItemDropIndex = INDEX_NONE; // Index where item would be placed
	FInv_SpaceQueryResult CurrentQueryResult;
	bool bMouseWithinCanvas;
	bool bLastMouseWithinCanvas;
	int32 LastHighlightedIndex;
	FIntPoint LastHighlightedDimensions;
	
	void ConstructGrid();
	bool MatchesCategory(const UInv_InventoryItem* Item) const;
	FInv_SlotAvailabilityResult HasRoomForItem(const UInv_InventoryItem* Item);
	FInv_SlotAvailabilityResult HasRoomForItem(const FInv_ItemManifest& Manifest);
	void AddItemToIndices(const FInv_SlotAvailabilityResult& Result, UInv_InventoryItem* NewItem);
	FVector2D GetDrawSize(const FInv_GridFragment* GridFragment) const;
	void SetSlottedItemImage(const UInv_SlottedItem* SlottedItem, const FInv_GridFragment* GridFragment, const FInv_ImageFragment* ImageFragment) const;
	void AddItemAtIndex(UInv_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount);
	UInv_SlottedItem* CreateSlottedItem(UInv_InventoryItem* Item, const bool bStackable, const int32 StackAmount, const FInv_GridFragment* GridFragment, const FInv_ImageFragment* ImageFragment, const int32 Index);
	void AddSlottedItemToCanvas(const int32 Index, const FInv_GridFragment* GridFragment, UInv_SlottedItem* SlottedItem) const;
	void UpdateGridSlots(UInv_InventoryItem* NewItem, const int32 Index, bool bStackableItem, const int32 StackAmount);
	bool HasRoomAtIndex(const UInv_GridSlot* GridSlot, const FIntPoint& Dimensions, const TSet<int32>& CheckedIndices, TSet<int32>& OutTentativelyClaimed, const FGameplayTag& ItemTag, const int32 MaxStackSize);
	bool CheckSlotConstraints(const UInv_GridSlot* SubGridSlot, const TSet<int32>& CheckedIndices, TSet<int32>& OutTentativelyClaimed, const UInv_GridSlot* GridSlot, const FGameplayTag& ItemTag, const int32 MaxStackSize) const;
	bool IsInGridBounds(const int32 StartIndex, const FIntPoint& ItemDimensions) const;
	int32 DetermineFillAmountForSLot(const bool bStackable, const int32 MaxStackSize, const int32 Amount, const UInv_GridSlot* GridSlot) const;
	bool IsRightCLick(const FPointerEvent& MouseEvent) const;
	bool IsLeftCLick(const FPointerEvent& MouseEvent) const;
	void Pickup(UInv_InventoryItem* ClickedItem, const int32 GridIndex);
	void AssignHoverItem(UInv_InventoryItem* Item);
	void AssignHoverItem(UInv_InventoryItem* Item, const int32 GridIndex, const int32 PreviousGridIndex);
	void RemoveItemFromGrid(UInv_InventoryItem* Item, const int32 GridIndex);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void UpdateTileParameters(const FVector2D& CanvasPosition, const FVector2D& MousePosition);
	FIntPoint CalculcateHoveredCoordinates(const FVector2D& CanvasPosition, const FVector2D& MousePosition) const;
	EInv_TileQuadrant CalculateTileQuadrant(const FVector2D& CanvasPosition, const FVector2D& MousePosition) const;
	void OnTileParametersUpdated(const FInv_TileParameters& Params);
	FIntPoint CalculateStartingCoordinate(const FIntPoint& Coordinate, const FIntPoint& Dimensions, const EInv_TileQuadrant Quadrant) const;
	FInv_SpaceQueryResult CheckHoverPosition(const FIntPoint& Position, const FIntPoint& Dimensions);
	bool CursorExitedCanvas(const FVector2D& CanvasPos, const FVector2D& CanvasSize, const FVector2D& Location);
	void HighlightSlots(const int32 Index, const FIntPoint& Dimensions);
	void UnHighlightSlots(const int32 Index, const FIntPoint& Dimensions);
	void ChangeHoverType(const int32 Index, const FIntPoint& Dimensions, EInv_GridSlotState State);
	void PutDownAtIndex(const int32 Index);
	void ClearHoverItem();
	UUserWidget* GetVisibleCursorWidget();
	UUserWidget* GetHiddenCursorWidget();
	void SwapWithHoverItem(UInv_InventoryItem* Item, const int32 Index);
	void SwapStackCounts(const int32 ClickedStackCount, const int32 HoveredStackCount, const int32 Index);
	void ConsumeHoverItemStacks(const int32 ClickedStackCount, const int32 HoveredStackCount, const int32 Index);
	void FillInStack(const int32 FillAmount, const int32 Remainder, const int32 Index);
	void CreateItemPopup(const int32 Index);

	UFUNCTION() void AddStacks(const FInv_SlotAvailabilityResult& Result);
	UFUNCTION() void OnSlottedItemClicked(const int32 GridIndex, const FPointerEvent& MouseEvent);
	UFUNCTION() void OnGridSlotClicked(int32 GridIndex, const FPointerEvent& MouseEvent);
	UFUNCTION() void OnGridSlotHovered(int32 GridIndex, const FPointerEvent& MouseEvent);
	UFUNCTION() void OnGridSlotUnhovered(int32 GridIndex, const FPointerEvent& MouseEvent);
	UFUNCTION() void OnPopupMenuSplit(int32 SplitAmount, int32 Index);
	UFUNCTION() void OnPopupMenuDrop(int32 Index);
	UFUNCTION() void OnPopupMenuConsume(int32 Index);
};

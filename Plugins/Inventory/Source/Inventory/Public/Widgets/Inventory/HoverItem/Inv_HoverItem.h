#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_HoverItem.generated.h"

class UTextBlock;
class UInv_InventoryItem;
class UImage;
struct FGameplayTag;

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_HoverItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetImageBrush(const FSlateBrush& Brush) const;
	void UpdateStackCount(int32 Count) const;
	FGameplayTag GetItemType() const;
	int32 GetStackCount() const;
	bool IsStackable() const;
	void SetIsStackable(bool bStacks);
	int32 GetPreviousGridIndex() const;
	void SetPreviousGridIndex(int32 Index);
	FIntPoint GetGridDimension() const;
	void SetGridDimensions(const FIntPoint& Dimension);
	UInv_InventoryItem* GetInventoryItem() const;
	void SetInventoryItem(UInv_InventoryItem* Item);
	
private:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> Image_Icon;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> Text_StackCount;
	
	int32 PreviousGridIndex;
	FIntPoint GridDimensions;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bIsStackable;
	int32 StackCount = 0;
};

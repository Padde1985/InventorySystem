#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_SlottedItem.generated.h"

class UInv_InventoryItem;
class UImage;
class UTextBlock;

UCLASS()
class INVENTORY_API UInv_SlottedItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetIsStackable(bool bStackable);
	bool GetIsStackable() const;
	void SetImageBrush(const FSlateBrush& Brush) const;
	UImage* GetImageIcon();
	void SetGridIndex(int32 Index);
	int32 GetGridIndex() const;
	void SetGridDimensions(const FIntPoint& Dimensions);
	FIntPoint GetGridDimensions() const;
	void SetInventoryItem(UInv_InventoryItem* Item);
	UInv_InventoryItem* GetInventoryItem() const;
	void UpdateStackCount(int32 StackCount);
	
private:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UImage> Image_Icon;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> Text_StackCount;
	
	int32 GridIndex;
	FIntPoint GridDimensions;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bIsStackable = false;
};

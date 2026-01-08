#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_GridSlot.generated.h"

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
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "", meta = (AllowPrivateAccess = "true", BindWidget)) TObjectPtr<UImage> Image_GridSlot;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_Unoccupied;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_Occupied;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_Selected;
	UPROPERTY(EditAnywhere, Category = "Inventory") FSlateBrush Brush_GrayedOut;
	
	int32 TileIndex;
	EInv_GridSlotState State;
};

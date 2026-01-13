#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"
#include "Blueprint/UserWidget.h"
#include "Inv_ItemPopup.generated.h"

class USizeBox;
class UTextBlock;
class USlider;
class UButton;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FPopupMenuSplit, int32, SplitAmount, int32, Index);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPopupMenuDrop, int32, Index);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPopupMenuConsume, int32, Index);

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_ItemPopup : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FPopupMenuSplit SplitDelegate;
	FPopupMenuDrop DropDelegate;
	FPopupMenuConsume ConsumeDelegate;
	
	virtual void NativeOnInitialized() override;
	int32 GetSplitAmount() const;
	void CollapseSplitButton() const;
	void CollapseConsumeButton() const;
	void SetSliderParams(const float Max, const float Value) const;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	FVector2D GetBoxSize() const;
	void SetGridIndex(int32 Index);
	int32 GetGrindex() const;
	
private:
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> Button_Split;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> Button_Drop;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UButton> Button_Consume;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<USlider> Slider_Split;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<UTextBlock> Text_Split;
	UPROPERTY(meta = (BindWidget)) TObjectPtr<USizeBox> SizeBox_Root;
	
	int32 GridIndex = INDEX_NONE;
	
	UFUNCTION() void SplitButtonClicked();
	UFUNCTION() void DropButtonClicked();
	UFUNCTION() void ConsumeButtonClicked();
	UFUNCTION() void SliderValueChanged(float Value);
};

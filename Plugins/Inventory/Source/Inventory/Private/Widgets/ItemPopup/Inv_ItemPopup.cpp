#include "Widgets/ItemPopup/Inv_ItemPopup.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

void UInv_ItemPopup::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	this->Button_Split->OnClicked.AddDynamic(this, &ThisClass::SplitButtonClicked);
	this->Button_Consume->OnClicked.AddDynamic(this, &ThisClass::ConsumeButtonClicked);
	this->Button_Drop->OnClicked.AddDynamic(this, &ThisClass::DropButtonClicked);
	this->Slider_Split->OnValueChanged.AddDynamic(this, &ThisClass::SliderValueChanged);
}

int32 UInv_ItemPopup::GetSplitAmount() const
{
	return FMath::Floor(this->Slider_Split->GetValue());
}

void UInv_ItemPopup::SplitButtonClicked()
{
	if (this->SplitDelegate.ExecuteIfBound(this->GetSplitAmount(), this->GridIndex))
	{
		RemoveFromParent();
	}
}

void UInv_ItemPopup::DropButtonClicked()
{
	if (this->DropDelegate.ExecuteIfBound(this->GridIndex))
	{
		RemoveFromParent();
	}
}

void UInv_ItemPopup::ConsumeButtonClicked()
{
	if (this->ConsumeDelegate.ExecuteIfBound(this->GridIndex))
	{
		RemoveFromParent();
	}
}

void UInv_ItemPopup::SliderValueChanged(float Value)
{
	this->Text_Split->SetText(FText::AsNumber(FMath::Floor(Value)));
}

void UInv_ItemPopup::CollapseSplitButton() const
{
	this->Button_Split->SetVisibility(ESlateVisibility::Collapsed);
	this->Slider_Split->SetVisibility(ESlateVisibility::Collapsed);
	this->Text_Split->SetVisibility(ESlateVisibility::Collapsed);
}

void UInv_ItemPopup::CollapseConsumeButton() const
{
	this->Button_Consume->SetVisibility(ESlateVisibility::Collapsed);
}

void UInv_ItemPopup::SetSliderParams(const float Max, const float Value) const
{
	this->Slider_Split->SetMaxValue(Max);
	this->Slider_Split->SetMinValue(1);
	this->Slider_Split->SetValue(Value);
	this->Text_Split->SetText(FText::AsNumber(this->Slider_Split->GetValue()));
}

void UInv_ItemPopup::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	RemoveFromParent();
}

FVector2D UInv_ItemPopup::GetBoxSize() const
{
	return FVector2D(this->SizeBox_Root->GetWidthOverride(), this->SizeBox_Root->GetHeightOverride());
}

void UInv_ItemPopup::SetGridIndex(int32 Index)
{
	this->GridIndex = Index;
}

int32 UInv_ItemPopup::GetGrindex() const
{
	return this->GridIndex;
}

#include "Widgets/Composite/Inv_LeafLabeledValue.h"
#include "Components/TextBlock.h"

void UInv_LeafLabeledValue::SetTextLabel(const FText& Text, bool bCollapse) const
{
	if (bCollapse)
	{
		this->TextLabel->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	this->TextLabel->SetText(Text);
}

void UInv_LeafLabeledValue::SetTextValue(const FText& Text, bool bCollapse) const
{
	if (bCollapse)
	{
		this->TextValue->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	this->TextValue->SetText(Text);
}

void UInv_LeafLabeledValue::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	FSlateFontInfo FontLabel = this->TextLabel->GetFont();
	FontLabel.Size = this->FontSizeLabel;
	this->TextLabel->SetFont(FontLabel);
	
	FSlateFontInfo FontValue = this->TextValue->GetFont();
	FontValue.Size = this->FontSizeValue;
	this->TextValue->SetFont(FontValue);	
}
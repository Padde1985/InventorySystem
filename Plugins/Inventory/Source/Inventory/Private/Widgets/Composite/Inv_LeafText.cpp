#include "Widgets/Composite/Inv_LeafText.h"
#include "Components/TextBlock.h"

// set text
void UInv_LeafText::SetText(const FText& Text) const
{
	this->TextBlock->SetText(Text);
}

// set basic settings
void UInv_LeafText::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	FSlateFontInfo Font = this->TextBlock->GetFont();
	Font.Size = this->FontSize;
	this->TextBlock->SetFont(Font);
}
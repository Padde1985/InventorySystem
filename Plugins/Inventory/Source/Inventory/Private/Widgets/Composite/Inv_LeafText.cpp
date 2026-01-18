#include "Widgets/Composite/Inv_LeafText.h"

#include "Components/TextBlock.h"

void UInv_LeafText::SetText(const FText& Text) const
{
	this->TextBlock->SetText(Text);
}

void UInv_LeafText::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	FSlateFontInfo Font = this->TextBlock->GetFont();
	Font.Size = this->FontSize;
	this->TextBlock->SetFont(Font);
}

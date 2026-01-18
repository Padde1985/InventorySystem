#include "Widgets/Composite/Inv_LeafImage.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

void UInv_LeafImage::SetImage(UTexture2D* Texture) const
{
	this->ImageIcon->SetBrushFromTexture(Texture);
}

void UInv_LeafImage::SetBoxSize(const FVector2D Size) const
{
	this->SizeBoxIcon->SetWidthOverride(Size.X);
	this->SizeBoxIcon->SetHeightOverride(Size.Y);
}

void UInv_LeafImage::SetImageSize(const FVector2D Size) const
{
	this->ImageIcon->SetDesiredSizeOverride(Size);
}

FVector2D UInv_LeafImage::GetImageSize() const
{
	return this->ImageIcon->GetDesiredSize();
}

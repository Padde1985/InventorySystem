#include "Widgets/Composite/Inv_LeafImage.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

// set image
void UInv_LeafImage::SetImage(UTexture2D* Texture) const
{
	this->ImageIcon->SetBrushFromTexture(Texture);
}

// set box dimensions
void UInv_LeafImage::SetBoxSize(const FVector2D Size) const
{
	this->SizeBoxIcon->SetWidthOverride(Size.X);
	this->SizeBoxIcon->SetHeightOverride(Size.Y);
}

// set image size based on fragment information
void UInv_LeafImage::SetImageSize(const FVector2D Size) const
{
	this->ImageIcon->SetDesiredSizeOverride(Size);
}

// getter for image size
FVector2D UInv_LeafImage::GetImageSize() const
{
	return this->ImageIcon->GetDesiredSize();
}
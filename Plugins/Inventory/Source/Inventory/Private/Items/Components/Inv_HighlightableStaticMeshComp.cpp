#include "Items/Components/Inv_HighlightableStaticMeshComp.h"

void UInv_HighlightableStaticMeshComp::Highlight_Implementation()
{
	SetOverlayMaterial(this->HighlightMaterial);
}

void UInv_HighlightableStaticMeshComp::UnHighlight_Implementation()
{
	SetOverlayMaterial(nullptr);
}
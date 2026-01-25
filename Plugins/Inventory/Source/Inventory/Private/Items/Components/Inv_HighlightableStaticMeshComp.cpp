#include "Items/Components/Inv_HighlightableStaticMeshComp.h"

// highlight material (highlighting potions in the world)
void UInv_HighlightableStaticMeshComp::Highlight_Implementation()
{
	SetOverlayMaterial(this->HighlightMaterial);
}

// unhighlight material in the world
void UInv_HighlightableStaticMeshComp::UnHighlight_Implementation()
{
	SetOverlayMaterial(nullptr);
}
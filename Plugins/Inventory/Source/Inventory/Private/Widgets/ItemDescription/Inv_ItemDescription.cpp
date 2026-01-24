#include "Widgets/ItemDescription/Inv_ItemDescription.h"
#include "Components/SizeBox.h"

FVector2D UInv_ItemDescription::GetBoxSize() const
{
	return this->SizeBox->GetDesiredSize();
}

void UInv_ItemDescription::SetVisibility(ESlateVisibility InVisibility)
{
	for (UInv_CompositeBase* Child : GetChildren())
	{
		Child->Collapse();
	}
	Super::SetVisibility(InVisibility);
}

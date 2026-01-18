#include "Widgets/Composite/Inv_CompositeBase.h"

FGameplayTag UInv_CompositeBase::GetFragmentTag() const
{
	return this->FragmentTag;
}

void UInv_CompositeBase::SetFragmentTag(const FGameplayTag& Tag)
{
	this->FragmentTag = Tag;
}

void UInv_CompositeBase::Collapse()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UInv_CompositeBase::Expand()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UInv_CompositeBase::ApplyFunction(FuncType Func)
{
}

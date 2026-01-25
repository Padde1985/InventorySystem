#include "Widgets/Composite/Inv_CompositeBase.h"

// getter for fragment tag
FGameplayTag UInv_CompositeBase::GetFragmentTag() const
{
	return this->FragmentTag;
}

// setter for fragment tag
void UInv_CompositeBase::SetFragmentTag(const FGameplayTag& Tag)
{
	this->FragmentTag = Tag;
}

// set visibility to collapse
void UInv_CompositeBase::Collapse()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

// set visibility to visible
void UInv_CompositeBase::Expand()
{
	SetVisibility(ESlateVisibility::Visible);
}

// placeholder, gets overriden in all child classes
void UInv_CompositeBase::ApplyFunction(FuncType Func)
{
}
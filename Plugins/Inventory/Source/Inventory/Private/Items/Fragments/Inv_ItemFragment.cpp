#include "Items/Fragments/Inv_ItemFragment.h"

FGameplayTag FInv_ItemFragment::GetFragmentTag() const
{
	return this->FragmentTag;
}

void FInv_ItemFragment::SetFragmentTag(FGameplayTag Tag)
{
	this->FragmentTag = Tag;
}

FIntPoint FInv_GridFragment::GetGridSize() const
{
	return this->GridSize;
}

void FInv_GridFragment::SetGridSize(const FIntPoint& Size)
{
	this->GridSize = Size;
}

float FInv_GridFragment::GetGridPadding() const
{
	return this->GridPadding;
}

void FInv_GridFragment::SetGridPadding(float Padding)
{
	this->GridPadding = Padding;
}

UTexture2D* FInv_ImageFragment::GetIcon() const
{
	return this->Icon;
}

int32 FInv_StackableFragment::GetMaxStackSize() const
{
	return this->MaxStackSize;
}

int32 FInv_StackableFragment::GetStackCount() const
{
	return this->StackCount;
}

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

void FInv_StackableFragment::SetStackCount(int32 Count)
{
	this->StackCount = Count;
}

void FInv_ConsumableFragment::OnConsume(APlayerController* PC)
{
	//do something generic
}

void FInv_HealthPotionFragment::OnConsume(APlayerController* PC)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health Potion consumed healing by: %f"), this->HealAmount));
	// do something specific
}

void FInv_ManaPotionFragment::OnConsume(APlayerController* PC)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Mana Potion consumed healing by: %f"), this->ManaAmount));
	// do something specific
}

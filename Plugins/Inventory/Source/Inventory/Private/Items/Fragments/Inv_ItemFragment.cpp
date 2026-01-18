#include "Items/Fragments/Inv_ItemFragment.h"
#include "Widgets/Composite/Inv_CompositeBase.h"
#include "Widgets/Composite/Inv_LeafImage.h"
#include "Widgets/Composite/Inv_LeafLabeledValue.h"
#include "Widgets/Composite/Inv_LeafText.h"

FGameplayTag FInv_ItemFragment::GetFragmentTag() const
{
	return this->FragmentTag;
}

void FInv_ItemFragment::SetFragmentTag(FGameplayTag Tag)
{
	this->FragmentTag = Tag;
}

void FInv_ItemFragment::Manifest()
{
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

void FInv_ImageFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	
	if (!MatchesWidgetTag(Composite)) return;
	
	UInv_LeafImage* Image = Cast<UInv_LeafImage>(Composite);
	if (!IsValid(Image)) return;
	
	Image->SetImage(this->Icon);
	Image->SetBoxSize(this->IconDimensions);
	Image->SetImageSize(this->IconDimensions);
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
	for (TInstancedStruct<FInv_ConsumeModifier>& Modifier : this->ConsumeModifiers)
	{
		FInv_ConsumeModifier& ModRef = Modifier.GetMutable();
		ModRef.OnConsume(PC);
	}
}

void FInv_ConsumableFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	
	for (const TInstancedStruct<FInv_ConsumeModifier>& Modifier : this->ConsumeModifiers)
	{
		const FInv_ConsumeModifier& ModRef = Modifier.Get();
		ModRef.Assimilate(Composite);
	}
}

void FInv_ConsumableFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
	
	for (TInstancedStruct<FInv_ConsumeModifier>& Modifier : this->ConsumeModifiers)
	{
		FInv_ConsumeModifier& ModRef = Modifier.GetMutable();
		ModRef.Manifest();
	}
}

void FInv_HealthPotionFragment::OnConsume(APlayerController* PC)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health Potion consumed healing by: %f"), GetValue()));
	// do something specific
}

void FInv_ManaPotionFragment::OnConsume(APlayerController* PC)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Mana Potion consumed healing by: %f"), GetValue()));
	// do something specific
}

void FInv_TextFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	
	if (!MatchesWidgetTag(Composite)) return;
	
	UInv_LeafText* Text = Cast<UInv_LeafText>(Composite);
	if (!IsValid(Text)) return;
	
	Text->SetText(this->FragmentText);
}

FText FInv_TextFragment::GetText() const
{
	return this->FragmentText;
}

void FInv_TextFragment::SetText(const FText& Text)
{
	this->FragmentText = Text;
}

void FInv_LabeledNumberFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	
	if (!MatchesWidgetTag(Composite)) return;
	
	UInv_LeafLabeledValue* LabeledValue = Cast<UInv_LeafLabeledValue>(Composite);
	if (!IsValid(LabeledValue)) return;
	
	LabeledValue->SetTextLabel(this->TextLabel, this->bCollapseLabel);
	
	FNumberFormattingOptions NumberFormattingOptions;
	NumberFormattingOptions.MinimumFractionalDigits = this->MinFractionalDigits;
	NumberFormattingOptions.MaximumFractionalDigits = this->MaxFractionalDigits;
	LabeledValue->SetTextValue(FText::AsNumber(this->Value, &NumberFormattingOptions), this->bCollapseValue);
}

void FInv_LabeledNumberFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
	
	if (this->bRandomizeOnManifest)
	{
		this->Value = FMath::FRandRange(this->Min, this->Max);
	}
	this->bRandomizeOnManifest = false;
}

float FInv_LabeledNumberFragment::GetValue() const
{
	return this->Value;
}

void FInv_ConsumeModifier::OnConsume(APlayerController* PC)
{
}

void FInv_InventoryItemFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	if (!this->MatchesWidgetTag(Composite))
	{
		Composite->Collapse();
		return;
	}
	
	Composite->Expand();
}

bool FInv_InventoryItemFragment::MatchesWidgetTag(const UInv_CompositeBase* Composite) const
{
	return Composite->GetFragmentTag().MatchesTagExact(GetFragmentTag());
}

#include "Items/Fragments/Inv_ItemFragment.h"
#include "EquipmentManagement/EquipActor/Inv_EquipActor.h"
#include "Widgets/Composite/Inv_CompositeBase.h"
#include "Widgets/Composite/Inv_LeafImage.h"
#include "Widgets/Composite/Inv_LeafLabeledValue.h"
#include "Widgets/Composite/Inv_LeafText.h"

// getter for fragment tag
FGameplayTag FInv_ItemFragment::GetFragmentTag() const
{
	return this->FragmentTag;
}

// set the fragment tag
void FInv_ItemFragment::SetFragmentTag(FGameplayTag Tag)
{
	this->FragmentTag = Tag;
}

// manifest placeholder, gets overridden in all child classes
void FInv_ItemFragment::Manifest()
{
}

// getter for grid size
FIntPoint FInv_GridFragment::GetGridSize() const
{
	return this->GridSize;
}

// setter for grid size
void FInv_GridFragment::SetGridSize(const FIntPoint& Size)
{
	this->GridSize = Size;
}

// getter for grid padding
float FInv_GridFragment::GetGridPadding() const
{
	return this->GridPadding;
}

// setter for grid padding
void FInv_GridFragment::SetGridPadding(float Padding)
{
	this->GridPadding = Padding;
}

// getter for item icon
UTexture2D* FInv_ImageFragment::GetIcon() const
{
	return this->Icon;
}

// assimiliate function, gets called by the item fragment to initialize settings
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

// getter for maximum stack count
int32 FInv_StackableFragment::GetMaxStackSize() const
{
	return this->MaxStackSize;
}

// getter for current stack count
int32 FInv_StackableFragment::GetStackCount() const
{
	return this->StackCount;
}

// setter for stack count
void FInv_StackableFragment::SetStackCount(int32 Count)
{
	this->StackCount = Count;
}

// callback for consuming an item
void FInv_ConsumableFragment::OnConsume(APlayerController* PC)
{
	for (TInstancedStruct<FInv_ConsumeModifier>& Modifier : this->ConsumeModifiers)
	{
		FInv_ConsumeModifier& ModRef = Modifier.GetMutable();
		ModRef.OnConsume(PC);
	}
}

// assimilate function, gets called by item fragment to initialize basic settings
void FInv_ConsumableFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	
	for (const TInstancedStruct<FInv_ConsumeModifier>& Modifier : this->ConsumeModifiers)
	{
		const FInv_ConsumeModifier& ModRef = Modifier.Get();
		ModRef.Assimilate(Composite);
	}
}

// manifest function, gets called by the item fragment to set run time values
void FInv_ConsumableFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
	
	for (TInstancedStruct<FInv_ConsumeModifier>& Modifier : this->ConsumeModifiers)
	{
		FInv_ConsumeModifier& ModRef = Modifier.GetMutable();
		ModRef.Manifest();
	}
}

// callback for consuming an item
void FInv_HealthPotionFragment::OnConsume(APlayerController* PC)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health Potion consumed healing by: %f"), GetValue()));
	// do something specific
}

// callback for consuming an item
void FInv_ManaPotionFragment::OnConsume(APlayerController* PC)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Mana Potion consumed healing by: %f"), GetValue()));
	// do something specific
}

// assimilate function, called by item fragment to set the item text
void FInv_TextFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	
	if (!MatchesWidgetTag(Composite)) return;
	
	UInv_LeafText* Text = Cast<UInv_LeafText>(Composite);
	if (!IsValid(Text)) return;
	
	Text->SetText(this->FragmentText);
}

// getter for item text
FText FInv_TextFragment::GetText() const
{
	return this->FragmentText;
}

// setter for item text
void FInv_TextFragment::SetText(const FText& Text)
{
	this->FragmentText = Text;
}

// callback for equipping an item
void FInv_EquipmentFragment::OnEquip(APlayerController* PC)
{
	if (this->bEquipped) return;
	
	this->bEquipped = true;
	for (TInstancedStruct<FInv_EquipModifier>& Modifier : this->EquipModifiers)
	{
		FInv_EquipModifier& ModRef = Modifier.GetMutable();
		ModRef.OnEquip(PC);
	}
}

// callback for unequipping an item
void FInv_EquipmentFragment::OnUnequip(APlayerController* PC)
{
	if (!this->bEquipped) return;
	
	this->bEquipped = false;
	for (TInstancedStruct<FInv_EquipModifier>& Modifier : this->EquipModifiers)
	{
		FInv_EquipModifier& ModRef = Modifier.GetMutable();
		ModRef.OnUnequip(PC);
	}
}

// assimilate function, called by item fragment 
void FInv_EquipmentFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	
	for (const TInstancedStruct<FInv_EquipModifier>& Modifier : this->EquipModifiers)
	{
		const FInv_EquipModifier& ModRef = Modifier.Get();
		ModRef.Assimilate(Composite);
	}
}

// manifest function, called by item fragment
void FInv_EquipmentFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
	
	for (TInstancedStruct<FInv_EquipModifier>& Modifier : this->EquipModifiers)
	{
		FInv_EquipModifier& ModRef = Modifier.GetMutable();
		ModRef.Manifest();
	}
}

// spawn the equipped actor and attach to socket
AInv_EquipActor* FInv_EquipmentFragment::SpawnAttachedActor(USkeletalMeshComponent* AttachMesh) const
{
	if (!IsValid(this->EquipActorClass) || !IsValid(AttachMesh)) return nullptr;
	
	AInv_EquipActor* SpawnActor = AttachMesh->GetWorld()->SpawnActor<AInv_EquipActor>(this->EquipActorClass);
	SpawnActor->AttachToComponent(AttachMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, this->SocketAttachPoint);
	
	return SpawnActor;
}

// destroy attached actor when unequipping
void FInv_EquipmentFragment::DestroyAttachedActor()
{
	if (this->EquipActor.IsValid()) this->EquipActor.Reset(); this->EquipActor->Destroy();
}

// getter for equipment type
FGameplayTag FInv_EquipmentFragment::GetEquipmentType() const
{
	return this->EquipmentType;
}

// setter for equipped actor
void FInv_EquipmentFragment::SetEquippedActor(AInv_EquipActor* Actor)
{
	this->EquipActor = Actor;
}

// placeholder
void FInv_EquipModifier::OnEquip(APlayerController* PC)
{
}

// placeholder
void FInv_EquipModifier::OnUnequip(APlayerController* PC)
{
}

// placeholder
void FInv_StrengthModifier::OnEquip(APlayerController* PC)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("Strength increased by: %f"), GetValue()));
}

// placeholder
void FInv_StrengthModifier::OnUnequip(APlayerController* PC)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Strength decreased by: %f"), GetValue()));
}

// assimilate function, called by item fragment to set basic settings
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

// manifest function, called by item fragment to generate run time values
void FInv_LabeledNumberFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
	
	if (this->bRandomizeOnManifest)
	{
		this->Value = FMath::FRandRange(this->Min, this->Max);
	}
	this->bRandomizeOnManifest = false;
}

// getter for number value
float FInv_LabeledNumberFragment::GetValue() const
{
	return this->Value;
}

// placeholder
void FInv_ConsumeModifier::OnConsume(APlayerController* PC)
{
}

// assimilate function, called by item fragment
void FInv_InventoryItemFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	if (!this->MatchesWidgetTag(Composite))	return;
	
	Composite->Expand();
}

// check if the current fragment tag matches the given tag
bool FInv_InventoryItemFragment::MatchesWidgetTag(const UInv_CompositeBase* Composite) const
{
	return Composite->GetFragmentTag().MatchesTagExact(GetFragmentTag());
}
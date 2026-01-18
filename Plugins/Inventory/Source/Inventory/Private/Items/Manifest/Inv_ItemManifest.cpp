#include "Items/Manifest/Inv_ItemManifest.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Items/Fragments/Inv_ItemFragment.h"
#include "Widgets/Composite/Inv_CompositeBase.h"

EInv_ItemCategory FInv_ItemManifest::GetItemCategory() const
{
	return this->ItemCategory;
}

UInv_InventoryItem* FInv_ItemManifest::Manifest(UObject* NewOuter)
{
	UInv_InventoryItem* Item = NewObject<UInv_InventoryItem>(NewOuter, UInv_InventoryItem::StaticClass());
	Item->SetItemManifest(*this);
	
	for (TInstancedStruct<FInv_ItemFragment>& FragmentPtr : Item->GetItemManifestMutable().GetAllFragmentsMutable())
	{
		FragmentPtr.GetMutable().Manifest();
	}
	this->ClearFragments();
	
	return Item;
}

FGameplayTag FInv_ItemManifest::GetItemType() const
{
	return this->ItemType;
}

void FInv_ItemManifest::SpawnPickupActor(const UObject* WorldContextObject, const FVector& SpawnLocation, const FRotator& SpawnRotation) const
{
	if (!IsValid(this->PickupActorClass) || !IsValid(WorldContextObject)) return;
	
	AActor* SpawnedActor = WorldContextObject->GetWorld()->SpawnActor<AActor>(this->PickupActorClass, SpawnLocation, SpawnRotation);
	if (!IsValid(SpawnedActor)) return;
	
	UInv_ItemComponent* ItemComp = SpawnedActor->FindComponentByClass<UInv_ItemComponent>();
	check(ItemComp);
	
	ItemComp->InitItemManifest(*this);
}

void FInv_ItemManifest::AssimilateInventoryFragments(UInv_CompositeBase* Composite) const
{
	const TArray<const FInv_InventoryItemFragment*>& AssimilateFragments = this->GetAllFragmentsByType<FInv_InventoryItemFragment>();
	for (const FInv_InventoryItemFragment* FragmentPtr : AssimilateFragments)
	{
		Composite->ApplyFunction([FragmentPtr](UInv_CompositeBase* Widget)
		{
			FragmentPtr->Assimilate(Widget);
		});
	}
}

TArray<TInstancedStruct<FInv_ItemFragment>>& FInv_ItemManifest::GetAllFragmentsMutable()
{
	return this->Fragments;
}

void FInv_ItemManifest::ClearFragments()
{
	for (TInstancedStruct<FInv_ItemFragment>& FragmentPtr : this->GetAllFragmentsMutable())
	{
		FragmentPtr.Reset();
	}
	this->GetAllFragmentsMutable().Empty();
}

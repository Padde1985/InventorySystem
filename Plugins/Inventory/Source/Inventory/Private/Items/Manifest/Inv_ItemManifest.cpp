#include "Items/Manifest/Inv_ItemManifest.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"

EInv_ItemCategory FInv_ItemManifest::GetItemCategory() const
{
	return this->ItemCategory;
}

UInv_InventoryItem* FInv_ItemManifest::Manifest(UObject* NewOuter)
{
	UInv_InventoryItem* Item = NewObject<UInv_InventoryItem>(NewOuter, UInv_InventoryItem::StaticClass());
	Item->SetItemManifest(*this);
	
	return Item;
}

FGameplayTag FInv_ItemManifest::GetItemType() const
{
	return this->ItemType;
}

void FInv_ItemManifest::SpawnPickupActor(const UObject* WorldContextObject, const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
	if (!IsValid(this->PickupActorClass) || !IsValid(WorldContextObject)) return;
	
	AActor* SpawnedActor = WorldContextObject->GetWorld()->SpawnActor<AActor>(this->PickupActorClass, SpawnLocation, SpawnRotation);
	if (!IsValid(SpawnedActor)) return;
	
	UInv_ItemComponent* ItemComp = SpawnedActor->FindComponentByClass<UInv_ItemComponent>();
	check(ItemComp);
	
	ItemComp->InitItemManifest(*this);
}

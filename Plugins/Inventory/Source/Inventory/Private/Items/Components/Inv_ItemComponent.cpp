#include "Items/Components/Inv_ItemComponent.h"
#include "Net/UnrealNetwork.h"

// set replication and pickup message
UInv_ItemComponent::UInv_ItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	this->PickupMessage = FString("E - Pick up Item");
}

// getter for pickup message
FString UInv_ItemComponent::GetPickupMessage() const
{
	return this->PickupMessage;
}

// replication for item manifest, only needed for multiplayer
void UInv_ItemComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, ItemManifest);
}

// getter for item manifest
FInv_ItemManifest UInv_ItemComponent::GetItemManifest() const
{
	return this->ItemManifest;
}

// getter for editable item manifest
FInv_ItemManifest& UInv_ItemComponent::GetItemManifestMutable()
{
	return this->ItemManifest;
}

// callback for picked up item
void UInv_ItemComponent::PickedUp()
{
	this->OnPickedUp();
	GetOwner()->Destroy();
}

// store item manifest on item component
void UInv_ItemComponent::InitItemManifest(FInv_ItemManifest CopyOfManifest)
{
	this->ItemManifest = CopyOfManifest;
}
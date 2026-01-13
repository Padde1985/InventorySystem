#include "Items/Components/Inv_ItemComponent.h"
#include "Net/UnrealNetwork.h"

UInv_ItemComponent::UInv_ItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	this->PickupMessage = FString("E - Pick up Item");
}

FString UInv_ItemComponent::GetPickupMessage() const
{
	return this->PickupMessage;
}

void UInv_ItemComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, ItemManifest);
}

FInv_ItemManifest UInv_ItemComponent::GetItemManifest() const
{
	return this->ItemManifest;
}

void UInv_ItemComponent::PickedUp()
{
	this->OnPickedUp();
	GetOwner()->Destroy();
}

void UInv_ItemComponent::InitItemManifest(FInv_ItemManifest CopyOfManifest)
{
	this->ItemManifest = CopyOfManifest;
}


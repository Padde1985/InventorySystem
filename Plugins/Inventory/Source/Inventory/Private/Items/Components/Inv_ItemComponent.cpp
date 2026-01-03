#include "Items/Components/Inv_ItemComponent.h"

UInv_ItemComponent::UInv_ItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	this->PickupMessage = FString("E - Pick up Item");
}

FString UInv_ItemComponent::GetPickupMessage() const
{
	return this->PickupMessage;
}


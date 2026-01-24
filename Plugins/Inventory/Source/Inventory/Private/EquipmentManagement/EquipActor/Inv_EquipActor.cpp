#include "EquipmentManagement/EquipActor/Inv_EquipActor.h"

// Sets default values
AInv_EquipActor::AInv_EquipActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

FGameplayTag AInv_EquipActor::GetEquipmentType() const
{
	return this->EquipmentType;
}

void AInv_EquipActor::SetEquipmentType(FGameplayTag Type)
{
	this->EquipmentType = Type;
}

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Inv_EquipActor.generated.h"

UCLASS(PrioritizeCategories=("Inventory"))
class INVENTORY_API AInv_EquipActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInv_EquipActor();
	
	FGameplayTag GetEquipmentType() const;
	void SetEquipmentType(FGameplayTag Type);
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory") FGameplayTag EquipmentType;
};

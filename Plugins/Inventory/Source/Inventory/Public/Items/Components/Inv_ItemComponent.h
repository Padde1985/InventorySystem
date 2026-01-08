#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Inv_ItemComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), PrioritizeCategories = ("Inventory"), Blueprintable)
class INVENTORY_API UInv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInv_ItemComponent();

	FString GetPickupMessage() const;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	FInv_ItemManifest GetItemManifest() const;

private:
	UPROPERTY(EditAnywhere, Category = "Inventory") FString PickupMessage;
	UPROPERTY(EditAnywhere, Category = "Inventory", Replicated) FInv_ItemManifest ItemManifest;
};

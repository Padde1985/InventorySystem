#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Inv_EquipmentComponent.generated.h"

struct FInv_ItemManifest;
struct FInv_EquipmentFragment;
class AInv_EquipActor;
class UInv_InventoryComponent;
class UInv_InventoryItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void SetOwningSkeletalMesh(USkeletalMeshComponent* OwningMesh);
	void SetIsProxy(bool bProxy);
	void InitializeOwner(APlayerController* PlayerController);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY() TArray<TObjectPtr<AInv_EquipActor>> EquippedActors;
	
	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	TWeakObjectPtr<APlayerController> OwningPlayerController;
	TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	bool bIsProxy = false;
	
	UFUNCTION() void OnItemEquipped(UInv_InventoryItem* EquippedItem);
	UFUNCTION() void OnItemUnequipped(UInv_InventoryItem* UnequippedItem);
	UFUNCTION() void OnPossedPawnChange(APawn* OldPawn, APawn* NewPawn);
	
	void InitInventoryComponent();
	AInv_EquipActor* SpawnEquippedActor(FInv_EquipmentFragment* EquipmentFragment, const FInv_ItemManifest& Manifest, USkeletalMeshComponent* AttachMesh) const;
	AInv_EquipActor* FindEquippedActorByType(const FGameplayTag& Tag);
	void RemoveEquippedActor(const FGameplayTag& Tag);
	void InitPlayerController();
};

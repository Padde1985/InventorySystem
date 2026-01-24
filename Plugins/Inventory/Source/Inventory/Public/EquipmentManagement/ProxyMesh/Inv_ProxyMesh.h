#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inv_ProxyMesh.generated.h"

class UInv_EquipmentComponent;

UCLASS()
class INVENTORY_API AInv_ProxyMesh : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInv_ProxyMesh();
	
	USkeletalMeshComponent* GetMesh() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory") TObjectPtr<UInv_EquipmentComponent> EquipmentComponent;
	UPROPERTY(VisibleAnywhere, Category = "Inventory") TObjectPtr<USkeletalMeshComponent> Mesh;
	
	TWeakObjectPtr<USkeletalMeshComponent> SourceCharacterMesh;
	FTimerHandle TimerForNextTick;
	
	void DelayedInitializeOwner();
	void DelayedInitialization();
};

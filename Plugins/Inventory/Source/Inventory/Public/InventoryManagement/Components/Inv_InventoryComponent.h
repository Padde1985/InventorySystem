#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inv_InventoryComponent.generated.h"

class UInv_InventoryBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), PrioritizeCategories = ("Inventory"), Blueprintable)
class INVENTORY_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInv_InventoryComponent();

	void ToggleInventoryMenu();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_InventoryBase> InventoryMenuClass;
	UPROPERTY() TObjectPtr<UInv_InventoryBase> InventoryMenu;

	TWeakObjectPtr<APlayerController> OwningController;
	bool bInventoryMenuOpen;

	void ConstructInventory();
	void OpenInventoryMenu();
	void CloseInventoryMenu();
};

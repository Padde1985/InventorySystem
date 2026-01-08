#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagement/FastArray/Inv_FastArray.h"
#include "Inv_InventoryComponent.generated.h"

class UInv_InventoryItem;
class UInv_InventoryBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UInv_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoRoomInInvetory);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), PrioritizeCategories = ("Inventory"), Blueprintable)
class INVENTORY_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;
	FNoRoomInInvetory InventorySpace;
	
	// Sets default values for this component's properties
	UInv_InventoryComponent();

	UFUNCTION(BlueprintCallable, Category="Inventory", BlueprintAuthorityOnly) void TryAddItem(UInv_ItemComponent* ItemComponent);
	UFUNCTION(Server, Reliable) void Server_AddNewItem(UInv_ItemComponent* ItemComponent, int32 StackCount);
	UFUNCTION(Server, Reliable) void Server_AddStacksToItem(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);
	
	void ToggleInventoryMenu();
	void AddRepSubObj(UObject* SubObj);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_InventoryBase> InventoryMenuClass;
	UPROPERTY() TObjectPtr<UInv_InventoryBase> InventoryMenu;
	UPROPERTY(Replicated) FInv_InventoryFastArray InventoryList;

	TWeakObjectPtr<APlayerController> OwningController;
	bool bInventoryMenuOpen;

	void ConstructInventory();
	void OpenInventoryMenu();
	void CloseInventoryMenu();
};

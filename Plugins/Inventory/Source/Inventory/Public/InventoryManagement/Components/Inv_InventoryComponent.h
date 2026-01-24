#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagement/FastArray/Inv_FastArray.h"
#include "Inv_InventoryComponent.generated.h"

struct FInv_SlotAvailabilityResult;
class UInv_InventoryItem;
class UInv_InventoryBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UInv_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoRoomInInvetory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStackChange, const FInv_SlotAvailabilityResult&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemEquippedStatusChanged, UInv_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryMenuToggled, bool, bOpen);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), PrioritizeCategories = ("Inventory"), Blueprintable)
class INVENTORY_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;
	FNoRoomInInvetory InventorySpace;
	FStackChange OnStackChange;
	FItemEquippedStatusChanged OnItemEquipped;
	FItemEquippedStatusChanged OnItemUnequipped;
	FInventoryMenuToggled OnInventoryMenuToggle;
	
	// Sets default values for this component's properties
	UInv_InventoryComponent();

	UFUNCTION(BlueprintCallable, Category="Inventory", BlueprintAuthorityOnly) void TryAddItem(UInv_ItemComponent* ItemComponent);
	UFUNCTION(Server, Reliable) void Server_AddNewItem(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);
	UFUNCTION(Server, Reliable) void Server_AddStacksToItem(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);
	UFUNCTION(Server, Reliable) void Server_DropItem(UInv_InventoryItem* Item, int32 StackCount);
	UFUNCTION(Server, Reliable) void Server_ConsumeItem(UInv_InventoryItem* Item);
	UFUNCTION(Server, Reliable) void Server_EquippedSlotClicked(UInv_InventoryItem* ItemToEquip, UInv_InventoryItem* ItemToUnequip); // Server function
	UFUNCTION(NetMulticast, Reliable) void Multicast_EquippedSlotClicked(UInv_InventoryItem* ItemToEquip, UInv_InventoryItem* ItemToUnequip); // same function called from server on all clients
	
	void ToggleInventoryMenu();
	void AddRepSubObj(UObject* SubObj);
	void SpawnDroppedItem(UInv_InventoryItem* Item, int32 StackCount) const;
	UInv_InventoryBase* GetInventoryMenu() const;
	bool IsMenuOpen() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(EditAnywhere, Category = "Inventory") TSubclassOf<UInv_InventoryBase> InventoryMenuClass;
	UPROPERTY() TObjectPtr<UInv_InventoryBase> InventoryMenu;
	UPROPERTY(Replicated) FInv_InventoryFastArray InventoryList;
	UPROPERTY(EditAnywhere, Category = "Inventory") float DropSpawnAngleMin = -85.f;
	UPROPERTY(EditAnywhere, Category = "Inventory") float DropSpawnAngleMax = 85.f;
	UPROPERTY(EditAnywhere, Category = "Inventory") float DropSpawnDistanceMin = 10.f;
	UPROPERTY(EditAnywhere, Category = "Inventory") float DropSpawnDistanceMax = 50.f;
	UPROPERTY(EditAnywhere, Category = "Inventory") float RelativeSpawnElevation = 70.f;

	TWeakObjectPtr<APlayerController> OwningController;
	bool bInventoryMenuOpen;

	void ConstructInventory();
	void OpenInventoryMenu();
	void CloseInventoryMenu();
};

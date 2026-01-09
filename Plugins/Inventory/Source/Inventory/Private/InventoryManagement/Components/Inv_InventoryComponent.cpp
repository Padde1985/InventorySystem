#include "InventoryManagement/Components/Inv_InventoryComponent.h"

#include "Items/Components/Inv_ItemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"
#include "Items/Inv_InventoryItem.h"

// Sets default values for this component's properties
UInv_InventoryComponent::UInv_InventoryComponent() : InventoryList(this)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
	this->bInventoryMenuOpen = false;
}

void UInv_InventoryComponent::TryAddItem(UInv_ItemComponent* ItemComponent)
{
	FInv_SlotAvailabilityResult SlotAvailabilityResult = this->InventoryMenu->HasRoomForItem(ItemComponent);
	UInv_InventoryItem* FoundItem = this->InventoryList.FindFirstItemByType(ItemComponent->GetItemManifest().GetItemType());
	SlotAvailabilityResult.InventoryItem = FoundItem;
	
	if (SlotAvailabilityResult.TotalRoomToFill == 0)
	{
		this->InventorySpace.Broadcast();
		return;
	}
	
	if (SlotAvailabilityResult.InventoryItem.IsValid() && SlotAvailabilityResult.bIsStackable)
	{
		//add stacks to existing item
		this->Server_AddStacksToItem(ItemComponent, SlotAvailabilityResult.TotalRoomToFill, SlotAvailabilityResult.Remainder);
	}
	else if (SlotAvailabilityResult.TotalRoomToFill > 0)
	{
		//create new item and update slots
		this->Server_AddNewItem(ItemComponent, SlotAvailabilityResult.bIsStackable ? SlotAvailabilityResult.TotalRoomToFill : 0);
	}
}

void UInv_InventoryComponent::Server_AddNewItem_Implementation(UInv_ItemComponent* ItemComponent, int32 StackCount)
{
	UInv_InventoryItem* NewItem = this->InventoryList.AddEntry(ItemComponent);
	
	if (GetOwner()->GetNetMode() == ENetMode::NM_ListenServer || GetOwner()->GetNetMode() == ENetMode::NM_Standalone)
	{
		this->OnItemAdded.Broadcast(NewItem);
	}
}

void UInv_InventoryComponent::Server_AddStacksToItem_Implementation(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder)
{
}

void UInv_InventoryComponent::ToggleInventoryMenu()
{
	if (this->bInventoryMenuOpen)
	{
		this->CloseInventoryMenu();
	}
	else
	{
		this->OpenInventoryMenu();
	}
}

void UInv_InventoryComponent::AddRepSubObj(UObject* SubObj)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && IsValid(SubObj))	AddReplicatedSubObject(SubObj);
}

// Called when the game starts
void UInv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	this->ConstructInventory();
}

void UInv_InventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, InventoryList);
}

void UInv_InventoryComponent::ConstructInventory()
{
	this->OwningController = Cast<APlayerController>(GetOwner());
	checkf(this->OwningController.IsValid(), TEXT("InventoryComponent should have a player controller as owner"));
	if (!this->OwningController->IsLocalController()) return;

	this->InventoryMenu = CreateWidget<UInv_InventoryBase>(this->OwningController.Get(), this->InventoryMenuClass);
	this->InventoryMenu->AddToViewport();
	this->CloseInventoryMenu();
}

void UInv_InventoryComponent::OpenInventoryMenu()
{
	if (!IsValid(this->InventoryMenu)) return;

	this->InventoryMenu->SetVisibility(ESlateVisibility::Visible);
	this->bInventoryMenuOpen = true;
	
	if (!this->OwningController.IsValid()) return;
	FInputModeGameAndUI InputMode;
	this->OwningController->SetInputMode(InputMode);
	this->OwningController->SetShowMouseCursor(true);
}

void UInv_InventoryComponent::CloseInventoryMenu()
{
	if (!IsValid(this->InventoryMenu)) return;

	this->InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
	this->bInventoryMenuOpen = false;

	if (!this->OwningController.IsValid()) return;
	FInputModeGameOnly InputMode;
	this->OwningController->SetInputMode(InputMode);
	this->OwningController->SetShowMouseCursor(false);
}



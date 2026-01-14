#include "InventoryManagement/Components/Inv_InventoryComponent.h"

#include "Items/Components/Inv_ItemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Fragments/Inv_ItemFragment.h"

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
		this->OnStackChange.Broadcast(SlotAvailabilityResult);
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
	NewItem->SetStackCount(StackCount);
	
	if (GetOwner()->GetNetMode() == ENetMode::NM_ListenServer || GetOwner()->GetNetMode() == ENetMode::NM_Standalone)
	{
		this->OnItemAdded.Broadcast(NewItem);
	}
	
	ItemComponent->PickedUp();
}

void UInv_InventoryComponent::Server_AddStacksToItem_Implementation(UInv_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder)
{
	const FGameplayTag& ItemType = IsValid(ItemComponent) ? ItemComponent->GetItemManifest().GetItemType() : FGameplayTag::EmptyTag;
	UInv_InventoryItem* Item = this->InventoryList.FindFirstItemByType(ItemType);
	if (!IsValid(Item)) return;
	
	Item->SetStackCount(Item->GetStackCount() + StackCount);
	
	if (Remainder == 0)
	{
		ItemComponent->PickedUp();
	}
	else if (FInv_StackableFragment* StackableFragment = ItemComponent->GetItemManifest().GetFragmentByTypeMutable<FInv_StackableFragment>())
	{
		StackableFragment->SetStackCount(Remainder);
	}
}

void UInv_InventoryComponent::Server_DropItem_Implementation(UInv_InventoryItem* Item, int32 StackCount)
{
	const int32 NewStackCount = Item->GetStackCount() - StackCount;
	if (NewStackCount <= 0)
	{
		this->InventoryList.RemoveEntry(Item);
	}
	else
	{
		Item->SetStackCount(NewStackCount);
	}
	
	this->SpawnDroppedItem(Item, StackCount);
}

void UInv_InventoryComponent::Server_ConsumeItem_Implementation(UInv_InventoryItem* Item)
{
	const int32 NewStackCount = Item->GetStackCount() - 1;
	if (NewStackCount <= 0)
	{
		this->InventoryList.RemoveEntry(Item);
	}
	else
	{
		Item->SetStackCount(NewStackCount);
	}
	
	if (FInv_ConsumableFragment* ConsumableFragment = Item->GetItemManifestMutable().GetFragmentByTypeMutable<FInv_ConsumableFragment>())
	{
		ConsumableFragment->OnConsume(this->OwningController.Get());
	}
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

void UInv_InventoryComponent::SpawnDroppedItem(UInv_InventoryItem* Item, int32 StackCount)
{
	const APawn* OwningPawn = this->OwningController->GetPawn();
	FVector Forward = OwningPawn->GetActorForwardVector();
	Forward = Forward.RotateAngleAxis(FMath::FRandRange(this->DropSpawnAngleMin, this->DropSpawnAngleMax), FVector::UpVector);
	FVector SpawnLocation = OwningPawn->GetActorLocation() + Forward * FMath::FRandRange(this->DropSpawnDistanceMin, this->DropSpawnDistanceMax);
	SpawnLocation.Z -= this->RelativeSpawnElevation;
	const FRotator Rotation = FRotator::ZeroRotator;
	
	FInv_ItemManifest& ItemManifest = Item->GetItemManifestMutable();
	if (FInv_StackableFragment* StackableFragment = ItemManifest.GetFragmentByTypeMutable<FInv_StackableFragment>())
	{
		StackableFragment->SetStackCount(StackCount);
	}
	ItemManifest.SpawnPickupActor(this, SpawnLocation, Rotation);
}

UInv_InventoryBase* UInv_InventoryComponent::GetInventoryMenu() const
{
	return this->InventoryMenu;
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



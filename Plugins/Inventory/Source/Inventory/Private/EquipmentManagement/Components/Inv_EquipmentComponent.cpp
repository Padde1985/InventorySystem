#include "EquipmentManagement/Components/Inv_EquipmentComponent.h"
#include "EquipmentManagement/EquipActor/Inv_EquipActor.h"
#include "GameFramework/Character.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Items/Fragments/Inv_ItemFragment.h"

// store owning mesh (actor with the equipment component)
void UInv_EquipmentComponent::SetOwningSkeletalMesh(USkeletalMeshComponent* OwningMesh)
{
	this->SkeletalMeshComponent = OwningMesh;
}

// define if the owner is a proxy or playable character
void UInv_EquipmentComponent::SetIsProxy(bool bProxy)
{
	this->bIsProxy = bProxy;
}

// set player controller for reference
void UInv_EquipmentComponent::InitializeOwner(APlayerController* PlayerController)
{
	if (IsValid(PlayerController))
	{
		this->OwningPlayerController = PlayerController;
	}
	this->InitInventoryComponent();
}

// Called when the game starts
void UInv_EquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	this->InitPlayerController();
}

// callback when item gets equipped
void UInv_EquipmentComponent::OnItemEquipped(UInv_InventoryItem* EquippedItem)
{
	if (!IsValid(EquippedItem) || !this->OwningPlayerController->HasAuthority()) return;
	
	FInv_ItemManifest& ItemManifest = EquippedItem->GetItemManifestMutable();
	FInv_EquipmentFragment* EquipmentFragment = ItemManifest.GetFragmentByTypeMutable<FInv_EquipmentFragment>();
	if (EquipmentFragment == nullptr) return;
	
	if (!this->bIsProxy) EquipmentFragment->OnEquip(this->OwningPlayerController.Get());
	
	if (!this->SkeletalMeshComponent.IsValid()) return;
	AInv_EquipActor* SpawnedActor = this->SpawnEquippedActor(EquipmentFragment, ItemManifest, this->SkeletalMeshComponent.Get());
	this->EquippedActors.Add(SpawnedActor);
}

// callback when item gets unequipped
void UInv_EquipmentComponent::OnItemUnequipped(UInv_InventoryItem* UnequippedItem)
{
	if (!IsValid(UnequippedItem) || !this->OwningPlayerController->HasAuthority()) return;
	
	FInv_ItemManifest& ItemManifest = UnequippedItem->GetItemManifestMutable();
	FInv_EquipmentFragment* EquipmentFragment = ItemManifest.GetFragmentByTypeMutable<FInv_EquipmentFragment>();
	if (EquipmentFragment == nullptr) return;
	
	if (!this->bIsProxy) EquipmentFragment->OnUnequip(this->OwningPlayerController.Get());
	
	this->RemoveEquippedActor(EquipmentFragment->GetEquipmentType());
}

// callback when pawn gets possessed by controller (can be delayed in network environment)
void UInv_EquipmentComponent::OnPossedPawnChange(APawn* OldPawn, APawn* NewPawn)
{
	if (ACharacter* OwnerCharacter = Cast<ACharacter>(this->OwningPlayerController->GetPawn()); IsValid(OwnerCharacter))
	{
		this->SkeletalMeshComponent = OwnerCharacter->GetMesh();
	}
	this->InitInventoryComponent();
}

// bind callback for equipping and unequipping items
void UInv_EquipmentComponent::InitInventoryComponent()
{
	this->InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(this->OwningPlayerController.Get());
	if (!this->InventoryComponent.IsValid()) return;
		
	if (!this->InventoryComponent->OnItemEquipped.IsAlreadyBound(this, &UInv_EquipmentComponent::OnItemEquipped))
	{
		this->InventoryComponent->OnItemEquipped.AddDynamic(this, &UInv_EquipmentComponent::OnItemEquipped);
	}
	
	if (!this->InventoryComponent->OnItemUnequipped.IsAlreadyBound(this, &UInv_EquipmentComponent::OnItemUnequipped))
	{
		this->InventoryComponent->OnItemUnequipped.AddDynamic(this, &UInv_EquipmentComponent::OnItemUnequipped);
	}
}

// spawn the actual item to be equipped (inventory item is just a placeholder for pickup)
AInv_EquipActor* UInv_EquipmentComponent::SpawnEquippedActor(FInv_EquipmentFragment* EquipmentFragment, const FInv_ItemManifest& Manifest, USkeletalMeshComponent* AttachMesh) const
{
	AInv_EquipActor* SpawnActor = EquipmentFragment->SpawnAttachedActor(AttachMesh);
	SpawnActor->SetEquipmentType(EquipmentFragment->GetEquipmentType());
	SpawnActor->SetOwner(GetOwner());
	EquipmentFragment->SetEquippedActor(SpawnActor);
	
	return SpawnActor;
}

// find the equipped item type (cloak, mask, weapon)
AInv_EquipActor* UInv_EquipmentComponent::FindEquippedActorByType(const FGameplayTag& Tag)
{
	TObjectPtr<AInv_EquipActor>* Actor = this->EquippedActors.FindByPredicate([&Tag](const AInv_EquipActor* EquippedActor)
	{
		return EquippedActor->GetEquipmentType().MatchesTagExact(Tag);
	});
	
	return Actor ? *Actor : nullptr;
}

// remove equipped item and destroy it (inventory item gets created to be dropped or put back into inventory)
void UInv_EquipmentComponent::RemoveEquippedActor(const FGameplayTag& Tag)
{
	if (AInv_EquipActor* Actor = this->FindEquippedActorByType(Tag); IsValid(Actor))
	{
		this->EquippedActors.Remove(Actor);
		Actor->Destroy();
	}
}

// set owning playercontroller
void UInv_EquipmentComponent::InitPlayerController()
{
	if (this->OwningPlayerController = Cast<APlayerController>(GetOwner()); this->OwningPlayerController.IsValid())
	{
		if (ACharacter* OwnerCharacter = Cast<ACharacter>(this->OwningPlayerController->GetPawn()); IsValid(OwnerCharacter))
		{
			this->OnPossedPawnChange(nullptr, OwnerCharacter);
		}
		else
		{
			this->OwningPlayerController->OnPossessedPawnChanged.AddDynamic(this, &UInv_EquipmentComponent::OnPossedPawnChange);
		}
	}
}
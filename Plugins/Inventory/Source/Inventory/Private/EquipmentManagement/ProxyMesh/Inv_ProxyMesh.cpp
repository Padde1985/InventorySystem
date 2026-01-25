#include "EquipmentManagement/ProxyMesh/Inv_ProxyMesh.h"
#include "EquipmentManagement/Components/Inv_EquipmentComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AInv_ProxyMesh::AInv_ProxyMesh()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(false);
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	this->Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	this->Mesh->SetupAttachment(RootComponent);
	
	this->EquipmentComponent = CreateDefaultSubobject<UInv_EquipmentComponent>("Equipment");
	this->EquipmentComponent->SetOwningSkeletalMesh(this->Mesh);
	this->EquipmentComponent->SetIsProxy(true);
}

// getter for the mesh of the proxy character
USkeletalMeshComponent* AInv_ProxyMesh::GetMesh() const
{
	return this->Mesh;
}

// Called when the game starts or when spawned
void AInv_ProxyMesh::BeginPlay()
{
	Super::BeginPlay();
	
	this->DelayedInitializeOwner();
}

// initialize owner (maybe delayed as engine initializes objects not always in the correct order)
void AInv_ProxyMesh::DelayedInitializeOwner()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		this->DelayedInitialization();
		return;
	}
	
	APlayerController* PC = World->GetFirstPlayerController();
	if (!IsValid(PC))
	{
		this->DelayedInitialization();
		return;
	}
	
	ACharacter* Character = Cast<ACharacter>(PC->GetPawn());
	if (!IsValid(Character))
	{
		this->DelayedInitialization();
		return;
	}
	
	USkeletalMeshComponent* SkeletalMeshComponent = Character->GetMesh();
	if (!IsValid(SkeletalMeshComponent))
	{
		this->DelayedInitialization();
		return;
	}
	
	this->SourceCharacterMesh = SkeletalMeshComponent;
	this->Mesh->SetSkeletalMesh(SkeletalMeshComponent->GetSkeletalMeshAsset());
	this->Mesh->SetAnimInstanceClass(SkeletalMeshComponent->GetAnimInstance()->GetClass());
	
	this->EquipmentComponent->InitializeOwner(PC);
}

// delayed initialization (gets called each tick until all requirements are met)
void AInv_ProxyMesh::DelayedInitialization()
{
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &AInv_ProxyMesh::DelayedInitializeOwner);
	GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
}
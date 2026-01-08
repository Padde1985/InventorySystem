#include "Player/Inv_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Widgets/HUD/Inv_HUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Interaction/Inv_HighlightableInterface.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"

AInv_PlayerController::AInv_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	this->TraceLength = 500.f;
	this->ItemTraceChannel = ECollisionChannel::ECC_GameTraceChannel1;
}

void AInv_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->TraceForItem();
}

void AInv_PlayerController::ToggleInventory()
{
	if (!this->InventoryComponent.IsValid()) return;
	this->InventoryComponent->ToggleInventoryMenu();
}

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->InventoryComponent = FindComponentByClass<UInv_InventoryComponent>();

	this->CreateHUDWidget();
}

void AInv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : this->DefaultIMCs)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(this->InputComponent);
	EnhancedInputComponent->BindAction(this->PrimaryInteractAction, ETriggerEvent::Started, this, &AInv_PlayerController::PrimaryInteract);
	EnhancedInputComponent->BindAction(this->ToggleInventoryAction, ETriggerEvent::Started, this, &AInv_PlayerController::ToggleInventory);
}

void AInv_PlayerController::PrimaryInteract()
{
	if (!this->ThisActor.IsValid()) return;
	
	UInv_ItemComponent* ItemComp = this->ThisActor->FindComponentByClass<UInv_ItemComponent>();
	if (!IsValid(ItemComp) || !this->InventoryComponent.IsValid()) return;
	
	this->InventoryComponent->TryAddItem(ItemComp);
}

void AInv_PlayerController::CreateHUDWidget()
{
	if (!IsLocalController()) return;

	this->HUDWidget = CreateWidget<UInv_HUDWidget>(this, this->HUDWidgetClass);
	if (IsValid(this->HUDWidget)) this->HUDWidget->AddToViewport();
}

void AInv_PlayerController::TraceForItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport)) return;

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2;
	FVector TraceStart;
	FVector Forward;
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;

	const FVector TraceEnd = TraceStart + Forward * this->TraceLength;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, this->ItemTraceChannel);
	this->LastActor = this->ThisActor;
	this->ThisActor = HitResult.GetActor();

	if (!this->ThisActor.IsValid() && IsValid(this->HUDWidget)) this->HUDWidget->HidePickupMessage();

	if (this->ThisActor == this->LastActor) return;
	if (this->ThisActor.IsValid())
	{
		if (UActorComponent* Highlightable = this->ThisActor->FindComponentByInterface(UInv_HighlightableInterface::StaticClass()); IsValid(Highlightable))
		{
			IInv_HighlightableInterface::Execute_Highlight(Highlightable);
		}

		UInv_ItemComponent* ItemComp = this->ThisActor->FindComponentByClass<UInv_ItemComponent>();
		if (!IsValid(ItemComp)) return;

		if (IsValid(this->HUDWidget)) this->HUDWidget->ShowPickupMessage(ItemComp->GetPickupMessage());
	}

	if (this->LastActor.IsValid())
	{
		if (UActorComponent* Highlightable = this->LastActor->FindComponentByInterface(UInv_HighlightableInterface::StaticClass()); IsValid(Highlightable))
		{
			IInv_HighlightableInterface::Execute_UnHighlight(Highlightable);
		}
	}
}

#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"

// Sets default values for this component's properties
UInv_InventoryComponent::UInv_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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

// Called when the game starts
void UInv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	this->ConstructInventory();
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



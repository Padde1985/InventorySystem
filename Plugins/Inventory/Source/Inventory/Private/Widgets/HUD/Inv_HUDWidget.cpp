#include "Widgets/HUD/Inv_HUDWidget.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Widgets/HUD/Inv_InfoMessage.h"

void UInv_HUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	UInv_InventoryComponent* InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	if (!IsValid(InventoryComponent))
	{
		InventoryComponent->InventorySpace.AddDynamic(this, &UInv_HUDWidget::OnNoRoom);
	}
}

void UInv_HUDWidget::OnNoRoom()
{
	if (!IsValid(this->InfoMessage)) return;
	
	this->InfoMessage->SetMessage(FText::FromString("No Room in Inventory"));
}

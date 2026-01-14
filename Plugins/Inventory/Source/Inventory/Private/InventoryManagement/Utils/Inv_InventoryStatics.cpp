#include "InventoryManagement/Utils/Inv_InventoryStatics.h"

#include "IDetailTreeNode.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Types/Inv_GridTypes.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"

UInv_InventoryComponent* UInv_InventoryStatics::GetInventoryComponent(const APlayerController* PlayerController)
{
	if (!IsValid(PlayerController)) return nullptr;
	
	UInv_InventoryComponent* InventoryComponent = PlayerController->FindComponentByClass<UInv_InventoryComponent>();
	return InventoryComponent;
}

EInv_ItemCategory UInv_InventoryStatics::GetItemCategoryByItemComponent(UInv_ItemComponent* ItemComponent)
{
	if (!IsValid(ItemComponent)) return EInv_ItemCategory::None;
	
	return ItemComponent->GetItemManifest().GetItemCategory();
}

void UInv_InventoryStatics::ItemHovered(APlayerController* PlayerController, UInv_InventoryItem* Item)
{
	UInv_InventoryComponent* InventoryComponent = GetInventoryComponent(PlayerController);
	if (!IsValid(InventoryComponent)) return;
	
	UInv_InventoryBase* InventoryBase = InventoryComponent->GetInventoryMenu();
	if (!IsValid(InventoryBase)) return;
	
	if (InventoryBase->HasHoverItem()) return;
	
	InventoryBase->OnItemHovered(Item);
}

void UInv_InventoryStatics::ItemUnhovered(APlayerController* PlayerController)
{
	UInv_InventoryComponent* InventoryComponent = GetInventoryComponent(PlayerController);
	if (!IsValid(InventoryComponent)) return;
	
	UInv_InventoryBase* InventoryBase = InventoryComponent->GetInventoryMenu();
	if (!IsValid(InventoryBase)) return;
	
	InventoryBase->OnItemUnhovered();
}

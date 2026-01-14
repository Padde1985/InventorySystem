#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryBase.generated.h"

class UInv_ItemComponent;

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_InventoryBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual FInv_SlotAvailabilityResult HasRoomForItem(UInv_ItemComponent *Component) const;
	virtual void OnItemHovered(UInv_InventoryItem *Item);
	virtual void OnItemUnhovered();
	virtual bool HasHoverItem() const;
};

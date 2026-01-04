#pragma once

#include "Inv_GridTypes.generated.h"

UENUM(BlueprintType)
enum class EInv_ItemCtageory : uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};
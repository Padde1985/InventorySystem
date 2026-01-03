#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inv_HighlightableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInv_HighlightableInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORY_API IInv_HighlightableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent) void Highlight();
	UFUNCTION(BlueprintNativeEvent) void UnHighlight();
};

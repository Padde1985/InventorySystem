#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Inv_WidgetUtils.generated.h"

class UWidget;

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_WidgetUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static int32 GetIndexByPosition(const FIntPoint& Position, const int32 Columns);
	static FIntPoint GetPositionByIndex(const int32 Index, const int32 Columns);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory") static FVector2D GetWidgetPosition(UWidget* Widget);
	UFUNCTION(BlueprintCallable) static bool IsWithinBounds(const FVector2D& BoundaryPos, const FVector2D& WidgetSize, const FVector2D& MousePos);
	UFUNCTION(BlueprintCallable, Category = "Inventory") static FVector2D GetWidgetSize(UWidget* Widget);
};

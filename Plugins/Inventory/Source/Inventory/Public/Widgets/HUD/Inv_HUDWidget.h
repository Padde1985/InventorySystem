#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_HUDWidget.generated.h"

class UInv_InfoMessage;

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_HUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory") void ShowPickupMessage(const FString& Message);
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory") void HidePickupMessage();
	
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UInv_InfoMessage> InfoMessage;

	UFUNCTION() void OnNoRoom();
};

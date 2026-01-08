#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_InfoMessage.generated.h"

class UTextBlock;

UCLASS(PrioritizeCategories="Inventory")
class INVENTORY_API UInv_InfoMessage : public UUserWidget
{
	GENERATED_BODY()
public:	
	UFUNCTION(BlueprintImplementableEvent) void ShowMessage();
	UFUNCTION(BlueprintImplementableEvent) void HideMessage();
	void SetMessage(const FText& Message);
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(meta=(BindWidget)) TObjectPtr<UTextBlock> TextMessage;
	UPROPERTY(EditAnywhere, Category = "Inventory") float MessageLifeTime = 3.f;
	
	FTimerHandle MessageTimer;
	bool bIsMessageActive = false;
};

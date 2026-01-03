#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Interaction/Inv_HighlightableInterface.h"
#include "Inv_HighlightableStaticMeshComp.generated.h"

UCLASS()
class INVENTORY_API UInv_HighlightableStaticMeshComp : public UStaticMeshComponent, public IInv_HighlightableInterface
{
	GENERATED_BODY()

public:
	virtual void Highlight_Implementation() override;
	virtual void UnHighlight_Implementation() override;

private:
	UPROPERTY(EditAnywhere, Category = "Inventory") TObjectPtr<UMaterialInterface> HighlightMaterial;
};

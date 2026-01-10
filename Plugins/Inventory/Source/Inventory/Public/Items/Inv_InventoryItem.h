#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "StructUtils/InstancedStruct.h"
#include "Inv_InventoryItem.generated.h"

UCLASS(PrioritizeCategories = ("Inventory"))
class INVENTORY_API UInv_InventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	void SetItemManifest(const FInv_ItemManifest& Manifest);
	const FInv_ItemManifest& GetItemManifest() const;
	FInv_ItemManifest& GetItemManifestMutable();
	virtual bool IsSupportedForNetworking() const override;
	bool IsStackable() const;
	int32 GetStackCount() const;
	void SetStackCount(int32 Count);
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (BaseStruct = "/Script/Inventory.Inv_ItemManifest"), Replicated) FInstancedStruct ItemManifest;
	UPROPERTY(Replicated) int32 TotalStackCount = 0;
};
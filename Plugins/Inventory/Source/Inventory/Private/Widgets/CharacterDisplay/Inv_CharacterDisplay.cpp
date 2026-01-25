#include "Widgets/CharacterDisplay/Inv_CharacterDisplay.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "EquipmentManagement/ProxyMesh/Inv_ProxyMesh.h"
#include "Kismet/GameplayStatics.h"

// callback for mouse button down (activate dragging)
FReply UInv_CharacterDisplay::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->CurrentPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer()); 
	this->LastPosition = this->CurrentPosition;
	this->bIsDragging = true;
	
	return FReply::Handled();
}

// callback for mouse button release (stop dragging)
FReply UInv_CharacterDisplay::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	this->bIsDragging = false;
	
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

// callback for moving mouse off the character screen in inventory
void UInv_CharacterDisplay::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	this->bIsDragging = false;
}

// initiate proxy mesh
void UInv_CharacterDisplay::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, AInv_ProxyMesh::StaticClass(), Actors);
	if (!Actors.IsValidIndex(0)) return;
	
	AInv_ProxyMesh* ProxyMesh = Cast<AInv_ProxyMesh>(Actors[0]);
	if (!IsValid(ProxyMesh)) return;
	
	this->Mesh = ProxyMesh->GetMesh();
}

// rotate character display
void UInv_CharacterDisplay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!this->bIsDragging) return;
	
	this->LastPosition = this->CurrentPosition;
	this->CurrentPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer());
	const float HorizontalDelta = this->LastPosition.X - this->CurrentPosition.X;
	
	if (!this->Mesh.IsValid()) return;
	
	this->Mesh->AddRelativeRotation(FRotator(0.f, HorizontalDelta, 0.f));
}
#include "Widgets/HUD/Inv_InfoMessage.h"
#include "Components/TextBlock.h"

// set message to be displayed in info message box
void UInv_InfoMessage::SetMessage(const FText& Message)
{
	this->TextMessage->SetText(Message);
	
	if (!this->bIsMessageActive)
	{
		this->ShowMessage();
	}
	this->bIsMessageActive = true;
	
	GetWorld()->GetTimerManager().SetTimer(this->MessageTimer, [this]()
	{
		this->HideMessage();
		this->bIsMessageActive = false;
	}, this->MessageLifeTime, false);
}

// initialize info message box
void UInv_InfoMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	this->TextMessage->SetText(FText::GetEmpty());
	this->HideMessage();
}
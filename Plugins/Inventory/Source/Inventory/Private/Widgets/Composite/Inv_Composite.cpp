#include "Widgets/Composite/Inv_Composite.h"
#include "Blueprint/WidgetTree.h"

void UInv_Composite::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	WidgetTree->ForEachWidget([this](UWidget* Widget)
	{
		if (UInv_CompositeBase* Composite = Cast<UInv_CompositeBase>(Widget); IsValid(Composite))
		{
			Composite->Collapse();
			this->Children.Add(Composite);
		}
	});
}

void UInv_Composite::ApplyFunction(FuncType Func)
{
	for (TObjectPtr<UInv_CompositeBase>& Child : this->Children)
	{
		Child->ApplyFunction(Func);
	}
}

void UInv_Composite::Collapse()
{
	for (TObjectPtr<UInv_CompositeBase>& Child : this->Children)
	{
		Child->Collapse();
	}
}

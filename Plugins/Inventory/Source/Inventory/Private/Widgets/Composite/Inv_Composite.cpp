#include "Widgets/Composite/Inv_Composite.h"
#include "Blueprint/WidgetTree.h"

// initialize all composites (widget elements in the item description)
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

// apply function gets called from item description widget
void UInv_Composite::ApplyFunction(FuncType Func)
{
	for (TObjectPtr<UInv_CompositeBase>& Child : this->Children)
	{
		Child->ApplyFunction(Func);
	}
}

// collapse all elements
void UInv_Composite::Collapse()
{
	for (TObjectPtr<UInv_CompositeBase>& Child : this->Children)
	{
		Child->Collapse();
	}
}

// getter for all children elements
TArray<UInv_CompositeBase*> UInv_Composite::GetChildren() const
{
	return this->Children;
}
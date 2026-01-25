#include "Widgets/Composite/Inv_Leaf.h"

// apply function, typically a lambda
void UInv_Leaf::ApplyFunction(FuncType Func)
{
	Func(this);
}

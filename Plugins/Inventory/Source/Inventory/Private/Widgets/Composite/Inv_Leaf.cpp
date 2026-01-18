#include "Widgets/Composite/Inv_Leaf.h"

void UInv_Leaf::ApplyFunction(FuncType Func)
{
	Func(this);
}

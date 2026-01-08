#include "Widgets/Utils/Inv_WidgetUtils.h"

int32 UInv_WidgetUtils::GetIndexByPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.Y * Columns + Position.X;
}

FIntPoint UInv_WidgetUtils::GetPositionByIndex(const int32 Index, const int32 Columns)
{
	return FIntPoint(Index % Columns, Index / Columns);
}

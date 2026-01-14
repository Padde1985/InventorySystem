#include "Widgets/Utils/Inv_WidgetUtils.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/Widget.h"

int32 UInv_WidgetUtils::GetIndexByPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.Y * Columns + Position.X;
}

FIntPoint UInv_WidgetUtils::GetPositionByIndex(const int32 Index, const int32 Columns)
{
	return FIntPoint(Index % Columns, Index / Columns);
}

FVector2D UInv_WidgetUtils::GetWidgetPosition(UWidget* Widget)
{
	const FGeometry Geometry = Widget->GetCachedGeometry();
	
	FVector2D PixelPos;
	FVector2D ViewportPos;
	USlateBlueprintLibrary::LocalToViewport(Widget, Geometry, USlateBlueprintLibrary::GetLocalTopLeft(Geometry), PixelPos, ViewportPos);
	
	return ViewportPos;
}

bool UInv_WidgetUtils::IsWithinBounds(const FVector2D& BoundaryPos, const FVector2D& WidgetSize, const FVector2D& MousePos)
{
	return MousePos.X >= BoundaryPos.X && MousePos.X <= (BoundaryPos.X + WidgetSize.X) && MousePos.Y >= BoundaryPos.Y && MousePos.Y <= (BoundaryPos.Y + WidgetSize.Y);
}

FVector2D UInv_WidgetUtils::GetWidgetSize(UWidget* Widget)
{
	return Widget->GetCachedGeometry().GetLocalSize();
}

FVector2D UInv_WidgetUtils::GetClampedWidgetPosition(const FVector2D& Boundary, const FVector2D& WidgetSize, const FVector2D& MousePos)
{
	FVector2D ClampedPos = MousePos;
	
	if (MousePos.X + WidgetSize.X > Boundary.X) //exceeds the right edge of the screen
	{
		ClampedPos.X = Boundary.X - WidgetSize.X;
	}
	if (MousePos.X < 0.f) // exceeds the left edge
	{
		ClampedPos.X = 0.f;
	}
	
	if (MousePos.Y + WidgetSize.Y > Boundary.Y) // exceeds the bottom edge
	{
		ClampedPos.Y = Boundary.Y - WidgetSize.Y;
	}
	if (MousePos.Y < 0.f) // exceeds the top edge
	{
		ClampedPos.Y = 0.f;
	}
	
	return ClampedPos;
}

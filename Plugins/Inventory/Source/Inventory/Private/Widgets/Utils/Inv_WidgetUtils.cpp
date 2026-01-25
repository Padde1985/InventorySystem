#include "Widgets/Utils/Inv_WidgetUtils.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/Widget.h"

// get the grid index by mouse cursor position
int32 UInv_WidgetUtils::GetIndexByPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.Y * Columns + Position.X;
}

// get the screen position for a given slot
FIntPoint UInv_WidgetUtils::GetPositionByIndex(const int32 Index, const int32 Columns)
{
	return FIntPoint(Index % Columns, Index / Columns);
}

// getter for a widget position on screen
FVector2D UInv_WidgetUtils::GetWidgetPosition(UWidget* Widget)
{
	const FGeometry Geometry = Widget->GetCachedGeometry();
	
	FVector2D PixelPos;
	FVector2D ViewportPos;
	USlateBlueprintLibrary::LocalToViewport(Widget, Geometry, USlateBlueprintLibrary::GetLocalTopLeft(Geometry), PixelPos, ViewportPos);
	
	return ViewportPos;
}

// check if something is wihtin bounds of widget
bool UInv_WidgetUtils::IsWithinBounds(const FVector2D& BoundaryPos, const FVector2D& WidgetSize, const FVector2D& MousePos)
{
	return MousePos.X >= BoundaryPos.X && MousePos.X <= (BoundaryPos.X + WidgetSize.X) && MousePos.Y >= BoundaryPos.Y && MousePos.Y <= (BoundaryPos.Y + WidgetSize.Y);
}

// getter for widget size
FVector2D UInv_WidgetUtils::GetWidgetSize(UWidget* Widget)
{
	return Widget->GetCachedGeometry().GetLocalSize();
}

// clamp mouse position to stay within boundaries
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
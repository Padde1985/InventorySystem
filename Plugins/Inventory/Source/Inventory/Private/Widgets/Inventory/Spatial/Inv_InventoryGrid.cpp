#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"

#include "Inventory.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "InventoryManagement/Utils/Inv_InventoryStatics.h"
#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Widgets/Utils/Inv_WidgetUtils.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Items/Fragments/Inv_FragmentTags.h"
#include "Items/Fragments/Inv_ItemFragment.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"
#include "Widgets/Inventory/SlottedItems/Inv_SlottedItem.h"

void UInv_InventoryGrid::AddItem(UInv_InventoryItem* InventoryItem)
{
    if (!this->MatchesCategory(InventoryItem)) return;
    
    FInv_SlotAvailabilityResult Result = this->HasRoomForItem(InventoryItem->GetItemManifest());
    this->AddItemToIndices(Result, InventoryItem);
}

EInv_ItemCategory UInv_InventoryGrid::GetItemCategory() const
{
    return this->ItemCategory;
}

void UInv_InventoryGrid::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    this->ConstructGrid();
    this->InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
    this->InventoryComponent->OnItemAdded.AddDynamic(this, &UInv_InventoryGrid::AddItem);
    this->InventoryComponent->OnStackChange.AddDynamic(this, &UInv_InventoryGrid::AddStacks);
}

FInv_SlotAvailabilityResult UInv_InventoryGrid::HasRoomForItem(const UInv_ItemComponent* Component)
{
    return this->HasRoomForItem(Component->GetItemManifest());
}

FInv_SlotAvailabilityResult UInv_InventoryGrid::HasRoomForItem(const UInv_InventoryItem* Item)
{
    return this->HasRoomForItem(Item->GetItemManifest());
}

FInv_SlotAvailabilityResult UInv_InventoryGrid::HasRoomForItem(const FInv_ItemManifest& Manifest)
{
    FInv_SlotAvailabilityResult Result;
    
    const FInv_StackableFragment* StackableFragment = Manifest.GetFragmentByType<FInv_StackableFragment>();
    Result.bIsStackable = StackableFragment != nullptr;
    
    const int32 MaxStackSize = Result.bIsStackable ? StackableFragment->GetMaxStackSize() : 1;
    int32 AmountToFill = Result.bIsStackable ? StackableFragment->GetStackCount() : 1;
    
    TSet<int32> CheckedIndices;
    for (const TObjectPtr<UInv_GridSlot>& GridSlot : this->GridSlots)
    {
        if (AmountToFill == 0) break;
        
        if (CheckedIndices.Contains(GridSlot->GetTileIndex())) continue;
        
        const FInv_GridFragment* GridFragment = Manifest.GetFragmentByType<FInv_GridFragment>();
        const FIntPoint Dimensions = GridFragment ? GridFragment->GetGridSize() : FIntPoint(1,1);
        
        if (!this->IsInGridBounds(GridSlot->GetTileIndex(), Dimensions)) continue;
            
        TSet<int32> TentativelyClaimed;
        if (!this->HasRoomAtIndex(GridSlot, Dimensions, CheckedIndices, TentativelyClaimed, Manifest.GetItemType(), MaxStackSize)) continue;
        
        const int32 AmountToFillInSlot = this->DetermineFillAmountForSLot(Result.bIsStackable, MaxStackSize, AmountToFill, GridSlot);
        if (AmountToFillInSlot == 0) continue;
        
        CheckedIndices.Append(TentativelyClaimed);
        
        Result.TotalRoomToFill += AmountToFillInSlot;
        Result.SlotAvailabilities.Emplace(
                FInv_SlotAvailability{
                    GridSlot->GetInventoryItem().IsValid() ? GridSlot->GetUpperLeftIndex() : GridSlot->GetTileIndex(), 
                    Result.bIsStackable ? AmountToFillInSlot : 0,
                    GridSlot->GetInventoryItem().IsValid()
                }
        );
        AmountToFill -= AmountToFillInSlot;
        Result.Remainder = AmountToFill;
        if (AmountToFill == 0) return Result;
    }
    
    return Result;
}

void UInv_InventoryGrid::AddItemToIndices(const FInv_SlotAvailabilityResult& Result, UInv_InventoryItem* NewItem)
{
    for (const FInv_SlotAvailability& Availability : Result.SlotAvailabilities)
    {
        this->AddItemAtIndex(NewItem, Availability.Index, Result.bIsStackable, Availability.AmountToFill);
        this->UpdateGridSlots(NewItem, Availability.Index, Result.bIsStackable, Availability.AmountToFill);
    }
}

FVector2D UInv_InventoryGrid::GetDrawSize(const FInv_GridFragment* GridFragment) const
{
    const float IconTileWidth = this->TileSize - GridFragment->GetGridPadding() * 2; //*2 as we have padding on both sides
    return GridFragment->GetGridSize() * IconTileWidth;
}

void UInv_InventoryGrid::SetSlottedItemImage(const UInv_SlottedItem* SlottedItem, const FInv_GridFragment* GridFragment, const FInv_ImageFragment* ImageFragment) const
{
    FSlateBrush Brush;
    Brush.SetResourceObject(ImageFragment->GetIcon());
    Brush.DrawAs = ESlateBrushDrawType::Image;
    Brush.ImageSize = this->GetDrawSize(GridFragment);
    SlottedItem->SetImageBrush(Brush);
}

void UInv_InventoryGrid::AddItemAtIndex(UInv_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount)
{
    const FInv_GridFragment* GridFragment = UInv_InventoryStatics::GetFragment<FInv_GridFragment>(Item, FragmentTags::GridFragment);
    const FInv_ImageFragment* ImageFragment = UInv_InventoryStatics::GetFragment<FInv_ImageFragment>(Item, FragmentTags::IconFragment);
    if (!GridFragment || !ImageFragment) return;
    
    UInv_SlottedItem* SlottedItem = this->CreateSlottedItem(Item, bStackable, StackAmount, GridFragment, ImageFragment, Index);
    this->AddSlottedItemToCanvas(Index, GridFragment, SlottedItem);
    
    this->SlottedItems.Add(Index, SlottedItem);
}

UInv_SlottedItem* UInv_InventoryGrid::CreateSlottedItem(UInv_InventoryItem* Item, const bool bStackable, const int32 StackAmount, const FInv_GridFragment* GridFragment, const FInv_ImageFragment* ImageFragment, const int32 Index)
{
    UInv_SlottedItem* SlottedItem = CreateWidget<UInv_SlottedItem>(GetOwningPlayer(), this->SlottedItemClass);
    SlottedItem->SetInventoryItem(Item);
    this->SetSlottedItemImage(SlottedItem, GridFragment, ImageFragment);
    SlottedItem->SetGridIndex(Index);
    SlottedItem->SetIsStackable(bStackable);
    
    const int32 StackUpdateAmount = bStackable ? StackAmount : 0;
    SlottedItem->UpdateStackCount(StackUpdateAmount);
    SlottedItem->OnSlottedItemClicked.AddDynamic(this, &ThisClass::OnSlottedItemClicked);
    
    return SlottedItem;
}

void UInv_InventoryGrid::AddSlottedItemToCanvas(const int32 Index, const FInv_GridFragment* GridFragment, UInv_SlottedItem* SlottedItem) const
{
    this->CanvasPanel->AddChild(SlottedItem);
    UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(SlottedItem);
    CanvasSlot->SetSize(this->GetDrawSize(GridFragment));
    const FVector2D DrawPos = UInv_WidgetUtils::GetPositionByIndex(Index, Columns) * this->TileSize;
    //const FVector2D DrawPosWithPadding = DrawPos + FVector2D(GridFragment->GetGridPadding());
    FVector2D DrawPosWithPadding;
    DrawPosWithPadding.X = DrawPos.X + GridFragment->GetGridPadding() * GridFragment->GetGridSize().X;
    DrawPosWithPadding.Y = DrawPos.Y + GridFragment->GetGridPadding() * GridFragment->GetGridSize().Y;
    CanvasSlot->SetPosition(DrawPosWithPadding);
}

void UInv_InventoryGrid::UpdateGridSlots(UInv_InventoryItem* NewItem, const int32 Index, bool bStackableItem, const int32 StackAmount)
{
    check(this->GridSlots.IsValidIndex(Index));
    
    if (bStackableItem)
    {
       this->GridSlots[Index]->SetStackCount(StackAmount); 
    }
    
    const FInv_GridFragment* GridFragment = UInv_InventoryStatics::GetFragment<FInv_GridFragment>(NewItem, FragmentTags::GridFragment);    
    const FIntPoint Dimensions = GridFragment ? GridFragment->GetGridSize() : FIntPoint(1, 1);
    
    UInv_InventoryStatics::ForEach2D(this->GridSlots, Index, Dimensions, this->Columns, [&](UInv_GridSlot* GridSlot)
    {
        GridSlot->SetInventoryItem(NewItem);
        GridSlot->SetUpperLeftIndex(Index);
        GridSlot->SetOccupiedTexture();
        GridSlot->SetAvailable(false);
    });
}

bool UInv_InventoryGrid::HasRoomAtIndex(const UInv_GridSlot* GridSlot, const FIntPoint& Dimensions, const TSet<int32>& CheckedIndices, TSet<int32>& OutTentativelyClaimed, const FGameplayTag& ItemTag, const int32 MaxStackSize)
{
    bool bHasRoomAtIndex = true;
    
    UInv_InventoryStatics::ForEach2D(this->GridSlots, GridSlot->GetTileIndex(), Dimensions, this->Columns, [&](const UInv_GridSlot* SubGridSlot)
    {
        if (this->CheckSlotConstraints(SubGridSlot, CheckedIndices, OutTentativelyClaimed, GridSlot, ItemTag, MaxStackSize))
        {
            OutTentativelyClaimed.Add(SubGridSlot->GetTileIndex());
        }
        else
        {
            bHasRoomAtIndex = false;
        }
    });
    
    return bHasRoomAtIndex;
}

bool UInv_InventoryGrid::CheckSlotConstraints(const UInv_GridSlot* SubGridSlot, const TSet<int32>& CheckedIndices, TSet<int32>& OutTentativelyClaimed, const UInv_GridSlot* GridSlot, const FGameplayTag& ItemTag, const int32 MaxStackSize) const
{
    if (CheckedIndices.Contains(SubGridSlot->GetTileIndex())) return false;
    
    if (!SubGridSlot->GetInventoryItem().IsValid())
    {
        OutTentativelyClaimed.Add(SubGridSlot->GetTileIndex());
        return true;
    }
    
    if (SubGridSlot->GetUpperLeftIndex() != GridSlot->GetTileIndex()) return false;
    
    UInv_InventoryItem* SubItem = SubGridSlot->GetInventoryItem().Get();
    if (!SubItem->IsStackable()) return false;
    
    if (!SubItem->GetItemManifest().GetItemType().MatchesTagExact(ItemTag)) return false;
    
    if (GridSlot->GetStackCount() >= MaxStackSize) return false;
    
    return true;
}

bool UInv_InventoryGrid::IsInGridBounds(const int32 StartIndex, const FIntPoint& ItemDimensions) const
{
    if (StartIndex < 0 || StartIndex >= this->GridSlots.Num()) return false;
    
    const int32 EndColumn = (StartIndex % this->Columns) + ItemDimensions.X;
    const int32 EndRow = (StartIndex / this->Columns) + ItemDimensions.Y;
    
    return EndColumn <= this->Columns && EndRow <= this->Rows;
}

int32 UInv_InventoryGrid::DetermineFillAmountForSLot(const bool bStackable, const int32 MaxStackSize, const int32 Amount, const UInv_GridSlot* GridSlot) const
{
    int32 StackCount;
    if (const int32 UpperLeftIndex = GridSlot->GetUpperLeftIndex(); UpperLeftIndex != INDEX_NONE)
    {
        StackCount = this->GridSlots[UpperLeftIndex]->GetStackCount();
    }
    else
    {
       StackCount = GridSlot->GetStackCount();
    }
    const int32 RoomInSlot = MaxStackSize - StackCount;
    
    return bStackable ? FMath::Min(Amount, RoomInSlot) : 1;
}

bool UInv_InventoryGrid::IsRightCLick(const FPointerEvent& MouseEvent) const
{
    return MouseEvent.GetEffectingButton() == EKeys::RightMouseButton;
}

bool UInv_InventoryGrid::IsLeftCLick(const FPointerEvent& MouseEvent) const
{
    return MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton;
}

void UInv_InventoryGrid::Pickup(UInv_InventoryItem* ClickedItem, const int32 GridIndex)
{
    this->AssignHoverItem(ClickedItem, GridIndex, GridIndex);
    this->RemoveItemFromGrid(ClickedItem, GridIndex);
}

void UInv_InventoryGrid::AssignHoverItem(UInv_InventoryItem* Item)
{
    if (!IsValid(this->HoverItem))
    {
        this->HoverItem = CreateWidget<UInv_HoverItem>(GetOwningPlayer(), this->HoverItemClass);
    }
    
    const FInv_GridFragment* GridFragment = UInv_InventoryStatics::GetFragment<FInv_GridFragment>(Item, FragmentTags::GridFragment);
    const FInv_ImageFragment* ImageFragment = UInv_InventoryStatics::GetFragment<FInv_ImageFragment>(Item, FragmentTags::IconFragment);
    if (!GridFragment || !ImageFragment) return;
    
    const FVector2D DrawSize = this->GetDrawSize(GridFragment);
    FSlateBrush IconBrush;
    IconBrush.SetResourceObject(ImageFragment->GetIcon());
    IconBrush.DrawAs = ESlateBrushDrawType::Image;
    IconBrush.ImageSize = DrawSize * UWidgetLayoutLibrary::GetViewportScale(this);
    
    this->HoverItem->SetImageBrush(IconBrush);
    this->HoverItem->SetGridDimensions(GridFragment->GetGridSize());
    this->HoverItem->SetInventoryItem(Item);
    this->HoverItem->SetIsStackable(Item->IsStackable());
    
    GetOwningPlayer()->SetMouseCursorWidget(EMouseCursor::Default, this->HoverItem);
}

void UInv_InventoryGrid::AssignHoverItem(UInv_InventoryItem* Item, const int32 GridIndex, const int32 PreviousGridIndex)
{
    this->AssignHoverItem(Item);
    
    this->HoverItem->SetPreviousGridIndex(PreviousGridIndex);
    this->HoverItem->UpdateStackCount(Item->IsStackable() ? this->GridSlots[GridIndex]->GetStackCount() : 0);
}

void UInv_InventoryGrid::RemoveItemFromGrid(UInv_InventoryItem* Item, const int32 GridIndex)
{
    const FInv_GridFragment* GridFragment = UInv_InventoryStatics::GetFragment<FInv_GridFragment>(Item, FragmentTags::GridFragment);
    if (!GridFragment) return;
    
    UInv_InventoryStatics::ForEach2D(this->GridSlots, GridIndex, GridFragment->GetGridSize(), this->Columns, [&](UInv_GridSlot* GridSlot)
    {
        GridSlot->SetInventoryItem(nullptr);
        GridSlot->SetUpperLeftIndex(INDEX_NONE);
        GridSlot->SetUnoccupiedTexture();
        GridSlot->SetAvailable(true);
        GridSlot->SetStackCount(0);
    });
    
    if (this->SlottedItems.Contains(GridIndex))
    {
        TObjectPtr<UInv_SlottedItem> SlottedItem;
        this->SlottedItems.RemoveAndCopyValue(GridIndex, SlottedItem);
        SlottedItem->RemoveFromParent();
    }
}

void UInv_InventoryGrid::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    
    const FVector2D CanvasPos = UInv_WidgetUtils::GetWidgetPosition(this->CanvasPanel);
    const FVector2D MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer());
    
    if (this->CursorExitedCanvas(CanvasPos, UInv_WidgetUtils::GetWidgetSize(this->CanvasPanel), MousePos))
    {
        return;
    }
    
    this->UpdateTileParameters(CanvasPos, MousePos);
}

void UInv_InventoryGrid::UpdateTileParameters(const FVector2D& CanvasPosition, const FVector2D& MousePosition)
{
    if (!this->bMouseWithinCanvas) return;
    
    const FIntPoint HoveredTileCoordinates = this->CalculcateHoveredCoordinates(CanvasPosition, MousePosition);
    
    this->LastTileParameters = this->TileParameters;
    this->TileParameters.TileCoordinates = HoveredTileCoordinates;
    this->TileParameters.TileIndex = UInv_WidgetUtils::GetIndexByPosition(HoveredTileCoordinates, this->Columns);
    this->TileParameters.TileQuadrant = this->CalculateTileQuadrant(CanvasPosition, MousePosition);
    
   this->OnTileParametersUpdated(this->TileParameters);
}

FIntPoint UInv_InventoryGrid::CalculcateHoveredCoordinates(const FVector2D& CanvasPosition, const FVector2D& MousePosition) const
{
    return FIntPoint {
        static_cast<int32>(FMath::FloorToInt((MousePosition.X - CanvasPosition.X) / this->TileSize)),
        static_cast<int32>(FMath::FloorToInt((MousePosition.Y - CanvasPosition.Y) / this->TileSize))
    };
}

EInv_TileQuadrant UInv_InventoryGrid::CalculateTileQuadrant(const FVector2D& CanvasPosition, const FVector2D& MousePosition) const
{
    const float TileLocalX = FMath::Fmod((MousePosition.X - CanvasPosition.X), this->TileSize);
    const float TileLocalY = FMath::Fmod((MousePosition.Y - CanvasPosition.Y), this->TileSize);
    const bool bIsTop = TileLocalY < this->TileSize / 2.f; //Top if Y is in the upper half
    const bool bIsLeft = TileLocalX < this->TileSize / 2.f; //Top if Y is in the left half
    
    EInv_TileQuadrant TileQuadrant = EInv_TileQuadrant::None;
    if (bIsLeft && bIsTop) TileQuadrant = EInv_TileQuadrant::TopLeft;
    else if (!bIsLeft && bIsTop) TileQuadrant = EInv_TileQuadrant::TopRight;
    else if (bIsLeft && !bIsTop) TileQuadrant = EInv_TileQuadrant::BottomLeft;
    else if (!bIsLeft && !bIsTop) TileQuadrant = EInv_TileQuadrant::BottomRight;
    
    return TileQuadrant;
}

void UInv_InventoryGrid::OnTileParametersUpdated(const FInv_TileParameters& Params)
{
    if (!IsValid(this->HoverItem)) return;
    
    const FIntPoint Dimensions = this->HoverItem->GetGridDimension();
    const FIntPoint StartingCoordinate = this->CalculateStartingCoordinate(Params.TileCoordinates, Dimensions, Params.TileQuadrant);
    this->ItemDropIndex = UInv_WidgetUtils::GetIndexByPosition(StartingCoordinate, this->Columns);
    
    this->CurrentQueryResult = this->CheckHoverPosition(StartingCoordinate, Dimensions);
    
    if (this->CurrentQueryResult.bHasSpace)
    {
        this->HighlightSlots(this->ItemDropIndex, Dimensions);
        return;
    }
    this->UnHighlightSlots(this->LastHighlightedIndex, this->LastHighlightedDimensions);
    
    if (this->CurrentQueryResult.ValidItem.IsValid() && this->GridSlots.IsValidIndex(this->CurrentQueryResult.UpperLeftIndex))
    {
        const FInv_GridFragment* GridFragment = UInv_InventoryStatics::GetFragment<FInv_GridFragment>(this->CurrentQueryResult.ValidItem.Get(), FragmentTags::GridFragment);
        if (!GridFragment) return;
        
        this->ChangeHoverType(this->CurrentQueryResult.UpperLeftIndex, GridFragment->GetGridSize(), EInv_GridSlotState::GrayedOut);
    }
}

FIntPoint UInv_InventoryGrid::CalculateStartingCoordinate(const FIntPoint& Coordinate, const FIntPoint& Dimensions, const EInv_TileQuadrant Quadrant) const
{
    const int32 HasEvenWidth = Dimensions.X % 2 == 0 ? 1 : 0;
    const int32 HasEvenHeight = Dimensions.Y % 2 == 0 ? 1 : 0;
    
    FIntPoint StartingCoordinate;
    StartingCoordinate.X = Coordinate.X - FMath::FloorToInt(0.5f * Dimensions.X);
    StartingCoordinate.Y = Coordinate.Y - FMath::FloorToInt(0.5f * Dimensions.Y);
    
    switch (Quadrant)
    {
        case EInv_TileQuadrant::TopLeft:
            // nothing to do            
            break;
        case EInv_TileQuadrant::TopRight:
            StartingCoordinate.X += HasEvenWidth;
            break;
        case EInv_TileQuadrant::BottomLeft:
            StartingCoordinate.Y += HasEvenHeight;
            break;
        case EInv_TileQuadrant::BottomRight:
            StartingCoordinate.X += HasEvenWidth;
            StartingCoordinate.Y += HasEvenHeight;
            break;
        case EInv_TileQuadrant::None:
            UE_LOG(LogInventory, Error, TEXT("Invalid Quadrant"));
            return FIntPoint (-1, -1);
    }
    
    return StartingCoordinate;
}

FInv_SpaceQueryResult UInv_InventoryGrid::CheckHoverPosition(const FIntPoint& Position, const FIntPoint& Dimensions)
{
    FInv_SpaceQueryResult Result;
    
    if (!this->IsInGridBounds(UInv_WidgetUtils::GetIndexByPosition(Position, this->Columns), Dimensions)) return Result;
    
    Result.bHasSpace = true;
    
    TSet<int32> OccupiedUpperLeftIndices;
    UInv_InventoryStatics::ForEach2D(this->GridSlots, UInv_WidgetUtils::GetIndexByPosition(Position, this->Columns), Dimensions, this->Columns, [&](const UInv_GridSlot* HoverSlot)
    {
        if (HoverSlot->GetInventoryItem().IsValid())
        {
            OccupiedUpperLeftIndices.Add(HoverSlot->GetUpperLeftIndex());
            Result.bHasSpace = false;
            if (OccupiedUpperLeftIndices.Num() > 1) return; // no need to continue checking if there is already one other item found
        }
    });
    
    if (OccupiedUpperLeftIndices.Num() == 1)
    {
        const int32 Index = *OccupiedUpperLeftIndices.CreateConstIterator();
        Result.ValidItem = this->GridSlots[Index]->GetInventoryItem();
        Result.UpperLeftIndex = Index;
    }
    
    return Result;
}

bool UInv_InventoryGrid::CursorExitedCanvas(const FVector2D& CanvasPos, const FVector2D& CanvasSize, const FVector2D& Location)
{
    this->bLastMouseWithinCanvas = this->bMouseWithinCanvas;
    this->bMouseWithinCanvas = UInv_WidgetUtils::IsWithinBounds(CanvasPos, CanvasSize, Location);
    
    if (!this->bMouseWithinCanvas && this->bLastMouseWithinCanvas)
    {
        this->UnHighlightSlots(this->LastHighlightedIndex, this->LastHighlightedDimensions);
        return true;
    }
    
    return false;
}

void UInv_InventoryGrid::HighlightSlots(const int32 Index, const FIntPoint& Dimensions)
{
    if (!this->bMouseWithinCanvas) return;
    
    this->UnHighlightSlots(this->LastHighlightedIndex, this->LastHighlightedDimensions);
    
    UInv_InventoryStatics::ForEach2D(this->GridSlots, Index, Dimensions, this->Columns, [&](UInv_GridSlot* HoverSlot)
    {
        HoverSlot->SetOccupiedTexture();
    });
    
    this->LastHighlightedDimensions = Dimensions;
    this->LastHighlightedIndex = Index;
}

void UInv_InventoryGrid::UnHighlightSlots(const int32 Index, const FIntPoint& Dimensions)
{
    UInv_InventoryStatics::ForEach2D(this->GridSlots, Index, Dimensions, this->Columns, [&](UInv_GridSlot* HoverSlot)
    {
        if (HoverSlot->GetAvailable())
        {
            HoverSlot->SetUnoccupiedTexture();
        }
        else
        {
            HoverSlot->SetOccupiedTexture();
        }
    });
}

void UInv_InventoryGrid::ChangeHoverType(const int32 Index, const FIntPoint& Dimensions, EInv_GridSlotState State)
{
    this->UnHighlightSlots(this->LastHighlightedIndex, this->LastHighlightedDimensions);
    
    UInv_InventoryStatics::ForEach2D(this->GridSlots, Index, Dimensions, this->Columns, [State](UInv_GridSlot* HoverSlot)
    {
        switch (State)
        {
            case EInv_GridSlotState::Occupied:
                HoverSlot->SetOccupiedTexture();
                break;
            case EInv_GridSlotState::Unoccupied:
                HoverSlot->SetUnoccupiedTexture();
                break;
            case EInv_GridSlotState::GrayedOut:
                HoverSlot->SetGrayedOutTexture();
                break;
            case EInv_GridSlotState::Selected:
                HoverSlot->SetSelectedTexture();
                break;
        }
    });
    
    this->LastHighlightedIndex = Index;
    this->LastHighlightedDimensions = Dimensions;
}

void UInv_InventoryGrid::AddStacks(const FInv_SlotAvailabilityResult& Result)
{
    if (!MatchesCategory(Result.InventoryItem.Get())) return;
    
    for (const FInv_SlotAvailability& Availability : Result.SlotAvailabilities)
    {
        if (Availability.bItemAtIndex)
        {
            const TObjectPtr<UInv_SlottedItem>& SlottedItem = this->SlottedItems.FindChecked(Availability.Index);
            const TObjectPtr<UInv_GridSlot>& GridSlot = this->GridSlots[Availability.Index];
            SlottedItem->UpdateStackCount(GridSlot->GetStackCount() + Availability.AmountToFill);
            GridSlot->SetStackCount(GridSlot->GetStackCount() + Availability.AmountToFill);
        }
        else
        {
            this->AddItemAtIndex(Result.InventoryItem.Get(), Availability.Index, Result.bIsStackable, Availability.AmountToFill);
            this->UpdateGridSlots(Result.InventoryItem.Get(), Availability.Index, Result.bIsStackable, Availability.AmountToFill);
        }
    }
}

void UInv_InventoryGrid::OnSlottedItemClicked(int32 GridIndex, const FPointerEvent& MouseEvent)
{
    check(this->GridSlots.IsValidIndex(GridIndex));
    
    UInv_InventoryItem* ClickedItem = this->GridSlots[GridIndex]->GetInventoryItem().Get();
    
    if (!IsValid(this->HoverItem) && this->IsLeftCLick(MouseEvent))
    {
        this->Pickup(ClickedItem, GridIndex);
    }
}

void UInv_InventoryGrid::ConstructGrid()
{
    this->GridSlots.Reserve(this->Rows * this->Columns);
    
    for (int32 i = 0; i < this->Rows; i++)
    {
        for (int32 j = 0; j < this->Columns; j++)
        {
            UInv_GridSlot* GridSlot = CreateWidget<UInv_GridSlot>(this, this->GridSlotClass);
            this->CanvasPanel->AddChild(GridSlot);
            const FIntPoint TilePosition(j, i);
            GridSlot->SetTileIndex(UInv_WidgetUtils::GetIndexByPosition(FIntPoint(j,i), this->Columns));
            
            UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
            CanvasSlot->SetSize(FVector2D(this->TileSize));
            CanvasSlot->SetPosition(TilePosition * this->TileSize);
            
            this->GridSlots.Add(GridSlot);
        }
    }
}

bool UInv_InventoryGrid::MatchesCategory(const UInv_InventoryItem* Item) const
{
    return Item->GetItemManifest().GetItemCategory() == this->ItemCategory;
}
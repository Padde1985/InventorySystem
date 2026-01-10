#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"
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
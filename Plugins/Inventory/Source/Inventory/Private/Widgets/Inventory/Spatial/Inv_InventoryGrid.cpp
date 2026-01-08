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
    Result.TotalRoomToFill = 1;
    
    FInv_SlotAvailability SlotAvailability;
    SlotAvailability.AmountToFill = 1;
    SlotAvailability.Index = 0;
    Result.SlotAvailabilities.Add(MoveTemp(SlotAvailability)); //move the actual structure values inside the array rather than creating a copy of it
    
    return Result;
}

void UInv_InventoryGrid::AddItemToIndices(const FInv_SlotAvailabilityResult& Result, UInv_InventoryItem* NewItem)
{
    for (const FInv_SlotAvailability& Availability : Result.SlotAvailabilities)
    {
        this->AddItemAtIndex(NewItem, Availability.Index, Result.bIsStackable, Availability.AmountToFill);
        this->UpdateGridSlots(NewItem, Availability.Index);
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

void UInv_InventoryGrid::UpdateGridSlots(UInv_InventoryItem* NewItem, const int32 Index)
{
    check(this->GridSlots.IsValidIndex(Index));
    
    const FInv_GridFragment* GridFragment = UInv_InventoryStatics::GetFragment<FInv_GridFragment>(NewItem, FragmentTags::GridFragment);
    if (!GridFragment) return;
    
    const FIntPoint Dimensions = GridFragment ? GridFragment->GetGridSize() : FIntPoint(1, 1);
    UInv_InventoryStatics::ForEach2D(this->GridSlots, Index, Dimensions, this->Columns, [](UInv_GridSlot* GridSlot)
    {
        GridSlot->SetOccupiedTexture();
    });
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
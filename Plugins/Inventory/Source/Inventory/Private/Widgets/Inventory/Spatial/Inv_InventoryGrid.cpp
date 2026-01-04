#include "Widgets/Inventory/Spatial/Inv_InventoryGrid.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Widgets/Utils/Inv_WidgetUtils.h"

EInv_ItemCtageory UInv_InventoryGrid::GetItemCtageory() const
{
    return this->ItemCategory;
}

void UInv_InventoryGrid::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    this->ConstructGrid();
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

/// @brief Инструмент создания описания игрового предмета
class KCItemBuilder
{
    private EntityAI item;

    ref KCSaveItem ItemData;
    
    /// @brief Создание построителя данных о предмете
    /// @param targetItem игровой предмет кототорый нужно сохранить
    void KCItemBuilder(EntityAI targetItem)
    {
        item = targetItem;
        ItemData = new KCSaveItem();
    }

    /// @brief Сформировать данные игрового предмета
    void Build()
    {
        ItemData.ItemName = item.GetType();
        ItemData.Healt = item.GetHealth();
        Magazine_Base mb = Magazine_Base.Cast(item);
        if (mb)
        {
            ItemData.Quantity = mb.GetAmmoCount();
        }
        else
        {
            ItemData.Quantity = item.GetQuantity();
        }
        ItemBase ib = ItemBase.Cast(item);
        if ((ib)&&(ib.IsLiquidContainer()))
        {
            ItemData.LiquidType = ib.GetLiquidType();
        }
        GameInventory inventory = item.GetInventory();
        if (inventory)
        {
            InventoryLocation itemLocation = new InventoryLocation();
            inventory.GetCurrentInventoryLocation(itemLocation);
            ItemData.Row = itemLocation.GetRow();
            ItemData.Col = itemLocation.GetCol();
            ItemData.Flip = itemLocation.GetFlip();
            ItemData.SlotID = itemLocation.GetSlot();
            array<EntityAI> itemsArray = new array<EntityAI>;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
            ItemData.Child = new KCSaveItemCollection();
            foreach(EntityAI child:itemsArray)
            {
                EntityAI parent = child.GetHierarchyParent();
                if ((child!=item)&&(parent == item))
                {
                    KCItemBuilder childBuilder = new KCItemBuilder(child);
                    childBuilder.Build();
                    ItemData.Child.Insert(childBuilder.ItemData);
                }
            }
        }
    }

    /// @brief Добавить позицию предмета
    /// @param player Если указан игрок, то будет добавлена относительная позиция
    void AddPosition(PlayerBase player = NULL)
    {
        if (player)
        {
            float yaw = (0 - player.GetOrientation()[0]) * Math.DEG2RAD;
            vector relativePos = item.GetPosition() - player.GetPosition();
            ItemData.Position = RotationYaw(relativePos, yaw);
        }
        else
        {
            ItemData.Position = item.GetPosition();
            ItemData.IsAbsolute = true;
        }
    }

    /// @brief Добавить ориентацию предмета
    /// @param player Если указан игрок, то будет добавлена относительная ориентация
    void AddOrientation(PlayerBase player = NULL)
    {
        ItemData.Orientation = item.GetOrientation();
        if (player)
        {
            ItemData.Orientation[0] = ItemData.Orientation[0]-player.GetOrientation()[0];
        }
    }


    private vector RotationYaw(vector pos, float yaw)
	{
		vector result = pos;
		result[0] = pos[0]*Math.Cos(yaw)+pos[2]*Math.Sin(yaw);
		result[2] = pos[2]*Math.Cos(yaw)-pos[0]*Math.Sin(yaw);
		return result;
	}

}
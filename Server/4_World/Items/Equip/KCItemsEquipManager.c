class KCItemsEquipManager
{
    private PlayerBase player;

    void KCItemsEquipManager(PlayerBase target)
    {
        player = target;
    }

    /// @brief Сбросить на землю все игровые предметы у игрока
    void DropAll()
    {
        GameInventory inventory = player.GetInventory();
		if (inventory)
		{
			array<EntityAI> itemsArray = new array<EntityAI>;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
            foreach(EntityAI item:itemsArray)
            {
                EntityAI parent = item.GetHierarchyParent();
                if (parent == player)
                {
                    inventory.DropEntity(InventoryMode.SERVER, parent, item);
                    player.SetSynchDirty();
                }
            }
		}
    }

    /// @brief Удалить все игровые предметы у игрока
    /// @param player игрок которого нужно раздеть
    void DeleteAll()
    {
        GameInventory inventory = player.GetInventory();
		if (inventory)
		{
			array<EntityAI> itemsArray = new array<EntityAI>;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			foreach(EntityAI item:itemsArray)
            {
                EntityAI parent = item.GetHierarchyParent();
                if (parent == player)
                {
                    GetGame().ObjectDelete(item);
                    player.SetSynchDirty();
                }
            }
		}
    }
    
}
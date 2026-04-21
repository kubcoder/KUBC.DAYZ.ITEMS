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

    bool Equip(KCItemSet equip)
    {
        DeleteAll();
        auto itemFabric = new KCItemFabric(player);
        bool errors = false;
        foreach(auto item:equip.Items)
        {
            auto e = itemFabric.Create(item);
            if (e==NULL)
            {
                errors = true;
                KCItems.Log("Не смогли выдать предмет:"+ item.ItemName, KCLogLevel.Error);
            }
        }
        return !errors;
    }

    bool Equip(string equipName)
    {
        auto mission = MissionBaseWorld.Cast(GetGame().GetMission());
        auto directory = mission.GetEquipDirectory();
        if (directory == NULL)
        {
            KCItems.Log("Директория экипировок не создана", KCLogLevel.Error);
            return false;
        }
        string setFileName = directory.GetDataFile(equipName);
        if (setFileName=="")
        {
            KCItems.Log("Экипировка ["+equipName+"] не существует", KCLogLevel.Error);
            return false;
        }
        KCItemSet itemSet = directory.LoadFile(setFileName);
        if (itemSet==NULL)
        {
            KCItems.Log("Ошибка загрузки экипировки ["+equipName+"]", KCLogLevel.Error);
            return false;
        }
        return Equip(itemSet);
    }

    
}
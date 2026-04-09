/// @brief Команда починки игровых предметов
class KCItemsCMDRepair : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "repair";

    override string GetName()
    {
        return KCItemsCMDRepair.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            data.MessageOwner("Не указано что именно починить у игрока");
            return true;
        }
        switch(data.Arg[0])
        {
            case "h":
                ItemBase itemHands = data.GetTarget().GetItemInHands();
                if(itemHands)
                {
                    auto tool = new KCItemsRepairTool(itemHands);
                    tool.All();
                    data.Message("Починили все что было в руках");
                    return true;
                }
                data.Message("Не найден предмет в руках, чинить нечего");
                return true;
            case "*":
                RepairAll(data);
                return true;
        }
        return true;
    }

    /// @brief Починить все предметы игрока
    /// @param player игрок у которого нужно починять предметы
    private void RepairAll(KCTextCmd data)
    {
        GameInventory inventory = data.GetTarget().GetInventory();
		if (inventory == NULL)
		{
            data.MessageOwner("Не смогли получить доступ к инвентарю");
        }
        array<EntityAI> itemsArray = new array<EntityAI>;
        ItemBase item;
        inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
        foreach(EntityAI child: itemsArray)
        {
            EntityAI parent = child.GetHierarchyParent();
            if (parent == data.GetTarget())
            {
                auto tool = new KCItemsRepairTool(child);
                tool.All();
                data.Message("Починили " + child.GetDisplayName());
            }
        }
    }
}
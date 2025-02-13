/// @brief Команда починки игровых предметов
class KCItemsCMDRepair  : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "repair";

    override string GetName()
    {
        return KCItemsCMDSpawn.CMD_NAME;
    }
    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        if (data.Arg.Count()>0)
        {
            switch(data.Arg[0])
            {
                case "h":
                    ItemBase itemHands = data.Player.GetItemInHands();
                    if(itemHands)
                    {
                        KCItems.RepairItem(itemHands);
                        return true;
                    }
                    return false;
                case "*":
                    RepairAll(data.Player);
                    return true;
            }
        }
        return false;
    }

    
    /// @brief Починить все предметы игрока
    /// @param player игрок у которого нужно починять предметы
    void RepairAll(PlayerBase player)
    {
        GameInventory inventory = player.GetInventory();
		if (inventory)
		{
			array<EntityAI> itemsArray = new array<EntityAI>;
			ItemBase item;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			foreach(EntityAI child: itemsArray)
            {
                KCItems.RepairItem(child);
            }
		}
    }
}
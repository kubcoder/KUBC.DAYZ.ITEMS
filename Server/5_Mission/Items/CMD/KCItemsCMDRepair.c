/** @brief Команда починки игровых предметов*/
class KCItemsCMDRepair  : KCUserCMD
{
    /** @brief название команды*/
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
                        RepairItem(itemHands);
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

    /** @brief Починить игровой итем, и все его компоненты
    *   @param eAi игровой предмет который нужно починять
    */
    static void RepairItem(EntityAI eAi)
    {
        eAi.SetHealthMax( "", "" );
        string cfgPath = CFG_VEHICLESPATH + " " + eAi.GetType() + " DamageSystem";
        if ( GetGame().ConfigIsExisting(cfgPath) )
        {
            array<string> damageZones = new array<string>;
            int dmgZoneCount = GetGame().ConfigGetChildrenCount(cfgPath); 
            if ( dmgZoneCount > 0 )
            {
                for (int i = 0; i < dmgZoneCount; ++i)
                {
                    string parentClass;
                    GetGame().ConfigGetChildName(cfgPath, i, parentClass);
                    parentClass.ToLower();
                    if ( parentClass == "damagezones" )
                    {
                        int dmgZoneIndex = GetGame().ConfigGetChildrenCount(cfgPath + " DamageZones");
                        for (int j = 0; j < dmgZoneIndex; ++j)
                        {
                            string childZone;
                            GetGame().ConfigGetChildName(cfgPath + " DamageZones", j, childZone);
                            damageZones.Insert( childZone );
                        }
                    }
                }
            }
            if ( damageZones && damageZones.Count() > 0 )
            {
                foreach(string dmgZone: damageZones)
                {
                    eAi.SetHealth(dmgZone, "",eAi.GetMaxHealth(dmgZone, ""));
                }
            }           
        }
        array<EntityAI> itemsArray = new array<EntityAI>;
        GameInventory inventory = eAi.GetInventory();
        if (inventory)
        {
            inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
            foreach(EntityAI child: itemsArray)
            {
                if (child!=eAi)
                    RepairItem(child);
            }
        }
    }
    /** @brief Починить все предметы игрока
    *   @param player игрок у которого нужно починять предметы
    */
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
                RepairItem(child);
            }
		}
    }
}
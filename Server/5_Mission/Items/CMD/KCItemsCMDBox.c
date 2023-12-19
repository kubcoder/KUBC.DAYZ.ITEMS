/** @brief Команда выдачи ящичка*/
class KCItemsCMDBox : KCUserCMD
{
    /** @brief название команды*/
    static const string CMD_NAME = "box";
    

    override string GetName()
    {
        return KCItemsCMDBox.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        string BoxName = "WoodenCrate";
        string ItemName = "";
        if (data.Arg.Count()>0)
        {
            ItemName = data.Arg[0];
        }
        if (data.Arg.Count()>1)
        {
            BoxName = data.Arg[1];
        }
        if (IsAviable(BoxName))
        {
            if (IsAviable(ItemName))
            {
                EntityAI box = EntityAI.Cast(data.Player.GetHumanInventory().CreateInHands(BoxName));
                if (box)
                {
                    Log("Ящик создан");
                    InventoryLocation loc = new InventoryLocation();
                    while(box.GetInventory().FindFirstFreeLocationForNewEntity(ItemName, FindInventoryLocationType.ANY_CARGO, loc))
                    {
                        Log("Создаем объект " + ItemName);
                        EntityAI item =  box.GetInventory().LocationCreateEntity(loc, ItemName, 0, 0);
                        loc = new InventoryLocation();
                    }
                }
                KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Выдали " + BoxName + " забитый " + ItemName);
                return true;
            }
            else
            {
                KCPlayer.SendMessage(user,"","Не смогли найти тип: " + ItemName);
                return false;
            }
        }
        else
        {
            KCPlayer.SendMessage(user,"","Не смогли найти тип ящика: " + BoxName);
            return false;
        }
    }
    bool IsAviable(string ItemName)
    {
        if (ItemName=="")
        {
            return false;
        }
        TStringArray cfgPaths = new TStringArray;
        cfgPaths.Insert( "CfgVehicles" );
        cfgPaths.Insert( "CfgWeapons" );
        cfgPaths.Insert( "CfgMagazines" );
        foreach(string path:cfgPaths)
        {
            int scope = GetGame().ConfigGetInt( path + " " + ItemName + " scope" );
            if(scope>1)
            {
                return true;
            }
        }
        return false;

    }
}
/// @brief Команда работы с экипировкой
class KCItemsCMDEquip : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "equip";
    
    /// @brief аргумент сохранения экипировки
    static const string ARG_SAVE = "save";
    
    /// @brief аргумент перезаписи существующей экипировки
    static const string ARG_REPLACE = "r";
    
    /// @brief аргумент сохранения экипировки в общую попку
    static const string ARG_SHARED = "s";
    
    /// @brief аргумент сброса всех итемов игрока на землю
    static const string ARG_DROP = "drop";
    
    /// @brief аргумент удаления всей экипировки игрока
    static const string ARG_CLEAR = "clear";
    
    /// @brief аргумент выдачи экипировки рядом с игроком
    static const string AGR_GROUND = "g";
    
    override string GetName()
    {
        return KCItemsCMDEquip.CMD_NAME;
    }
    
    /// @brief получить описание экипировки игрока
    /// @param player игрок экипировку которого нужно сохранить
    /// @return набор итемов входящих в экипировку игрока
    static KCItemSet FromPlayer(PlayerBase player)
    {
        GameInventory inventory = player.GetInventory();
		if (inventory)
		{
            KCItemSet res = new KCItemSet();
			array<EntityAI> itemsArray = new array<EntityAI>;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			foreach(EntityAI child: itemsArray)
            {
                KCItems.Log("Итем: " + child);
                EntityAI parent = child.GetHierarchyParent();
                if (parent == player)
                {
                    KCSaveItem eItem = KCSaveItem.FromItem(child);
                    if (eItem)
                    {
                        InventoryLocation il = new InventoryLocation;
                        child.GetInventory().GetCurrentInventoryLocation(il);
                        eItem.Row = il.GetRow();
                        eItem.Col = il.GetCol();
                        eItem.Flip = il.GetFlip();
                        eItem.SlotID = il.GetSlot();
                        res.Items.Insert(eItem);
                    }
                    else
                    {
                        KCItems.Log("Не смогли создать описание итема");
                    }
                }
                else
                {
                    KCItems.Log("Пропущен по родительскому фильтру");
                }
            }
            return res;
		}
        return NULL;
    }
    
    /// @brief Сохранить экипировку
    /// @param user экипировку какого игрока сохранять
    /// @param data данные текстовой команды
    bool Save(PlayerBase user, KCTextCmd data)
    {
        string SettName = "";
        if (data.Arg.Count()>1)
        {
            SettName = data.Arg[1];
        }
        if (SettName=="")
        {
            return false;
        }
        bool Replace = false;
        bool Shared = false;
        foreach(string arg: data.Arg)
        {
            if (arg==ARG_REPLACE)
            {
                Replace = true;
            }
            if (arg==ARG_SHARED)
            {
                Shared = true;
            }
        }
        KCItemSet equip = FromPlayer(user);
        if (equip)
        {
            equip.NickName = user.GetIdentity().GetName();
            equip.SteamID = user.GetIdentity().GetPlainId();
            string FileName ="";
            if (Shared)
            {
                FileName = KCItems.GetEquipFileName(SettName);
            }
            else
            {
                FileName = KCItems.GetEquipFileName(SettName, user);
            }
            if (FileExist(FileName))
            {
                if(Replace)
                {
                    JsonFileLoader<KCItemSet>.JsonSaveFile(FileName, equip);
                    KCPlayer.SendMessage(user,"","экипировка " + SettName + " обновлена.");
                    return true;
                }
                else
                {
                    KCPlayer.SendMessage(user,"","Файл уже существует, сохранение не выполнено");
                }
            }
            else
            {
                JsonFileLoader<KCItemSet>.JsonSaveFile(FileName, equip);
                KCPlayer.SendMessage(user,"","Экипировка " + SettName + " создана.");     
                return true;           
            }
        }
        else
        {
            KCPlayer.SendMessage(user,"","Не смогли создать экипировку");
        }
        return false;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (data.Arg.Count()>0)
        {
            if (!data.Player)
            {
                data.Player = user;
            }
            if (data.Arg[0]==ARG_SAVE)
            {
                return Save(user, data);
            }
            if (data.Arg[0]==ARG_DROP)
            {
                KCItemSet.DropAll(data.Player);
                KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Сбросили всю экипировку под ноги");    
                return true;
            }
            if (data.Arg[0]==ARG_CLEAR)
            {
                KCItemSet.DeleteAll(data.Player);
                KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Удалили всю экипировку");    
                return true;
            }
            string FileName;
            KCItemSet cSet;
            if (data.ContainsArg(AGR_GROUND))
            {
                FileName = KCItems.GetEquipFileName(data.Arg[0], user);
                if (!FileExist(FileName))
                {
                    FileName = KCItems.GetEquipFileName(data.Arg[0]);
                }
                if (FileExist(FileName))
                {
                    JsonFileLoader<KCItemSet>.JsonLoadFile(FileName, cSet);
                    if (cSet)
                    {
                        foreach(KCSaveItem cItem:cSet.Items)
                        {
                            KCItems.Log("Выдаем итем: " + cItem.ItemName);
                            EntityAI ei = cItem.CreateOnRoute(data.Player, 0);
                            if (ei)
                            {
                                KCItems.Log("Итем выдан" + cItem.ItemName);
                            }
                            else
                            {
                                KCItems.Log("Не смогли выдать итем:" + cItem.ItemName, KCLogLevel.Error);
                            }
                        }
                        KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Экипировку сложили рядом с вами");
                        return true;
                    }
                    else
                    {
                        KCPlayer.SendMessage(user,"","Не смогли загрузить экипировку"); 
                    }
                }
                else
                {
                    KCPlayer.SendMessage(user,"","Не смогли найти экипировку"); 
                }
                return false;
            }
            FileName = KCItems.GetEquipFileName(data.Arg[0], user);
            if (!FileExist(FileName))
            {
                FileName = KCItems.GetEquipFileName(data.Arg[0]);
            }
            if (FileExist(FileName))
            {
                
                JsonFileLoader<KCItemSet>.JsonLoadFile(FileName, cSet);
                if(cSet)
                {
                    cSet.CreateEquip(data.Player, false);
                    KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Выдали новую экипировку");    
                    return true;
                }
                else
                {
                    KCPlayer.SendMessage(user,"","Не смогли загрузить экипировку");        
                }
                return false;
            }
            KCPlayer.SendMessage(user,"","Не смогли понять чего вы хотите");
        }
        return false;
    }
}
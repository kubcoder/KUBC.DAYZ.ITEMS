/// @brief Команда сохранения набора итемов
class KCItemsCMDSave : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "save";
    
    /// @brief аргумент перезаписи существующего набора
    static const string ARG_REPLACE = "r";
    
    /// @brief аргумент записи набора в общую папку админов
    static const string ARG_SHARED = "s";
    
    /// @brief аргумент записи набора вокруг игрока
    static const string ARG_GROUND = "g";
    
    /// @brief аргумент записи набора вокруг игрока с сохренением абсолютных координат
    static const string ARG_ABSGROUND = "a";
    
    /// @brief Растояние поиска предметов по умолчанию
    static const float DEF_DISTANCE = 3;

    override string GetName()
    {
        return KCItemsCMDSave.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        string SettName = "";
        bool Replace = false;
        bool Shared = false;
        float Distance = -1;
        bool IsAbsolute = false;
        if (data.Arg.Count()>0)
        {
            SettName = data.Arg[0];
            if (data.Arg.Count()>1)
            {
                for(int i=1; i<data.Arg.Count();i++)
                {
                    switch(data.Arg[i][0])
                    {
                        case ARG_REPLACE:
                            Replace = true;
                            break;
                        case ARG_SHARED:
                            Shared = true;
                            break;
                        case ARG_GROUND:
                            Distance = GetDistance(data.Arg[i]);
                            break;
                        case ARG_ABSGROUND:
                            Distance = GetDistance(data.Arg[i]);
                            IsAbsolute = true;
                            break;
                    }
                }
            }
        }
        if (SettName!="")
        {
            KCItemSet iSet = new KCItemSet();
            iSet.NickName = user.GetIdentity().GetName();
            iSet.SteamID = user.GetIdentity().GetPlainId();
            string FileName ="";
            if (Shared)
            {
                FileName = KCItems.GetSetsFile(SettName);
            }
            else
            {
                FileName = KCItems.GetSetsFile(SettName, user);
            }
            if(Distance>-1)
            {
                ref array<Object> nearest_objects = new array<Object>;
                ref array<CargoBase> proxy_cargos = new array<CargoBase>;
                GetGame().GetObjectsAtPosition ( data.Player.GetPosition(), Distance, nearest_objects, proxy_cargos);
                KCItemsSaveSettings options = KCItems.GetItemsSaveSettings();
                Log("Ориентация игрока:" + data.Player.GetOrientation());
                Log("Позиция игрока:" + data.Player.GetPosition());
                foreach(Object obj:nearest_objects)
                {
                    EntityAI eA = EntityAI.Cast(obj);
                    if (eA)
                    {
                        Log("Объект: " + eA.GetType());
                        Log("Позиция: " + eA.GetPosition());
                        Log("Ориентация: " + eA.GetOrientation());
                        if (options.IsSaveItem(obj.GetType()))
                        {
                            KCSaveItem gItem = KCSaveItem.FromItem(eA);
                            if (IsAbsolute)
                            {
                                gItem.Position = eA.GetPosition();
                                gItem.Orientation = eA.GetOrientation();
                                gItem.IsAbsolute = true;
                                gItem.Quantity = 0;
                                iSet.Items.Insert(gItem);
                            }
                            else
                            {
                                gItem.AddPosition(eA, data.Player);
                                gItem.AddOrientation(eA, data.Player);
                                gItem.Quantity = 0;
                                iSet.Items.Insert(gItem);
                            }
                        }
                        else
                        {
                            Log("Исключен из набора в соответсвии с настройками.");    
                        }
                        KCItems.Log("------------------------------------------");
                    }
                }

            }
            else
            {
                ItemBase itemHands = data.Player.GetItemInHands();
                if (itemHands)
                {
                    KCSaveItem sItem = KCSaveItem.FromItem(itemHands);
                    if (sItem)
                    {
                        iSet.Items.Insert(sItem);
                    }
                }
            }
            if (FileExist(FileName))
            {
                if(Replace)
                {
                    JsonFileLoader<KCItemSet>.JsonSaveFile(FileName, iSet);
                    KCPlayer.SendMessage(user,"","Набор " + SettName + " обновлен.");
                    return true;
                }
                else
                {
                    KCPlayer.SendMessage(user,"","Файл уже существует, сохранение не выполнено");
                    return false;
                }
            }
            else
            {
                JsonFileLoader<KCItemSet>.JsonSaveFile(FileName, iSet);
                KCPlayer.SendMessage(user,"","Набор " + SettName + " создан.");                
                return true;
            }
        }
        return false;
    }

    float GetDistance(string arg)
    {
        TStringArray gToken = new TStringArray;
        float distance = DEF_DISTANCE;
        arg.Split("=", gToken);
        if (gToken.Count()>1)
        {
            distance = gToken[1].ToFloat();
            if (distance==0)
            {
                distance = DEF_DISTANCE;
            }
        }
        return distance;
    }
}
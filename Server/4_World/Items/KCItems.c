class KCItems
{
    static const string MOD_NAME = "KC.ITEMS";
    static void Log(string Message, KCLogLevel Level = KCLogLevel.Info)
    {
        KCLog.Write(MOD_NAME, Message, Level);
    }
    /** @brief Корневая папка разработчика*/
    static const string ROOT_PATH = "KUBC";
    /** @brief Корневая папка класса мода*/
    static const string MOD_PATH = "ITEMS";
    /** @brief Папка где размещается справочник итемов*/
    static const string DICT_PATH = "Dictionary";
    /** @brief Папка где размещаются сеты итемов*/
    static const string SETS_PATH = "Sets";
    /** @brief Папка где размещаются сеты машин*/
    static const string CARS_PATH = "Cars";
    /** @brief Папка с сохранеными экипировками*/
    static const string EQUIP_PATH = "Equip";
    /** @brief Создаем папку мода и файл настроек если он не существует*/
    static void CreatePaths()
    {
        MakeDirectory("$profile:"+ROOT_PATH);
        MakeDirectory(GetModPath());
        MakeDirectory(GetDictionaryPath());
        MakeDirectory(GetStetsPath());
        MakeDirectory(GetEquipPath());
        MakeDirectory(GetCarsPath());
        if (FileExist(GetSettingsFile()))
        {
            Log("Файл настроек сохранения наборов итемов сущесвтует");
        }
        else
        {
            Log("Создаем файл настроек сохранения наборов итемов по умолчанию");
            KCItemsSaveSettings options = KCItemsSaveSettings.GetDefault();
            JsonFileLoader<KCItemsSaveSettings>.JsonSaveFile(GetSettingsFile(), options);
        }
    }
    /** @brief Полный путь к папке мода*/
    static string GetModPath()
    {
        return "$profile:"+ROOT_PATH + "\\" + MOD_PATH;
    }
    /** @brief Полный путь к папке справочника итемов*/
    static string GetDictionaryPath()
    {
        return GetModPath() + "\\" + DICT_PATH;
    }

    /** @brief Полный путь к папке наборов итемов*/
    static string GetStetsPath()
    {
        return GetModPath() + "\\" + SETS_PATH;
    }

    /** @brief Имя файла настроек*/
    static const string SETT_FILENAME = "ItemsSetOptions.json";

    /** @brief Получить полное имя файла настроек сохранения набора итемов*/
    static string GetSettingsFile()
    {
        return GetModPath() + "\\" + SETT_FILENAME;
    }

    /** @brief Получить настройки сохранения итемов*/
    static KCItemsSaveSettings GetItemsSaveSettings()
    {
        KCItemsSaveSettings options;
        JsonFileLoader<KCItemsSaveSettings>.JsonLoadFile(GetSettingsFile(), options);
        if (options)
        {
            return options;
        }
        return new KCItemsSaveSettings();
    }

    /** @brief Имя файла для сохранения набора итемов
    *   @param SetName введенное имя набора итемов
    *   @param player игрок который запросил сохранение
    *           если указано NULL то имя файла будет в общей папке набора
    */
    static string GetSetsFile(string SetName, PlayerBase player = NULL)
    {
        if (player)
        {
            MakeDirectory(GetStetsPath() + "\\" + player.GetIdentity().GetPlainId());
            return GetStetsPath() + "\\" + player.GetIdentity().GetPlainId() + "\\" + SetName + ".json";
        }
        else
        {
            return GetStetsPath() + "\\" + SetName + ".json";
        }
    }

    /** @brief Полный путь к папке экипировок
    *   @param player для какого игрока получать папку, если указан NULL
    *                 то будет возвращено корневая папка экипировок
    */
    static string GetEquipPath(PlayerBase player = NULL)
    {
        if (player)
        {
            string pathName = GetEquipPath() + "\\" + player.GetIdentity().GetPlainId();
            MakeDirectory(pathName);
            return pathName;
        }
        else
        {
            return GetModPath() + "\\" + EQUIP_PATH;
        }
    }
    /** @brief Получить полный путь к файлу экипировки
    *   @param SettName имя экипировки
    *   @param player для какого игрока получать папку, если указан NULL
    *                 то будет возвращено корневая папка экипировок
    */
    static string GetEquipFileName(string SettName, PlayerBase player = NULL)
    {
        return GetEquipPath(player) + "\\" + SettName + ".json";
    }

    /** @brief Полный путь к папке наборов машин*/
    static string GetCarsPath()
    {
        return GetModPath() + "\\" + CARS_PATH;
    }

    /** @brief Полный путь к набору машины
    *   @param SettName имя сохраненной тачилы
    *   @param player для какого игрока получать папку, если указан NULL
    *                 то будет возвращено корневая папка экипировок
    */
    static string GetCarFile(string SetName, PlayerBase player = NULL)
    {
        if (player)
        {
            MakeDirectory(GetCarsPath() + "\\" + player.GetIdentity().GetPlainId());
            return GetCarsPath() + "\\" + player.GetIdentity().GetPlainId() + "\\" + SetName + ".json";
        }
        else
        {
            return GetCarsPath() + "\\" + SetName + ".json";
        }
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
}
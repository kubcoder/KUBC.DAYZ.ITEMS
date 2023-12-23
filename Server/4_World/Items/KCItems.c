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
}
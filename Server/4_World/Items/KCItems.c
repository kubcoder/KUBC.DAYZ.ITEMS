class KCItems
{
    static const string MOD_NAME = "KC.ITEMS";
    static void Log(string Message, KCLogLevel Level = KCLogLevel.Info)
    {
        KCLog.Write(MOD_NAME, Message, Level);
    }
    /*Корневая папка разработчика*/
    static const string ROOT_PATH = "KUBC";
    /*Корневая папка класса мода*/
    static const string MOD_PATH = "ITEMS";
    /*Папка где размещается справочник итемов*/
    static const string DICT_PATH = "Dictionary";
    /*Папка где размещаются сеты итемов*/
    static const string SETS_PATH = "Sets";
    /*Папка где размещаются сеты машин*/
    static const string CARS_PATH = "Cars";
    //Создаем папку мода и файл настроек если он не существует
    static void CreatePaths()
    {
        MakeDirectory("$profile:"+ROOT_PATH);
        MakeDirectory(GetModPath());
        MakeDirectory(GetDictionaryPath());
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
    /*Полный путь к папке мода*/
    static string GetModPath()
    {
        return "$profile:"+ROOT_PATH + "\\" + MOD_PATH;
    }
    /*Полный путь к папке справочника итемов*/
    static string GetDictionaryPath()
    {
        return GetModPath() + "\\" + DICT_PATH;
    }

    /*Имя файла настроек*/
    static const string SETT_FILENAME = "ItemsSetOptions.json";

    static string GetSettingsFile()
    {
        return GetModPath() + "\\" + SETT_FILENAME;
    }
}
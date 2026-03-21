/// @brief Инструмент создания справочника игровых предметов
class KCItemsDictionary
{
    private ref KCItemsDictionaryDirectory directory;

    private ref KCItemCategories categories;

    private ref TStringArray cfgPaths;

    private ref KCItemDictionary dictionary;

    /// @brief Инициализируем справочник
    void KCItemsDictionary()
    {
        directory = new KCItemsDictionaryDirectory();
        directory.CreatePaths();
    }

    void Create()
    {
        string fileName = directory.GetDictionaryFileName();
        if(FileExist(fileName))
        {
            KCItems.Log("Справочник итемов существует. Для обновления удалите файл: " + fileName);
            return ;
        }
        KCItemCategoriesFactory categoriesFactory = new KCItemCategoriesFactory(directory.GetCategoriesFileName());
        categories = categoriesFactory.Load();
        if (categories == NULL)
        {
            return;
        }
        if (categories.Count()==0)
        {
            KCItems.Log("Не настроен файл категорий. Справочник не создан", KCLogLevel.Warning);
        }
        KCItems.Log("Категории загружены, начинаем подготовку файла итемов");
        foreach(KCItemCategory cat:categories)
        {
            KCItems.Log(cat.BaseClass + "[" + cat.ShowName + "]:" + cat.Priority.ToString());
        }
        KCItems.Log("Начинаем создание справочника итемов");
        dictionary = new KCItemDictionary();
        InitCfgsPaths();
        foreach(string path:cfgPaths)
        {
            AddPath(path);
        }
        KCItems.Log("Сохраняем справочник [" + dictionary.Count() + "] итемов");
        JsonFileLoader<KCItemDictionary>.JsonSaveFile(fileName, dictionary);
    }

    private void AddPath(string path)
    {
        int count =  GetGame().ConfigGetChildrenCount(path);
        for (int i=0;i<count;i++)
        {
            string strClassName;
            GetGame().ConfigGetChildName(path, i, strClassName );
            int scope = GetGame().ConfigGetInt( path + " " + strClassName + " scope" );
            if (scope>1)
            {
                KCItemDesc itm = new KCItemDesc();
                itm.Description = GetDisplayName(strClassName);
                itm.Category = GetCategoryName(strClassName);
                dictionary.Insert(strClassName, itm);
            }
        }
    }

    private void InitCfgsPaths()
    {
        cfgPaths = new TStringArray();
        cfgPaths.Insert( "CfgVehicles" );
        cfgPaths.Insert( "CfgWeapons" );
        cfgPaths.Insert( "CfgMagazines" );
        cfgPaths.Insert( "CfgNonAIVehicles");
    }

    private string GetDisplayName(string name)
    {
        
        string DisplayItemName = string.Empty;
        if (GetGame().ConfigGetText("CfgVehicles" + " " + name + " " + "displayName", DisplayItemName))
        {
            return DisplayItemName;
        }
        if (GetGame().ConfigGetText("CfgMagazines" + " " + name + " " + "displayName", DisplayItemName))
        {
            return DisplayItemName;
        }
        if (GetGame().ConfigGetText("cfgWeapons" + " " + name + " " + "displayName", DisplayItemName))
        {
            return DisplayItemName;
        }
        if (GetGame().ConfigGetText("cfgAmmo" + " " + name + " " + "displayName", DisplayItemName))
        {
            return DisplayItemName;
        }
        return name;
    }



    private string GetCategoryName(string name)
	{
		foreach(KCItemCategory cat:categories)
        {
            if(GetGame().IsKindOf(name, cat.BaseClass))
            {
                return cat.ShowName;
            }
        }
		return "";
	}
}
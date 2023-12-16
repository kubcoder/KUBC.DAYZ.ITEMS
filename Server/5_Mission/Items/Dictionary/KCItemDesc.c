/** @brief Описание итема в справочнике*/
class KCItemDesc
{
    /** @brief Класс итема*/
    string ItemName;
    /** @brief Категория итема*/
    string Category;
    /** @brief Описание итема на языке котором запущен сервер*/
    string Description;
    /** @brief Имя файла справочника*/
    static const string FILE_NAME = "items.json";
    /** @brief Полное имя файла справочника*/
    static string GetFileName()
    {
        return KCItems.GetDictionaryPath() + "\\" + FILE_NAME;
    }
    /** @brief формируем справочник итемов*/
    static KCItemDictionary GetDictionary()
    {
        KCItemCategories categories = KCItemCategory.GetCategories();
        if (categories.Count()>0)
        {
            KCItems.Log("Категории загружены, начинаем подготовку файла итемов");
			foreach(KCItemCategory cat:categories)
			{
				KCItems.Log(cat.BaseClass + "[" + cat.ShowName + "]:" + cat.Priority.ToString());
			}
            KCItemDictionary dict = new KCItemDictionary();
			TStringArray cfgPaths = new TStringArray;
			cfgPaths.Insert( "CfgVehicles" );
			cfgPaths.Insert( "CfgWeapons" );
			cfgPaths.Insert( "CfgMagazines" );
			cfgPaths.Insert( "CfgNonAIVehicles");
			foreach(string path:cfgPaths)
			{
				int count =  GetGame().ConfigGetChildrenCount(path);
				for (int i=0;i<count;i++)
				{
					string strClassName;
					GetGame().ConfigGetChildName( path, i, strClassName );
					int scope = GetGame().ConfigGetInt( path + " " + strClassName + " scope" );
					if (scope>1)
					{
						KCItemDesc itm = new KCItemDesc();
						itm.ItemName = strClassName;
						itm.Description = GetDisplayName(strClassName);
						itm.Category = GetCategoryName(strClassName,categories);
						dict.Insert(itm);
					}
				}
			}
            return dict;
        }
        else
        {
            KCItems.Log("Не настроен файл категорий. Справочник не создан", KCLogLevel.Warning);
        }
        return NULL;
    }

    static string GetCategoryName(string Name, KCItemCategories Cats)
	{
		foreach(KCItemCategory cat:Cats)
        {
            if(GetGame().IsKindOf(Name, cat.BaseClass))
            {
                return cat.ShowName;
            }
        }
		return "";		
	}


	static string GetDisplayName(string Name)
    {
        
        string DisplayItemName = string.Empty;
        if (GetGame().ConfigGetText("CfgVehicles" + " " + Name + " " + "displayName", DisplayItemName))
        {
            return DisplayItemName;
        }
        if (GetGame().ConfigGetText("CfgMagazines" + " " + Name + " " + "displayName", DisplayItemName))
        {
            return DisplayItemName;
        }
        if (GetGame().ConfigGetText("cfgWeapons" + " " + Name + " " + "displayName", DisplayItemName))
        {
            return DisplayItemName;
        }
        if (GetGame().ConfigGetText("cfgAmmo" + " " + Name + " " + "displayName", DisplayItemName))
        {
            return DisplayItemName;
        }
        return Name;
    }

    static void CreateDictionary()
    {
        string fnDict = GetFileName();
        if (FileExist(fnDict))
        {
            KCItems.Log("Справочник итемов существует. Для обновления удалите файл: " + fnDict);
        }
        else
        {
            KCItems.Log("Начинаем создание справочника итемов");
            KCItemDictionary dict = GetDictionary();
            if (dict)
            {
                KCItems.Log("Сохраняем справочник [" + dict.Count() + "] итемов");
                JsonFileLoader<KCItemDictionary>.JsonSaveFile(GetFileName(), dict);
            }
        }
        
    }
}
/** @brief Справочник итемов*/
typedef array<ref KCItemDesc>	KCItemDictionary;
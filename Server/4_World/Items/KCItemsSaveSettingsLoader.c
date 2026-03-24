/// @brief Загрузчик настроек сохранения игровых предметов
class KCItemsSaveSettingsLoader
{
    private string fullFileName;

    /// Инициализация фабрики настроек сохранения
    void KCItemsSaveSettingsLoader(string fileName)
    {
        fullFileName = fileName;
    }

    KCItemsSaveSettings Load()
    {
        KCItemsSaveSettings options;
        if (FileExist(fullFileName))
        {
            JsonFileLoader<KCItemsSaveSettings>.JsonLoadFile(fullFileName, options);
            if (options)
            {
                if (options.IsValid())
                {
                    return options;
                }
            }
            KCItems.Log("Ошибка загрузки файла настроек сохранения, или файл пустой. Используем значение по умолчанию", KCLogLevel.Error);
            return GetDefault();
        }
        KCItems.Log("Файл настроек сохранения несуществует, создаем со значениями по умолчанию", KCLogLevel.Info);
        options = GetDefault();
        JsonFileLoader<KCItemsSaveSettings>.JsonSaveFile(fullFileName, options);
        return options;
    }
    ///  @brief  получить настройки по умолчанию.
    ///  @return Набор всяких камней, кустов, игроков, зомбей
    ///          в общем всего того что не стоит сохранять, вот не нужно
    ///          ибо последствия могут быть совсем неожиданные.     
    private KCItemsSaveSettings GetDefault()
    {
        KCItemsSaveSettings options = new KCItemsSaveSettings();
        options.BaseClasses.Insert("SurvivorBase");
        options.BaseClasses.Insert("DZ_LightAI");
        options.BaseClasses.Insert("HouseNoDestruct");
        options.BaseClasses.Insert("Plant");
        options.BaseClasses.Insert("RockBase");
        options.BaseClasses.Insert("WoodBase");
        options.BaseClasses.Insert("Building");
        options.BaseClasses.Insert("BuildingSuper");
        options.BaseClasses.Insert("HouseNoDestruct");
        options.BaseClasses.Insert("BaseBuildingBase");
        options.BaseClasses.Insert("FenceKit");
        options.BaseClasses.Insert("WatchtowerKit");
        options.BaseClasses.Insert("TerritoryFlagKit");
        options.BaseClasses.Insert("transport");
        return options;
    }
    
}
/// @brief описание итемов которые не нужно сохранять
class KCItemsSaveSettings
{
    /// @brief  это черный список, т.е. выполняется сохранение
    ///           всех итемов кроме указанных.
    ///           Если данный параметр ложь, то выполняется 
    ///           сохранение только итемов которые указаны в списке
    bool IsBlackList = true;

    /// @brief список базовых классов
    ref TStringArray BaseClasses = new TStringArray;

    /// @brief  Проверка разрешений на сохранение итема
    /// @param  oType тип сохраняемого итема
    /// @return Истина если сохранение разрешено
    bool IsSaveItem(string oType)
    {
        if(IsBlackList)
        {
            if (IsChild(oType))
            {
                return false;
            }
            else
            {
                return true;
            }
        }        
        else
        {
            if (IsChild(oType))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    /// @brief Проверка содержится ли тип в списке BaseClasses
    /// @param  oType тип сохраняемого итема
    /// @return Истина если итем указан в списке, или является дочерним
    ///         от указанного в списке.
    bool IsChild(string oType)
    {
        foreach(string bClass:BaseClasses)
        {
            if (GetGame().IsKindOf(oType, bClass))
            {
                return true;
            }
        }
        return false;
    }

    /// @brief  получить настройки по умолчанию.
    /// @return Набор всяких камней, кустов, игроков, зомбей
    ///         в общем всего того что не стоит сохранять, вот не нужно
    ///         ибо последствия могут быть совсем неожиданные.        
    static KCItemsSaveSettings GetDefault()
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
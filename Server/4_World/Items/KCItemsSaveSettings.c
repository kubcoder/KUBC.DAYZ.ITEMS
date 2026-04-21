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

    /// @brief настройки загружены
    /// @return Истина если загружен один или более базовый класс
    bool IsValid()
    {
        return BaseClasses.Count()>0;
    }

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

}
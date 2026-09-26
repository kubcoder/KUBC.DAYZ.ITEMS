class KCItemsCMDTransport : KCUserCMD
{
    /// @brief Аргумент сохранения транспорта
    const string ARG_SAVE = "save";
    
    /// @brief аргумент на какой дистанции создать транспорта
    const string ARG_DISTANCE = "d";

    /// @brief Дистанция для поиска транспорта по умолчанию
    const float DEF_DIST = 10;

    /// @brief аргумент заправки транспорта
    const string ARG_REFUEL = "refuel";
    
    /// @brief аргумент ремонта транспорта
    const string ARG_REPAIR = "repair";
    
    /// @brief Аргумент для толчка транспорта вперед
    const string ARG_FRONT = "f";

    /// @brief Аргумент для толчка транспорта назад
    const string ARG_BACK = "b";

    /// @brief Аргумент для толчка транспорта влево
    const string ARG_LEFT = "l";

    /// @brief Аргумент для толчка транспорта вправо
    const string ARG_RIGHT = "r";

    /// @brief Импульс по умолчанию
    const float DEF_IMPULSE = 10000;

    /// @brief Аргумент для полной починки транспорта
    ///        включая инвентарь
    const string ARG_ALL = "all";

    /// @brief Аргумент для продления времени
    ///        жизни транспорта
    const string ARG_LT = "ll";

     /// @brief Проверяем нужно ли создать транспорт
    /// @param data данные команды
    /// @return истина если лодка должна быть создана
    bool MustBeSpawn(KCTextCmd data)
    {
        if (data.ContainsArg(ARG_REPAIR))
            return false;
        if (data.ContainsArg(ARG_REFUEL))
            return false;
        if (data.ContainsArg(ARG_FRONT))
            return false;
        if (data.ContainsArg(ARG_BACK))
            return false;
        if (data.ContainsArg(ARG_LEFT))
            return false;
        if (data.ContainsArg(ARG_RIGHT))
            return false;
        if (data.ContainsArg(ARG_SAVE))
            return false;
        if (data.ContainsArg(ARG_LT))
            return  false;
        return true;
    }
}
class KCItemsSetsDirectory : KCItemsDirectory
{
    /// @brief Папка где размещаются сеты итемов
    const string SETS_PATH = "Sets";

    void KCItemsSetsDirectory()
    {
        pathNames.Insert(SETS_PATH);
    }

    /// @brief Имя файла настроек
    const string SET_FILENAME = "ItemsSetOptions.json";

    /// @brief Получить имя файла конфигурации сохраннеия
    /// @return Полное имя файла конфигурации сохранения наборов
    string GetItemSetOptionsFile()
    {
        return GetName(SET_FILENAME);
    }
}
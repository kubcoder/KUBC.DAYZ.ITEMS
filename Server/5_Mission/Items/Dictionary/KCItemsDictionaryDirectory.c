class KCItemsDictionaryDirectory:KCItemsDirectory
{
    /// @brief Папка где размещается справочник итемов
    const string DICT_PATH = "Dictionary";

    void KCItemsDictionaryDirectory()
    {
        pathNames.Insert(DICT_PATH);
    }

    /// @brief Имя файла настроек категорий
    const string CATEGORIES_FILE_NAME = "categories.json";

    /// @brief Получить имя файла категорий
    /// @return Полное имя файла настроек категорий
    string GetCategoriesFileName()
    {
        return GetName(CATEGORIES_FILE_NAME);
    }

    /// @brief Имя файла справочника
    const string DICTIONARY_FILE_NAME = "items.json";

    /// @brief Получить имя файла справочника
    /// @return Полное имя файла справочника игровых предметов
    string GetDictionaryFileName()
    {
        return GetName(DICTIONARY_FILE_NAME);
    }

}
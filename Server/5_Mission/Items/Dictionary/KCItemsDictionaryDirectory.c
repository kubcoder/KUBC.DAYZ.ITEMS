class KCItemsDictionaryDirectory:KCDirectory
{
    /// @brief Папка где размещается справочник итемов
    const string DICT_PATH = "Dictionary";

    void KCItemsDictionaryDirectory()
    {
        pathNames.Insert(DICT_PATH);
    }
}
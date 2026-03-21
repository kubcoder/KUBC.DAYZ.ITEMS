class KCItemsSetsDirectory : KCItemsDirectory
{
    /// @brief Папка где размещаются сеты итемов
    const string SETS_PATH = "Sets";

    void KCItemsSetsDirectory()
    {
        pathNames.Insert(SETS_PATH);
    }
}
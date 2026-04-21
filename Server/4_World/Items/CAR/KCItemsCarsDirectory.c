class KCItemsCarsDirectory: KCItemsDirectory
{
    /// @brief Папка где размещаются наборы машин
    const string CARS_PATH = "Cars";

    void KCItemsCarsDirectory()
    {
        pathNames.Insert(CARS_PATH);
    }
}
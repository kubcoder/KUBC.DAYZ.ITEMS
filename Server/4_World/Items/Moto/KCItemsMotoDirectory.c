class KCItemsMotoDirectory: KCItemsDirectory
{
    /// @brief Папка где размещаются наборы мотоциклов
    const string MOTO_PATH = "Moto";

    void KCItemsMotoDirectory()
    {
        pathNames.Insert(MOTO_PATH);
    }
}
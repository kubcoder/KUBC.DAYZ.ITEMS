/// @brief Директория мода
class KCItemsDirectory:KCDirectory
{
    /// @brief Корневая папка класса мода
    const string MOD_PATH = "ITEMS";

    void KCItemsDirectory()
    {
        pathNames.Insert(MOD_PATH);
    }
}
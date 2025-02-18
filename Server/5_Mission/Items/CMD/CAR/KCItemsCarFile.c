/// @brief Клас для работы с файлами машины
class KCItemsCarFile
{


    /// @brief Полный путь к набору машины
    /// @param SettName имя сохраненной тачилы
    /// @param player для какого игрока получать папку, если указан NULL
    ///               то будет возвращено корневая папка машин
    string GetCarFile(string SetName, PlayerBase player = NULL)
    {
        if (player)
        {
            MakeDirectory(KCItems.GetCarsPath() + "\\" + player.GetIdentity().GetPlainId());
            return KCItems.GetCarsPath() + "\\" + player.GetIdentity().GetPlainId() + "\\" + SetName + ".json";
        }
        else
        {
            return KCItems.GetCarsPath() + "\\" + SetName + ".json";
        }
    }
}
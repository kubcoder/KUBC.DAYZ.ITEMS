/// @brief Директория мода
class KCItemsDirectory:KCDirectory
{
    /// @brief Корневая папка класса мода
    const string MOD_PATH = "ITEMS";

    void KCItemsDirectory()
    {
        pathNames.Insert(MOD_PATH);
    }

    /// Получить корневую папку мода
    string GetModPath()
    {
        return GetName(pathNames.Count() - 1);
    }

    /// @brief Получить имя файла 
    /// @param setName введенное имя набора
    /// @param player игрок который запросил сохранение
    ///           если указано NULL то имя файла будет в общей папке набора
    string GetDataFile(string setName, PlayerBase player = NULL)
    {
        string pathName = GetName();
        if (player)
        {
            pathName = GetPlayerPath(player);
            MakeDirectory(pathName);
        }
        return pathName + GetSeparator() + setName + ".json";
    }

    /// @brief Имя папки игрока
    /// @param player игрок владелец личной папки
    /// @return полный путь к папке игрока
    string GetPlayerPath(PlayerBase player)
    {
        return GetName() + GetSeparator() + player.GetIdentity().GetPlainId();
    }


    string FindDataFile(string setName, PlayerBase player)
    {
        string fileName = GetDataFile(setName, player);
        if(FileExist(fileName))
        {
            return fileName;
        }
        fileName = GetDataFile(setName);
        if(FileExist(fileName))
        {
            return fileName;
        }
        return "";
    }

    KCItemSet LoadFile(string fileName)
    {
        KCItemSet result;
        JsonFileLoader<KCItemSet>.JsonLoadFile(fileName, result);
        return result;
    }

}
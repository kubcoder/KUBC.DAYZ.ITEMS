/// @brief Команда сохранения набора итемов
class KCItemsCMDSave : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "save";
    
    /// @brief аргумент перезаписи существующего набора
    const string ARG_REPLACE = "r";
    
    /// @brief аргумент записи набора в общую папку админов
    const string ARG_SHARED = "s";
    
    /// @brief аргумент записи набора вокруг игрока
    const string ARG_GROUND = "g";
    
    /// @brief аргумент записи набора вокруг игрока с сохренением абсолютных координат
    const string ARG_ABSGROUND = "a";
    
    /// @brief Растояние поиска предметов по умолчанию
    const float DEF_DISTANCE = 3;

    private ref KCItemsSetsDirectory directory;

    void KCItemsCMDSave(KCItemsSetsDirectory setsDirectory)
    {
        directory = setsDirectory;
    }

    override string GetName()
    {
        return KCItemsCMDSave.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        return true;
    }
}
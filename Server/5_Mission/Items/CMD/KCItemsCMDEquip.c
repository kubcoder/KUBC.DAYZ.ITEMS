/// @brief Команда работы с экипировкой
class KCItemsCMDEquip : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "equip";
    
    /// @brief аргумент сохранения экипировки
    const string ARG_SAVE = "save";
        
    /// @brief аргумент сброса всех итемов игрока на землю
    const string ARG_DROP = "drop";
    
    /// @brief аргумент удаления всей экипировки игрока
    const string ARG_CLEAR = "clear";
    
    /// @brief аргумент выдачи экипировки рядом с игроком
    const string AGR_GROUND = "g";
    
    

    override string GetName()
    {
        return KCItemsCMDEquip.CMD_NAME;
    }

    private ref KCItemsEquipDirectory directory;

    void KCItemsCMDEquip(KCItemsEquipDirectory setsDirectory)
    {
        directory = setsDirectory;
    }
}
class KCItemsEquipDirectory: KCItemsDirectory
{
    /// @brief Папка где размещаются экипировки
    const string EQUIP_PATH = "Equip";

    void KCItemsEquipDirectory()
    {
        pathNames.Insert(EQUIP_PATH);
    }
}
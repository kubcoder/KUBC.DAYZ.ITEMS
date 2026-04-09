modded class MissionServer
{
    private ref KCItemsSetsDirectory setsDirectory;

    private ref KCItemsCarsDirectory carsDirectory;

    private ref KCItemsEquipDirectory equipDirectory;
    
    override KCItemsEquipDirectory GetEquipDirectory()
    {
        return equipDirectory;
    }

    /// @brief  Инициализируем настройки мода.
    ///         В частности создаем структуру папочек, и файлы настроек 
    ///         по умолчанию.
    override void OnInit()
    {
        super.OnInit();
        setsDirectory = new KCItemsSetsDirectory();
        setsDirectory.CreatePaths();
        usersCmd.RegisterCommand(KCItemsCMDSave.CMD_NAME, new KCItemsCMDSave(setsDirectory));
        usersCmd.RegisterCommand(KCItemsCMDGet.CMD_NAME, new KCItemsCMDGet(setsDirectory));
        usersCmd.RegisterCommand(KCItemsCMDBat.CMD_NAME, new KCItemsCMDBat());
        usersCmd.RegisterCommand(KCItemsCMDBoat.CMD_NAME, new KCItemsCMDBoat());
        usersCmd.RegisterCommand(KCItemsCMDBox.CMD_NAME, new KCItemsCMDBox());
        carsDirectory = new KCItemsCarsDirectory();
        carsDirectory.CreatePaths();
        usersCmd.RegisterCommand(KCItemsCMDCar.CMD_NAME, new KCItemsCMDCar(carsDirectory));
        usersCmd.RegisterCommand(KCItemsCMDDel.CMD_NAME, new KCItemsCMDDel());
        usersCmd.RegisterCommand(KCItemsCMDDry.CMD_NAME, new KCItemsCMDDry());
        equipDirectory = new KCItemsEquipDirectory();
        equipDirectory.CreatePaths();
        usersCmd.RegisterCommand(KCItemsCMDEquip.CMD_NAME, new KCItemsCMDEquip(equipDirectory));
        KCItemsDictionary dictionary = new KCItemsDictionary();
        dictionary.Create();

    }
}
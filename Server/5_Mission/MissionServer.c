modded class MissionServer
{
    /// @brief  Инициализируем настройки мода.
    ///         В частности создаем структуру папочек, и файлы настроек 
    ///         по умолчанию.
    
    override void OnInit()
    {
        super.OnInit();      
        RegisterCommand(KCItemsCMDSpawn.CMD_NAME, new KCItemsCMDSpawn());
        RegisterCommand(KCItemsCMDDel.CMD_NAME, new KCItemsCMDDel());
        RegisterCommand(KCItemsCMDBox.CMD_NAME, new KCItemsCMDBox());
        RegisterCommand(KCItemsCMDSave.CMD_NAME, new KCItemsCMDSave());
        RegisterCommand(KCItemsCMDGet.CMD_NAME, new KCItemsCMDGet());
        RegisterCommand(KCItemsCMDRepair.CMD_NAME, new KCItemsCMDRepair());
        RegisterCommand(KCItemsCMDEquip.CMD_NAME, new KCItemsCMDEquip());
        RegisterCommand(KCItemsCMDCar.CMD_NAME, new KCItemsCMDCar());
        RegisterCommand(KCItemsCMDFence.CMD_NAME, new KCItemsCMDFence());
        RegisterCommand(KCItemsCMDBoat.CMD_NAME, new KCItemsCMDBoat());
        RegisterCommand(KCItemsCMDBat.CMD_NAME, new KCItemsCMDBat());
        RegisterCommand(KCItemsCMDDry.CMD_NAME, new KCItemsCMDDry());
        KCItems.CreatePaths();
        KCItemDesc.CreateDictionary();
    }
}
modded class MissionServer
{
    /** @brief  Инициализируем настройки мода.
    *           В частности создаем структуру папочек, и файлы настроек 
                по умолчанию.
    */
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
        KCItems.CreatePaths();
        KCItemDesc.CreateDictionary();
    }
    

}
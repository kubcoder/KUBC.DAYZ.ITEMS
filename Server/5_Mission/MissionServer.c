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
        KCItems.CreatePaths();
        KCItemDesc.CreateDictionary();
    }
    

}
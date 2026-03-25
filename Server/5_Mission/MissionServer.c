modded class MissionServer
{
    private ref KCItemsSetsDirectory setsDirectory;
    
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
        KCItemsDictionary dictionary = new KCItemsDictionary();
        dictionary.Create();

    }
}
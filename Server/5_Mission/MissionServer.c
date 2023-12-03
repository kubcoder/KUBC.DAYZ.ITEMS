modded class MissionServer
{
    /** @brief  Инициализируем настройки мода.
    *           В частности создаем структуру папочек, и файлы настроек 
                по умолчанию.
    */
    override void OnInit()
    {
        super.OnInit();      
        KCItems.CreatePaths();
        KCItemDesc.CreateDictonary();
    }
    

}
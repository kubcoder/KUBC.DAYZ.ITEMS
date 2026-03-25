/// @brief Команда выдачи сохраненного набора
class KCItemsCMDGet : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "get";

    override string GetName()
    {
        return KCItemsCMDGet.CMD_NAME;
    }

    private ref KCItemsSetsDirectory directory;

    void KCItemsCMDGet(KCItemsSetsDirectory setsDirectory)
    {
        directory = setsDirectory;
    }

    override bool Execute(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            KCPlayer.SendMessage(data.Owner,"","Не указано имя набора, выдача не выполнена");
            return true;
        }
        string setFileName = directory.FindDataFile(data.Arg[0], data.Owner);
        if (setFileName=="")
        {
            KCPlayer.SendMessage(data.Owner,"","Набор ["+data.Arg[0]+"] не существует");
            return true;
        }
        KCItemSet itemSet = directory.LoadFile(setFileName);
        if (itemSet==NULL)
        {
            KCPlayer.SendMessage(data.Owner,"","Ошибка загрузки набора ["+data.Arg[0]+"]");
            return true;
        }
        auto fabric = new KCItemFabric(data.GetTarget());
        bool created = false;
        foreach(auto itemData:itemSet.Items)
        {
            auto item = fabric.Create(itemData);
            if (item)
            {
                created = true;
            }
        }
        if (created)
        {
            KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Выдал ["+data.Arg[0]+"]");
            KCPlayer.SendMessage(data.Owner,"","Набор ["+data.Arg[0]+"] выдан");
        }
        else
        {
            KCPlayer.SendMessage(data.Owner,"","Набор ["+data.Arg[0]+"] не получилось выдать");
        }
        return true;
    }    
}
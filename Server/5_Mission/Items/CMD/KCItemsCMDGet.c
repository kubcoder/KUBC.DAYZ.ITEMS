/** @brief Команда выдачи сохраненного набора*/
class KCItemsCMDGet : KCUserCMD
{
    /** @brief название команды*/
    static const string CMD_NAME = "get";

    override string GetName()
    {
        return KCItemsCMDGet.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        if (data.Arg.Count()>0)
        {
            KCItemSet lItem;
            string FileName = KCItems.GetSetsFile(data.Arg[0],user);
            if (!FileExist(FileName))
            {
                FileName = KCItems.GetSetsFile(data.Arg[0]);
            }
            JsonFileLoader<KCItemSet>.JsonLoadFile(FileName, lItem);
            if (lItem)
            {
                foreach(KCSaveItem i:lItem.Items)
                {
                    i.Create(data.Player);
                }
                KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Прошлись по списку, вроде все выдали");
                return true;
            }
            else
            {
                KCPlayer.SendMessage(user,"","Не нашли файл");
            }
        }
        return false;
    }
}
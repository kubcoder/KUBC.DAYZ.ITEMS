/// @brief Команда сохранения набора итемов
class KCItemsCMDSave : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "save";
    
    /// @brief аргумент перезаписи существующего набора
    const string ARG_REPLACE = "r";
    
    /// @brief аргумент записи набора в общую папку админов
    const string ARG_SHARED = "s";
    
    /// @brief аргумент записи набора вокруг игрока
    const string ARG_GROUND = "g";
    
    /// @brief аргумент записи набора вокруг игрока с сохренением абсолютных координат
    const string ARG_ABSGROUND = "a";
    
    /// @brief Растояние поиска предметов по умолчанию
    const float DEF_DISTANCE = 3.0;

    private ref KCItemsSetsDirectory directory;

    void KCItemsCMDSave(KCItemsSetsDirectory setsDirectory)
    {
        directory = setsDirectory;
    }

    override string GetName()
    {
        return KCItemsCMDSave.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        string fileName = GetSettName(data);
        if (fileName == "")
        {
            KCPlayer.SendMessage(data.Owner,"", "Вы не указали имя набора, сохранение не выполнено");
            return true;
        }
        if (FileExist(fileName))
        {
            if (!data.ContainsArg(ARG_REPLACE))
            {
                KCPlayer.SendMessage(data.Owner,"", "Набор уже существует, сохранение не выполнено!");
                return true;
            }
        }
        
        KCItemSet iSet = GetSet(data);
        if (iSet.Items.Count() == 0)
        {
            KCPlayer.SendMessage(data.Owner,"", "Отсутсвуют предметы для сохранения, сохранение не выполнено!");
            return true;
        }
        
        JsonFileLoader<KCItemSet>.JsonSaveFile(fileName, iSet);
        KCPlayer.SendMessage(data.Owner,"","Набор " + data.Arg[0] + " сохранен!");
        return true;
    }

    private KCItemSet GetSet(KCTextCmd data)
    {
        KCItemSet iSet = new KCItemSet();
        iSet.NickName = data.Owner.GetIdentity().GetName();
        iSet.SteamID = data.Owner.GetIdentity().GetPlainId();
        if (!IsOnGround(data))
        {
            KCSaveItem itemData = GetHands(data.Owner);
            if (itemData)
            {
                iSet.Items.Insert(itemData);
            }
        }
        else
        {
            KCItemsGroundFinder finder = new KCItemsGroundFinder(directory.GetItemSetOptionsFile());
            KCSaveItemCollection itemsData = finder.FindItems(data.Owner, GetRadius(data), !data.ContainsArg(ARG_ABSGROUND));
            foreach(KCSaveItem id:itemsData)
            {
                iSet.Items.Insert(id);
            }
        }
        return iSet;
    }

    private float GetRadius(KCTextCmd data)
    {
        float result = data.GetFloat(ARG_GROUND, -1);
        if (result > -1)
        {
            return result;
        }
        result = data.GetFloat(ARG_ABSGROUND, -1);
        if (result > -1)
        {
            return result;
        }
        return DEF_DISTANCE;
    } 

    private KCSaveItem GetHands(PlayerBase player)
    {
        ItemBase itemHands = player.GetItemInHands();
        if (itemHands)
        {
            KCItemBuilder builder = new KCItemBuilder(itemHands);
            builder.Build();
            builder.ItemData.SlotID = 0;
            return builder.ItemData;
        }
        KCPlayer.SendMessage(player,"", "В руках не найден предмет для сохранеения");
        return NULL;
    }

    private bool  IsOnGround(KCTextCmd data)
    {
        if (data.ContainsArg(ARG_GROUND))
        {
            return true;
        }
        if (data.ContainsArg(ARG_ABSGROUND))
        {
            return true;
        }
        return false;
    }

    private string  GetSettName(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            return "";
        }
        string settName = data.Arg[0];
        if (settName == "")
        {
            return "";
        }
        if (data.ContainsArg(ARG_SHARED))
        {
            return directory.GetDataFile(settName);
        }
        else
        {
            return directory.GetDataFile(settName, data.Owner);
        }

    }
}
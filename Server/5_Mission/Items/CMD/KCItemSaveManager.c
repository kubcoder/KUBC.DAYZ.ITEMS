class KCItemSaveManager
{
    /// @brief аргумент перезаписи существующего набора
    const string ARG_REPLACE = "r";
    
    /// @brief аргумент записи набора в общую папку админов
    const string ARG_SHARED = "s";

    private ref KCItemsDirectory directory;

    private ref KCTextCmd cmdData;

    private string fileName;

    private string settName;

    private ref KCItemSet iSet;

    string GetName()
    {
        return settName;
    }

    void KCItemSaveManager(KCItemsDirectory setsDirectory, KCTextCmd data)
    {
        directory = setsDirectory;
        cmdData = data;
        settName = "";
        fileName = "";
    }

    void InitName(int namePosition = 1)
    {
        if (cmdData.Arg.Count()<namePosition)
        {
            return;
        }
        settName = cmdData.Arg[namePosition];
        if (settName == "")
        {
            return;
        }
        if (cmdData.ContainsArg(ARG_SHARED))
        {
            fileName = directory.GetDataFile(settName);
        }
        else
        {
            fileName = directory.GetDataFile(settName, cmdData.Owner);
        }
        iSet = new KCItemSet();
        iSet.NickName = cmdData.Owner.GetIdentity().GetName();
        iSet.SteamID = cmdData.Owner.GetIdentity().GetPlainId();
    }

    bool CanBeSave()
    {
        if (fileName == "")
        {
            return false;
        }
        if (!FileExist(fileName))
        {
            return true;
        }
        return cmdData.ContainsArg(ARG_REPLACE);
    }

    void Add(KCSaveItem itemData)
    {
        iSet.Items.Insert(itemData);
    }

    void Add(KCSaveItemCollection itemsData)
    {
        foreach(KCSaveItem id:itemsData)
        {
            iSet.Items.Insert(id);
        }
    }

    bool Save()
    {
        if (iSet.Items.Count() == 0)
        {
            return false;
        }
        JsonFileLoader<KCItemSet>.JsonSaveFile(fileName, iSet);
        return true;
    }
     
}
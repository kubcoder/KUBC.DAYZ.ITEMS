/// @brief Команда работы с машинами
class KCItemsCMDMoto : KCItemsCMDTransport
{
    /// @brief название команды
    static const string CMD_NAME = "moto";
    
    
    private ref KCItemsMotoDirectory directory;

    void KCItemsCMDMoto(KCItemsMotoDirectory motoDirectory)
    {
        directory = motoDirectory;
    }

    override string GetName()
    {
        return KCItemsCMDMoto.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            return true;
        }
        if (MustBeSpawn(data))
        {
            return SpawnMoto(data);
        }
        KCItemsMotoManager manager = GetManager(data);
        if (manager==NULL)
        {
            return true;
        }
        float power = DEF_IMPULSE;
        switch (data.Arg[0])
        {
            case ARG_REPAIR:
                manager.Repair();
                data.Message("Починили мотоцикл");
                return true;
            case ARG_REFUEL:
                manager.Refuel();
                data.Message("Заправили мотоцикл");
                return true;
            case ARG_LT:
                manager.SetLongLife();
                data.Message("Продлили время жизни мотоцикла");
                return true;
            case ARG_SAVE:
                return SaveMoto(data, manager);
        }
        return true;
    }

    bool SpawnMoto(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            data.MessageOwner("Не указано имя мотоцикла, выдача не выполнена");
            return true;
        }
        string setFileName = directory.FindDataFile(data.Arg[0], data.Owner);
        if (setFileName=="")
        {
            data.MessageOwner("Мотоцикл ["+data.Arg[0]+"] не существует");
            return true;
        }
        KCItemSet itemSet = directory.LoadFile(setFileName);
        if (itemSet==NULL)
        {
            data.MessageOwner("Ошибка загрузки мотоцикла ["+data.Arg[0]+"]");
            return true;
        }
        KCItemFabric fabric = new KCItemFabric(data.GetTarget());
        auto moto = MotorbikeScript.Cast(fabric.CreateOnRoute(itemSet.Items[0], data.GetFloat(ARG_DISTANCE, DEF_DIST)));
        if (moto==NULL)
        {
            data.MessageOwner("Ошибка создания мотоцикла ["+data.Arg[0]+"]");
            return true;
        }
        auto manager = new KCItemsMotoManager(moto);
        manager.Refuel();
        data.Message("Мотоцикл выдан ["+data.Arg[0]+"]");
        return true;
    }

    
    /// @brief Получить менеджер машины
    /// @param data 
    /// @return менеджер транспорта, если найден
    KCItemsMotoManager GetManager(KCTextCmd data)
    {
        float radius = data.GetFloat(ARG_DISTANCE, DEF_DIST);
        KCItemsMotoFinder motoFinder = new KCItemsMotoFinder();
        MotorbikeScript moto = motoFinder.GetMoto(data.GetTarget(), radius);
        if (moto)
        {
            return new KCItemsMotoManager(moto);
        }
        else
        {
            data.MessageOwner("Не нашли мотоцикл");
            return NULL;
        }
    }

    bool SaveMoto(KCTextCmd data,KCItemsMotoManager manager)
    {
        auto saveManager = new KCItemSaveManager(directory, data);
        saveManager.InitName(1);
        if (saveManager.GetName() == "")
        {
            data.MessageOwner("Вы не указали имя мотоцикла, сохранение не выполнено");
            return true;
        }
        if (!saveManager.CanBeSave())
        {
            data.MessageOwner("Мотоцикл уже существует, сохранение не выполнено!");
            return true;
        }
        KCItemBuilder builder = new KCItemBuilder(manager.target);
        builder.Build();
        saveManager.Add(builder.ItemData);
        saveManager.Save();
        data.MessageOwner("Мотоцикл " + saveManager.GetName() + " сохранена!");
        return true;
    }
}
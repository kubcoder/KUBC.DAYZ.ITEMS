/// @brief Команда работы с машинами
class KCItemsCMDCar : KCItemsCMDTransport
{
    /// @brief название команды
    static const string CMD_NAME = "car";
    
    
    private ref KCItemsCarsDirectory directory;

    void KCItemsCMDCar(KCItemsCarsDirectory carDirectory)
    {
        directory = carDirectory;
    }

    override string GetName()
    {
        return KCItemsCMDCar.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            return true;
        }
        if (MustBeSpawn(data))
        {
            return SpawnCar(data);
        }
        KCItemsCarManager manager = GetManager(data);
        if (manager==NULL)
        {
            return true;
        }
        float power = DEF_IMPULSE;
        switch (data.Arg[0])
        {
            case ARG_REPAIR:
                if (data.ContainsArg(ARG_ALL))
                {
                    manager.Repair(true);
                    KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Починили машину и все что было в ней");
                }
                else
                {
                    manager.Repair(false);
                    KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Починили машину и все её детали");
                }
                return true;
            case ARG_REFUEL:
                manager.Refuel();
                KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Заправили машину");
                return true;
            case ARG_LT:
                manager.SetLongLife();
                KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Продлили время жизни  машины");
                return true;
            case ARG_FRONT:
                power = data.GetFloat(ARG_FRONT, DEF_IMPULSE);
                manager.GetImpulseTool().FrontImpulse(power);
                KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Толкнули машину по направлению движения");
                return true;
            case ARG_BACK:
                power = data.GetFloat(ARG_BACK, DEF_IMPULSE);
                manager.GetImpulseTool().BackImpulse(power);
                KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Толкнули машину обратно направлению движения");
                return true;
            case ARG_LEFT:
                power = data.GetFloat(ARG_LEFT, DEF_IMPULSE);
                manager.GetImpulseTool().LeftImpulse(power);
                KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Толкнули машину в левый борт");
                return true;
            case ARG_RIGHT:
                power = data.GetFloat(ARG_RIGHT, DEF_IMPULSE);
                manager.GetImpulseTool().RightImpulse(power);
                KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Толкнули машину в правый борт");
                return true;
            case ARG_SAVE:
                return SaveCar(data, manager);
        }
        return true;
    }

    bool SpawnCar(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            KCPlayer.SendMessage(data.Owner,"","Не указано имя машины, выдача не выполнена");
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
        KCItemFabric fabric = new KCItemFabric(data.GetTarget());
        auto car = CarScript.Cast(fabric.CreateOnRoute(itemSet.Items[0], data.GetFloat(ARG_DISTANCE, DEF_DIST)));
        if (car==NULL)
        {
            KCPlayer.SendMessage(data.Owner,"","Ошибка создания машины ["+data.Arg[0]+"]");
            return true;
        }
        auto manager = new KCItemsCarManager(car);
        manager.Refuel();
        manager.Charge();
        KCPlayer.SendMessage(data.Owner,"","Машина выдана ["+data.Arg[0]+"]");
        if (data.Owner!=data.GetTarget())
        {
            KCPlayer.SendMessage(data.GetTarget(),data.Owner.GetIdentity().GetName(),"Машина выдана ["+data.Arg[0]+"]");
        }
        return true;
    }

    
    /// @brief Получить менеджер машины
    /// @param data 
    /// @return менеджер транспорта, если найден
    KCItemsCarManager GetManager(KCTextCmd data)
    {
        float radius = data.GetFloat(ARG_DISTANCE, DEF_DIST);
        KCItemsCarFinder carFinder = new KCItemsCarFinder();
        CarScript car = carFinder.GetCar(data.GetTarget(), radius);
        if (car)
        {
            return new KCItemsCarManager(car);
        }
        else
        {
            KCPlayer.SendMessage(data.Owner,"","Не нашли машину");
            return NULL;
        }
    }

    bool SaveCar(KCTextCmd data,KCItemsCarManager manager)
    {
        auto saveManager = new KCItemSaveManager(directory, data);
        saveManager.InitName(1);
        if (saveManager.GetName() == "")
        {
            KCPlayer.SendMessage(data.Owner,"", "Вы не указали имя машины, сохранение не выполнено");
            return true;
        }
        if (!saveManager.CanBeSave())
        {
            KCPlayer.SendMessage(data.Owner,"", "Машина уже существует, сохранение не выполнено!");
            return true;
        }
        KCItemBuilder builder = new KCItemBuilder(manager.target);
        builder.Build();
        saveManager.Add(builder.ItemData);
        saveManager.Save();
        KCPlayer.SendMessage(data.Owner,"","Машина " + saveManager.GetName() + " сохранена!");
        return true;
    }
}
/// @brief Команда работы с машинами
class KCItemsCMDCar : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "car";
    
    /// @brief Аргумент сохранения машины
    static const string ARG_SAVE = "save";
    
    /// @brief аргумент на какой дистанции создать машину
    static const string ARG_DISTANCE = "d";

    /// @brief Дистанция для поиска машины по умолчанию
    static const float DEF_DIST = 10;

    /// @brief аргумент заправки транспорта
    static const string ARG_REFUEL = "refuel";
    
    /// @brief аргумент ремонта машины
    static const string ARG_REPAIR = "repair";
    
    /// @brief Аргумент для толчка машины вперед
    static const string ARG_FRONT = "f";

    /// @brief Аргумент для толчка машины назад
    static const string ARG_BACK = "b";

    /// @brief Аргумент для толчка машины влево
    static const string ARG_LEFT = "l";

    /// @brief Аргумент для толчка машины вправо
    static const string ARG_RIGHT = "r";

    /// @brief Импульс по умолчанию
    static const float DEF_IMPULSE = 10000;

    /// @brief Аргумент для полной починки машины
    ///        включая инвентарь
    static const string ARG_ALL = "all";


    override string GetName()
    {
        return KCItemsCMDCar.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        if (MustBeSpawn(data))
        {
            KCItemsCarFabric fabric = new KCItemsCarFabric();  
            fabric.Create(data.Arg[0], user, data.Player);
        }
        else
        {
            KCItemsCarManager manager = GetManager(data);
            if (manager)
            {
                float power = DEF_IMPULSE;
                switch (data.Arg[0])
                {
                    case ARG_REPAIR:
                        if (data.ContainsArg(ARG_ALL))
                        {
                            manager.Repair(true);
                            KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Починили машину и все что было в ней");
                        }
                        else
                        {
                            manager.Repair(false);
                            KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Починили машину и все её детали");
                        }
                        return true;
                    case ARG_REFUEL:
                        manager.Refuel();
                        manager.SetLongLife();
                        KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Заправили машину");
                        return true;
                    case ARG_FRONT:
                        power = data.GetFloat(ARG_FRONT, DEF_IMPULSE);
                        manager.GetImpulseTool().FrontImpulse(power);
                        KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Толкнули машину по направлению движения");
                        return true;
                    case ARG_BACK:
                        power = data.GetFloat(ARG_BACK, DEF_IMPULSE);
                        manager.GetImpulseTool().BackImpulse(power);
                        KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Толкнули машину обратно направлению движения");
                        return true;
                    case ARG_LEFT:
                        power = data.GetFloat(ARG_LEFT, DEF_IMPULSE);
                        manager.GetImpulseTool().LeftImpulse(power);
                        KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Толкнули машину в левый борт");
                        return true;
                    case ARG_RIGHT:
                        power = data.GetFloat(ARG_RIGHT, DEF_IMPULSE);
                        manager.GetImpulseTool().RightImpulse(power);
                        KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Толкнули машину в правый борт");
                        return true;
                    case ARG_SAVE:
                        return manager.Save(data.Player, data);
                }
            }

        }
        return true;
    }


    /// @brief Проверяем нужно ли создать лодку
    /// @param data данные команды
    /// @return истина если лодка должна быть создана
    bool MustBeSpawn(KCTextCmd data)
    {
        if (data.ContainsArg(ARG_REPAIR))
            return false;
        if (data.ContainsArg(ARG_REFUEL))
            return false;
        if (data.ContainsArg(ARG_FRONT))
            return false;
        if (data.ContainsArg(ARG_BACK))
            return false;
        if (data.ContainsArg(ARG_LEFT))
            return false;
        if (data.ContainsArg(ARG_RIGHT))
            return false;
        if (data.ContainsArg(ARG_SAVE))
            return false;
        return true;
    }

    /// @brief Получить менеджер машины
    /// @param data 
    /// @return менеджер транспорта, если найден
    KCItemsCarManager GetManager(KCTextCmd data)
    {
        float radius = data.GetFloat(ARG_DISTANCE, DEF_DIST);
        KCItemsCarFinder carFinder = new KCItemsCarFinder();
        CarScript car = carFinder.GetCar(data.Player, radius);
        if (car)
        {
            return new KCItemsCarManager(car);
        }
        else
        {
            KCPlayer.SendMessage(data.Player,"","Не нашли машину");
            return NULL;
        }
    }    
}
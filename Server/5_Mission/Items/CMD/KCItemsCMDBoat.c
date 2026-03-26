/// @brief Команда работы с лодочками
class KCItemsCMDBoat : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "boat";

    /// @brief аргумент на какой дистанции создать лодку
    const string ARG_DISTANCE = "d";

    /// @brief Аргумент для починки лодки
    const string ARG_REPAIR = "repair";

    /// @brief Аргумент для заправки
    const string ARG_REFUEL = "refuel";

    /// @brief Аргумент для толчка лодки вперед
    const string ARG_FRONT = "f";

    /// @brief Аргумент для толчка лодки назад
    const string ARG_BACK = "b";

    /// @brief Аргумент для толчка лодки влево
    const string ARG_LEFT = "l";

    /// @brief Аргумент для толчка лодки вправо
    const string ARG_RIGHT = "r";

    /// @brief Импульс по умолчанию
    const float DEF_IMPULSE = 10000;

    /// @brief Аргумент для полной починки лодки
    ///        включая инвентарь
    const string ARG_ALL = "all";
    
     
    override string GetName()
    {
        return KCItemsCMDBoat.CMD_NAME;
    }

    
    override bool Execute(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            return true;
        }
        if (MustBeSpawn(data))
        {
            SpawnBoat(data);
            return true;
        }
        
        KCItemsBoatManager manager = GetManager(data);
        if (manager==NULL)
        {
            return true;
        }
        if (data.ContainsArg(ARG_REPAIR))
        {
            if (data.ContainsArg(ARG_ALL))
            {
                manager.Repair(true);
                KCPlayer.SendMessage(data.Player,data.Owner.GetIdentity().GetName(),"Починили лодку и все что было в ней");
            }
            else
            {
                manager.Repair(false);
                KCPlayer.SendMessage(data.Player,data.Owner.GetIdentity().GetName(),"Починили лодку и все её детали");
            }
            return true;
        }
        if (data.ContainsArg(ARG_REFUEL))
        {
            manager.Refuel();
            manager.SetLongLife();
            KCPlayer.SendMessage(data.Player,data.Owner.GetIdentity().GetName(),"Заправили лодку");
            return true;
        }
        float power = DEF_IMPULSE;
        if (data.ContainsArg(ARG_FRONT))
        {
            power = data.GetFloat(ARG_FRONT, DEF_IMPULSE);
            manager.GetImpulseTool().FrontImpulse(power);
            KCPlayer.SendMessage(data.Player,data.Owner.GetIdentity().GetName(),"Толкнули лодку по направлению движения");
            return true;
        }
        if (data.ContainsArg(ARG_BACK))
        {
            power = data.GetFloat(ARG_BACK, DEF_IMPULSE);
            manager.GetImpulseTool().BackImpulse(power);
            KCPlayer.SendMessage(data.Player,data.Owner.GetIdentity().GetName(),"Толкнули лодку обратно направлению движения");
            return true;
        }
        if (data.ContainsArg(ARG_LEFT))
        {
            power = data.GetFloat(ARG_LEFT, DEF_IMPULSE);
            manager.GetImpulseTool().LeftImpulse(power);
            KCPlayer.SendMessage(data.Player,data.Owner.GetIdentity().GetName(),"Толкнули лодку в левый борт");
            return true;
        }
        if (data.ContainsArg(ARG_RIGHT))
        {
            power = data.GetFloat(ARG_RIGHT, DEF_IMPULSE);
            manager.GetImpulseTool().RightImpulse(power);
            KCPlayer.SendMessage(data.Player,data.Owner.GetIdentity().GetName(),"Толкнули лодку в правый борт");
            return true;
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
        return true;
    }


    /// @brief Заспавнить лодочку
    /// @param pos где спавнить 
    void SpawnBoat(KCTextCmd data)
    {
        vector pos = GetPosition(data);
        if (pos!=vector.Zero)
        {
            BoatScript boat = BoatScript.Cast(GetGame().CreateObject( data.Arg[0], pos));
            if (boat)
            {
                boat.GetInventory().CreateAttachment("SparkPlug");
                KCItemsBoatManager manager = new KCItemsBoatManager(boat);
                manager.Refuel();
                manager.SetLongLife();
            }
        }
    }
    /// @brief Получить координату спавна лодки
    /// @param data данные команды
    /// @return координаты в море, или vector.Zero если расчетная точка не в море
    vector GetPosition(KCTextCmd data)
    {
        float distance = data.GetFloat(ARG_DISTANCE, 10);
        auto player = data.GetTarget();
        vector pos = player.GetPosition() + player.GetDirection() * distance;
        if (GetGame().SurfaceIsSea(pos[0],pos[2]))
        {
            pos[1] = GetGame().SurfaceGetSeaLevel();
            return pos;
        }
        else
        {
            KCPlayer.SendMessage(player,"","Координата не в море лодка создана не будет");
        }
        return vector.Zero;
    }

    KCItemsBoatManager GetManager(KCTextCmd data)
    {
        float radius = data.GetFloat(ARG_DISTANCE, 10);
        auto player = data.GetTarget();
        KCItemsBoatFinder boatFinder = new KCItemsBoatFinder();
        BoatScript boat = boatFinder.GetBoat(player.GetPosition(), radius);
        if (boat)
        {
            return new KCItemsBoatManager(boat);
        }
        else
        {
            KCPlayer.SendMessage(player,"","Не нашли лодку");
            return NULL;
        }
    }
}
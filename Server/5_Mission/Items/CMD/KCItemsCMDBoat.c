/// @brief Команда работы с лодочками
class KCItemsCMDBoat : KCItemsCMDTransport
{
    /// @brief название команды
    static const string CMD_NAME = "boat";
     
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
                data.Message("Починили лодку и все что было в ней");
            }
            else
            {
                manager.Repair(false);
                data.Message("Починили лодку и все её детали");
            }
            return true;
        }
        if (data.ContainsArg(ARG_REFUEL))
        {
            manager.Refuel();
            manager.SetLongLife();
            data.Message("Заправили лодку");
            return true;
        }
        float power = DEF_IMPULSE;
        if (data.ContainsArg(ARG_FRONT))
        {
            power = data.GetFloat(ARG_FRONT, DEF_IMPULSE);
            manager.GetImpulseTool().FrontImpulse(power);
            data.Message("Толкнули лодку по направлению движения");
            return true;
        }
        if (data.ContainsArg(ARG_BACK))
        {
            power = data.GetFloat(ARG_BACK, DEF_IMPULSE);
            manager.GetImpulseTool().BackImpulse(power);
            data.Message("Толкнули лодку обратно направлению движения");
            return true;
        }
        if (data.ContainsArg(ARG_LEFT))
        {
            power = data.GetFloat(ARG_LEFT, DEF_IMPULSE);
            manager.GetImpulseTool().LeftImpulse(power);
            data.Message("Толкнули лодку в левый борт");
            return true;
        }
        if (data.ContainsArg(ARG_RIGHT))
        {
            power = data.GetFloat(ARG_RIGHT, DEF_IMPULSE);
            manager.GetImpulseTool().RightImpulse(power);
            data.Message("Толкнули лодку в правый борт");
            return true;
        }
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
            data.MessageOwner("Координата не в море лодка создана не будет");
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
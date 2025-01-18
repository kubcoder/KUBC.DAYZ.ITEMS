/** @brief Команда работы с лодочками*/
class KCItemsCMDBoat : KCUserCMD
{
    /** @brief название команды*/
    static const string CMD_NAME = "boat";

    /** @brief аргумент пнуть машину вперед*/
    static const string ARG_DISTANCE = "d";

    override string GetName()
    {
        return KCItemsCMDBoat.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (data.Arg.Count()>0)
        {
            if (!data.Player)
            {
                data.Player = user;
            }
            SpawnBoat(data);
        }
        return true;
    }

    /// @brief Заспавнить лодочку
    /// @param pos где спавнить 
    /// @param className 
    void SpawnBoat(KCTextCmd data)
    {
        vector pos = GetPosition(data);
        if (pos!=vector.Zero)
        {
            Boat boat = Boat.Cast(GetGame().CreateObject( data.Arg[0], pos));
        }
    }

    vector GetPosition(KCTextCmd data)
    {
        float distance = data.GetFloat("d", 10);
        Log("Дистанция создания лодки: " + distance);
        vector pos = data.Player.GetPosition() + data.Player.GetDirection() * distance;
        if (GetGame().SurfaceIsSea(pos[0],pos[2]))
        {
            pos[1] = GetGame().SurfaceGetSeaLevel();
            return pos;
        }
        else
        {
            Log("Координата это не море");
        }
        return vector.Zero;
    }
}
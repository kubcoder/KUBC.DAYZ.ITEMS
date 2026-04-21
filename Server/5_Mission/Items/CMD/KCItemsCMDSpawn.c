/// @brief Команда спавна игрового итема
class KCItemsCMDSpawn : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "spawn";
    
    /// @brief аргумент задающий кол-во создаваемых итемов
    const string PARAM_COUNT = "c";
    
    /// @brief аргумент задающий размещение игрового итема на земле
    const string PARAM_GROUND = "g";
    
    override string GetName()
    {
        return KCItemsCMDSpawn.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            data.MessageOwner("Не указан предмет для спавна");
            return true;
        }
        auto spawner = new KCItemsSpawner(data.GetTarget());
        spawner.ItemName = data.Arg[0];
        spawner.Count = data.GetInt(PARAM_COUNT, 1);
        if (data.ContainsArg(PARAM_GROUND))
        {
            spawner.Distance = data.GetFloat(PARAM_GROUND, 0);
        }
        int spawnCount = spawner.Spawn();
        SendMessage(data, spawnCount, spawner.ItemName);
        return true;
    }

    private bool SendMessage(KCTextCmd data, int spawnCount, string className)
    {
        if (spawnCount==0)
        {
            data.MessageOwner("Несмогли выдать "+ className);
        }
        else
        {
            data.Message("Выдали ["+className+"] "+spawnCount+"шт.");
        }
        return true;
    }

    
}
/** @brief Команда работы с заборами*/
class KCItemsCMDFence : KCUserCMD
{
    /** @brief название команды*/
    static const string CMD_NAME = "fence";
    
    /** @brief Радиус поиска заборов по умолчанию*/
    static const float DEF_RADIUS = 10;

    override string GetName()
    {
        return KCItemsCMDFence.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        float radius = KCItemsCMDFence.DEF_RADIUS;
        if(data.Arg.Count()>1)
        {
            radius = data.Arg[1].ToFloat();
            if (radius==0)
            {
                radius = KCItemsCMDFence.DEF_RADIUS;
            }
        }
        ref array<Object> nearest_objects = new array<Object>;
        ref array<CargoBase> proxy_cargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition ( user.GetPosition(), radius, nearest_objects, proxy_cargos);
        foreach(Object obj:nearest_objects)
        {
            Fence cFence = Fence.Cast(obj);
            if (cFence)
            {
                switch (data.Arg[0])
                {
                    case "code":
                        if(cFence.IsLocked())
                        {
                            CombinationLock cLock = cFence.GetCombinationLock();
                            if (cLock)
                            {
                                KCPlayer.SendMessage(user,"", "Комбинация замка:" + cLock.m_CombinationLocked);                         
                            }
                        }
                        break;
                }
            }
        }
        return true;
        
    }
}
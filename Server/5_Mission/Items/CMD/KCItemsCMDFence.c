/// @brief Команда работы с заборами
class KCItemsCMDFence : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "fence";
    
    /// @brief Радиус поиска заборов по умолчанию
    const float DEF_RADIUS = 10;

    /// @brief Аргумент поиска кода замка
    const string ARG_CODE = "code";

    override string GetName()
    {
        return KCItemsCMDFence.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
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
        GetGame().GetObjectsAtPosition ( data.GetTarget().GetPosition(), radius, nearest_objects, proxy_cargos);
        foreach(Object obj:nearest_objects)
        {
            Fence cFence = Fence.Cast(obj);
            if (cFence)
            {
                switch (data.Arg[0])
                {
                    case ARG_CODE:
                        if(cFence.IsLocked())
                        {
                            CombinationLock cLock = cFence.GetCombinationLock();
                            if (cLock)
                            {
                                data.Message("Комбинация замка:" + cLock.m_CombinationLocked);
                            }
                        }
                        break;
                }
            }
        }
        return true;
    }
}
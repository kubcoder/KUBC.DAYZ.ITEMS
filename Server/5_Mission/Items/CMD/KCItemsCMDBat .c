/// @brief Команда работы с батарейками
class KCItemsCMDBat : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "bat";

    /// @brief Аргумент для зарядки батареи
    const string ARG_CHARGE = "charge";

    /// @brief Аргумент для разрядки батареи
    const string ARG_DISCHARGE = "discharge";

    override string GetName()
    {
        return KCItemsCMDBat.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        PlayerBase target = data.GetTarget();
        ItemBase itemHands = target.GetItemInHands();
        if(!itemHands)
        {
            KCPlayer.SendMessage(data.Owner,"BAT","Не нашли объект для зарядки");
            return true;
        }
        ComponentEnergyManager compEM = itemHands.GetCompEM();
        if (!compEM)
        {
            KCPlayer.SendMessage(data.Owner,"BAT","Объект не иммет компонента энергии");
            return true;
        }
        switch (data.Arg[0])
        {
            case ARG_DISCHARGE:
                compEM.ConsumeEnergy(compEM.GetEnergyMax());
                compEM.Synch();
                KCPlayer.SendMessage(target, data.Owner.GetIdentity().GetName(),"Разрядили в ноль");
                break;
            case ARG_CHARGE:
                float addEnergy = compEM.GetEnergyMax() - compEM.GetEnergy();
                compEM.AddEnergy(addEnergy);
                compEM.Synch();
                KCPlayer.SendMessage(target, data.Owner.GetIdentity().GetName(),"Зарядили до упора");
                break;
        }
        return true;
    }
}
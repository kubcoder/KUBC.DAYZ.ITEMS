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
            data.MessageOwner("Не нашли объект для зарядки");
            return true;
        }
        ComponentEnergyManager compEM = itemHands.GetCompEM();
        if (!compEM)
        {
            data.MessageOwner("Объект не иммет компонента энергии");
            return true;
        }
        switch (data.Arg[0])
        {
            case ARG_DISCHARGE:
                compEM.ConsumeEnergy(compEM.GetEnergyMax());
                compEM.Synch();
                data.Message("Разрядили "+itemHands.GetDisplayName()+" в ноль");
                break;
            case ARG_CHARGE:
                float addEnergy = compEM.GetEnergyMax() - compEM.GetEnergy();
                compEM.AddEnergy(addEnergy);
                compEM.Synch();
                data.Message("Зарядили "+itemHands.GetDisplayName()+" до упора");
                break;
        }
        return true;
    }
}
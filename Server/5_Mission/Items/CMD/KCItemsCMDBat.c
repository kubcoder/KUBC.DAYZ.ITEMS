/// @brief Команда работы с батарейками
class KCItemsCMDBat : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "bat";

    /// @brief Аргумент для зарядки батареи
    static const string ARG_CHARGE = "charge";

    /// @brief Аргумент для разрядки батареи
    static const string ARG_DISCHARGE = "discharge";

    override string GetName()
    {
        return KCItemsCMDBat.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        ItemBase itemHands = data.Player.GetItemInHands();
        if(!itemHands)
        {
            KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Не нашли объект для зарядки");
            return true;
        }
        ComponentEnergyManager compEM = itemHands.GetCompEM();
        if (!compEM)
        {
            KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Объект не иммет компонента энергии");
            return true;
        }
        switch (data.Arg[0])
        {
            case ARG_DISCHARGE:
                compEM.ConsumeEnergy(compEM.GetEnergyMax());
                compEM.Synch();
                KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Разрядили в ноль");
                break;
            case ARG_CHARGE:
                float addEnergy = compEM.GetEnergyMax() - compEM.GetEnergy();
                compEM.AddEnergy(addEnergy);
                compEM.Synch();
                KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Зарядили до упора");
                break;
        }
        return true;
    }
}
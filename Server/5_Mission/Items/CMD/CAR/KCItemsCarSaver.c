class KCItemsCarSaver : KCItemsCarFile
{
    /// @brief Аргумент вызывающий перезапись машины
    static const string ARG_REPLACE = "r";
        
    /// @brief Аргумент вызывающий сохранение транспорта в общуюю папку
    static const string ARG_SHARED = "s";

    /// @brief Какая машина будет использоваться
    ///        при манипуляциях
    CarScript car;
    
    void KCItemsCarSaver(CarScript target)
    {
        car=target;
    }

    /// @brief Сохранить машину на диск сервера
    /// @param user возле какого игрока шукать тачилу
    /// @param data данные команды
    /// @return истина если машина сохранилась
    bool SaveCar(PlayerBase user, KCTextCmd data)
    {
        string SettName = "";
        if (data.Arg.Count()>1)
        {
            SettName = data.Arg[1];
        }
        if (SettName=="")
        {
            return false;
        }
        bool Replace = data.ContainsArg(ARG_REPLACE);
        bool Shared = data.ContainsArg(ARG_SHARED);
        
        KCItemSet cSet = new KCItemSet();
        cSet.NickName = user.GetIdentity().GetName();
        cSet.SteamID = user.GetIdentity().GetPlainId();
        cSet.Items.Insert(KCSaveItem.FromCar(car));
        string FileName ="";
        if (Shared)
        {
            FileName = GetCarFile(SettName);
        }
        else
        {
            FileName = GetCarFile(SettName, user);
        }
        if (FileExist(FileName))
        {
            if(Replace)
            {
                JsonFileLoader<KCItemSet>.JsonSaveFile(FileName, cSet);
                KCPlayer.SendMessage(user,"","Машина " + SettName + " обновлен.");
                return true;
            }
            else
            {
                KCPlayer.SendMessage(user,"","Файл уже существует, сохранение не выполнено");
                return false;
            }
        }
        else
        {
            JsonFileLoader<KCItemSet>.JsonSaveFile(FileName, cSet);
            KCPlayer.SendMessage(user,"","Машина " + SettName + " создана."); 
            return true;               
        }
    }
}
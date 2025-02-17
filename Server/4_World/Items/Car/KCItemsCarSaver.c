class KCItemsCarSaver
{
    /// @brief Аргумент вызывающий перезапись машины
    static const string ARG_REPLACE = "r";
        
    /// @brief Аргумент вызывающий сохранение транспорта в общуюю папку
    static const string ARG_SHARED = "s";

    /*
    /// @brief Сохранить машину на диск сервера
    /// @param user возле какого игрока шукать тачилу
    /// @param data данные команды
    /// @return истина если машина сохранилась
    bool SaveCar(PlayerBase user, KCTextCmd data)
    {
        CarScript car = GetTransport(user);
        if (car)
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
                FileName = KCItems.GetCarFile(SettName);
            }
            else
            {
                FileName = KCItems.GetCarFile(SettName, user);
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
        else
        {
            KCPlayer.SendMessage(user,"","Не смогли найти транспорт рядом");
        }
        return false;
    }
        */
}
/// @brief Фабрика автомобильчиков
class KCItemsCarFabric
{
    /// @brief На какой дистанции создаем машину
    static const float DEF_DISTANCE = 10;
    
    /// @brief Создать транспорт
    /// @param fileName имя файла введенное пользователем
    /// @param user пользователь который выполнил команду
    /// @param target кому выдавать транспорт
    /// @return объект машина, если таковую удалось создать
    CarScript Create(string setName, PlayerBase user, PlayerBase target)
    {
        string FileName = GetCarFile(setName, user);
        if (!FileExist(FileName))
        {
            FileName = GetCarFile(setName);
        }
        if (FileExist(FileName))
        {
            return GetCar(FileName, target, user);
        }
        else
        {
            KCPlayer.SendMessage(user,"","На нашли файл сохраненной машины");
        }
        return NULL;
    }

    /// @brief Полный путь к набору машины
    /// @param SettName имя сохраненной тачилы
    /// @param player для какого игрока получать папку, если указан NULL
    ///               то будет возвращено корневая папка машин
    string GetCarFile(string SetName, PlayerBase player = NULL)
    {
        if (player)
        {
            MakeDirectory(KCItems.GetCarsPath() + "\\" + player.GetIdentity().GetPlainId());
            return KCItems.GetCarsPath() + "\\" + player.GetIdentity().GetPlainId() + "\\" + SetName + ".json";
        }
        else
        {
            return KCItems.GetCarsPath() + "\\" + SetName + ".json";
        }
    }
    
    /// @brief Выдать машину
    /// @param FileName - какую машину выдать
    /// @param player кому выдать
    /// @param user кто выдает
    CarScript GetCar(string FileName, PlayerBase player, PlayerBase user)
    {
        KCItemSet cSet;
        JsonFileLoader<KCItemSet>.JsonLoadFile(FileName, cSet);
        if (cSet)
        {
            EntityAI carItem = cSet.Items.Get(0).CreateOnRoute(player, DEF_DISTANCE);
            CarScript car = CarScript.Cast(carItem);
            if (car)
            {
                KCItemsCarManager manager = new KCItemsCarManager(car);
                manager.Refuel();
                KCPlayer.SendMessage(player,user.GetIdentity().GetName(),"Транспорт выдан");
                return car;
            }
            else
            {
                KCPlayer.SendMessage(user,"","Не смогли создать машину в мире");
            }
        }
        else
        {
            KCPlayer.SendMessage(user,"","Файл поврежден, создание невозможно");            
        }
        return NULL;
    }
}
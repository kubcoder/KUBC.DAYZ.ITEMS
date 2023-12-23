/** @brief Команда работы с машинами*/
class KCItemsCMDCar : KCUserCMD
{
    /** @brief название команды*/
    static const string CMD_NAME = "car";
    /** @brief Аргумент сохранения машины*/
    static const string ARG_SAVE = "save";
    /** @brief Аргумент вызывающий перезапись машины*/
    static const string ARG_REPLACE = "r";
    /** @brief Аргумент вызывающий сохранение транспорта в общуюю папку*/
    static const string ARG_SHARED = "s";
    /** @brief На какой дистанции создаем машину*/
    static const float DEF_DISTANCE = 10;
    /** @brief аргумент заправки транспорта*/
    static const string ARG_REFUEL = "refuel";
    /** @brief аргумент ремонта машины*/
    static const string ARG_REPAIR = "repair";
    /** @brief аргумент пнуть машину вперед*/
    static const string ARG_FRONTIMPULSE = "f";
    static const float DEF_IMPULSE = 10000;
    /** @brief аргумент пнуть машину назад*/
    static const string ARG_BACKIMPULSE = "b";
    /** @brief аргумент пнуть машину в левую бочину*/
    static const string ARG_LEFTIMPULSE = "l";
    /** @brief аргумент пнуть машину в правую бочину*/
    static const string ARG_RIGHTIMPULSE = "r";


    override string GetName()
    {
        return KCItemsCMDCar.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (data.Arg.Count()>0)
        {
            CarScript car;
            if (!data.Player)
            {
                data.Player = user;
            }
            if (data.Arg[0]==ARG_SAVE)
            {
                return SaveCar(user, data);
            }
            if (data.Arg[0]==ARG_REFUEL)
            {
                car = GetTransport(data.Player);
                if (car)
                {
                    Refuel(car);
                    KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Тачилу заправили");
                    return true;
                }
                else
                {
                    KCPlayer.SendMessage(user,"","не нашли машину для заправки");
                }
                return false;
            }
            if (data.Arg[0]==ARG_REPAIR)
            {
                car = GetTransport(data.Player);
                if (car)
                {
                    Repair(car);
                    KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Тачилу подшаманили, как новая");
                }
                else
                {
                    KCPlayer.SendMessage(user,"","не нашли машину для ремонта");
                }
                return false;
            }
            float power;
            vector pVector;
            if(data.Arg[0]==ARG_FRONTIMPULSE)
            {
                if (data.Arg.Count()>1)
                {
                    power = data.Arg[1].ToFloat();
                }
                if (power==0)
                {
                    power = DEF_IMPULSE;
                }
                car = GetTransport(data.Player);
                if (car)
                {
                    KCPlayer.SendMessage(user,"","Толкнули тачилу в зад от души");
                    pVector = car.GetDirection()*power;
                    dBodyApplyImpulse(car, pVector);
                    Log("Толкнули тачилу по вектору: " + pVector);
                    return true;
                }
                else
                {
                    KCPlayer.SendMessage(user,"","не нашли машину");
                }
                return false;
            }
            if(data.Arg[0]==ARG_BACKIMPULSE)
            {
                if (data.Arg.Count()>1)
                {
                    power = data.Arg[1].ToFloat();
                }
                if (power==0)
                {
                    power = DEF_IMPULSE;
                }
                car = GetTransport(data.Player);
                if (car)
                {
                    KCPlayer.SendMessage(user,"","Толкнули тачилу в лоб от души");
                    pVector = vector.RotateAroundZeroDeg(car.GetDirection(), vector.Up, 180);
                    pVector = pVector * power;
                    dBodyApplyImpulse(car, pVector);
                    Log("Толкнули тачилу по вектору: " + pVector);
                    return true;
                }
                else
                {
                    KCPlayer.SendMessage(user,"","не нашли машину");
                }
                return false;
            }
            if(data.Arg[0]==ARG_LEFTIMPULSE)
            {
                if (data.Arg.Count()>1)
                {
                    power = data.Arg[1].ToFloat();
                }
                if (power==0)
                {
                    power = DEF_IMPULSE;
                }
                car = GetTransport(data.Player);
                if (car)
                {
                    KCPlayer.SendMessage(user,"","Толкнули тачилу в левую бочину от души");
                    pVector = vector.RotateAroundZeroDeg(car.GetDirection(), vector.Up, 90);
                    pVector = pVector * power;
                    dBodyApplyImpulse(car, pVector);
                    Log("Толкнули тачилу по вектору: " + pVector);
                    return true;
                }
                else
                {
                    KCPlayer.SendMessage(user,"","не нашли машину");
                }
                return false;
            }
            if(data.Arg[0]==ARG_RIGHTIMPULSE)
            {
                if (data.Arg.Count()>1)
                {
                    power = data.Arg[1].ToFloat();
                }
                if (power==0)
                {
                    power = DEF_IMPULSE;
                }
                car = GetTransport(data.Player);
                if (car)
                {
                    KCPlayer.SendMessage(user,"","Толкнули тачилу в правую бочину от души");
                    pVector = vector.RotateAroundZeroDeg(car.GetDirection(), vector.Up, -90);
                    pVector = pVector * power;
                    dBodyApplyImpulse(car, pVector);
                    Log("Толкнули тачилу по вектору: " + pVector);
                }
                else
                {
                    KCPlayer.SendMessage(user,"","не нашли машину");
                }
                return false;
            }

            string FileName = KCItems.GetCarFile(data.Arg[0], user);
            if (!FileExist(FileName))
            {
                FileName = KCItems.GetCarFile(data.Arg[0]);
            }
            if (FileExist(FileName))
            {
                GetCar(FileName, data.Player, user);
                return true;
            }
            KCPlayer.SendMessage(user,"","Не смогли понять чего вы хотите");

        }
        return false;
    }

    void Refuel(Car vehicle)
    {
        if(vehicle)
        {
            float fuelReq = vehicle.GetFluidCapacity( CarFluid.FUEL ) - (vehicle.GetFluidCapacity( CarFluid.FUEL ) * vehicle.GetFluidFraction( CarFluid.FUEL ));
            float oilReq = vehicle.GetFluidCapacity( CarFluid.OIL ) - (vehicle.GetFluidCapacity( CarFluid.OIL ) * vehicle.GetFluidFraction( CarFluid.OIL ));
            float coolantReq = vehicle.GetFluidCapacity( CarFluid.COOLANT ) - (vehicle.GetFluidCapacity( CarFluid.COOLANT ) * vehicle.GetFluidFraction( CarFluid.COOLANT ));
            float brakeReq = vehicle.GetFluidCapacity( CarFluid.BRAKE ) - (vehicle.GetFluidCapacity( CarFluid.BRAKE ) * vehicle.GetFluidFraction( CarFluid.BRAKE ));
            vehicle.Fill( CarFluid.FUEL, fuelReq );
            vehicle.Fill( CarFluid.OIL, oilReq );
            vehicle.Fill( CarFluid.COOLANT, coolantReq );
            vehicle.Fill( CarFluid.BRAKE, brakeReq );
            vehicle.SetLifetimeMax(3888000);
            vehicle.SetLifetime(3888000);
            //TODO: Тут добавить поиск и зарядку АКБ
            vehicle.SetSynchDirty();
            vehicle.Synchronize();	

        }	
    }

    /** @brief Ремонт машины, включая все запчасти, если они убиты в гавно то будет полная замена*/
    void Repair(CarScript carEntity)
    {
        if ( carEntity == NULL || carEntity == NULL)
                return;
        KCItems.Log("Начинаем ремонт машины");
        if (carEntity)
        {
            carEntity.Repair();
        }
        else
        {
            KCItems.Log("Машина не найдена", KCLogLevel.Warning);
        }
    }

    /** @brief Выдать машину
    *   @param FileName - какую машину выдать
    *   @param player кто выдает
    *   @param user кому выдать
    */
    bool GetCar(string FileName, PlayerBase player, PlayerBase user)
    {
        KCItemSet cSet;
        JsonFileLoader<KCItemSet>.JsonLoadFile(FileName, cSet);
        if (cSet)
        {
            EntityAI carItem = cSet.Items.Get(0).CreateOnRoute(player, DEF_DISTANCE);
            Car car = Car.Cast(carItem);
            if (car)
            {
                Refuel(car);
                KCPlayer.SendMessage(player,user.GetIdentity().GetName(),"Транспорт выдан");
                return true;
            }
            else
            {
                KCPlayer.SendMessage(user,"","Не смогли создать машину в мире");
                return false;
            }
        }
        else
        {
            KCPlayer.SendMessage(user,"","Файл поврежден, создание невозможно");            
            return false;
        }
    }

    /** @brief Сохранить машину на диск сервера
    *   @param user возле какого игрока шукать тачилу
    *   @param data данные команды
    *   @return истина если машина сохранилась
    */
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

    /** @brief Найти машину рядом с игроком
    *   @param player возле какого игрока шукаем тачилу
    *   @return Найденный транспорт, или null если транспорт найти не удалось
    */
    CarScript GetTransport(PlayerBase player)
    {
        Log("Начинаем поиск транспорта");
        CarScript car;
        HumanCommandVehicle hcv = player.GetCommand_Vehicle();
        if (hcv)
        {
            Log("Транспорт найден:"+hcv);
            car = CarScript.Cast(hcv.GetTransport());
            return car;
        }
        ref array<Object> nearest_objects = new array<Object>;
        ref array<CargoBase> proxy_cargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition ( player.GetPosition(), 10, nearest_objects, proxy_cargos);
        foreach(Object obj:nearest_objects)
        {
            if(obj.IsTransport())
            {
                car = CarScript.Cast(obj);
                return car;
            }
        }
        Log("Транспорт не найден");
        return NULL;
    }
}
/// @brief Менеджер машин реализует различные манипуляции с транспортом
class KCItemsCarManager
{
    /// @brief Какая машина будет использоваться
    ///        при манипуляциях
    CarScript target;

    void KCItemsCarManager(CarScript car)
    {
        target = car;
    }

    bool Save(PlayerBase user, KCTextCmd data)
    {
        KCItemsCarSaver saver = new KCItemsCarSaver(target);
        return saver.SaveCar(user, data);
    }

    /// @brief Починить машину
    /// @param inventory если ИСТИНА будет чинится и весь инвентарь
    void Repair(bool inventory)
    {
        KCItemsRepairTool tool = new KCItemsRepairTool(target);
        tool.Healt();
        tool.Atach();
        Charge();
        if (inventory)
        {
            tool.Child();
        }
    }


    /// @brief Заправить машину топливом
    void Refuel()
    {
        float fuelReq = target.GetFluidCapacity( CarFluid.FUEL ) - (target.GetFluidCapacity( CarFluid.FUEL ) * target.GetFluidFraction( CarFluid.FUEL ));
        float oilReq = target.GetFluidCapacity( CarFluid.OIL ) - (target.GetFluidCapacity( CarFluid.OIL ) * target.GetFluidFraction( CarFluid.OIL ));
        float coolantReq = target.GetFluidCapacity( CarFluid.COOLANT ) - (target.GetFluidCapacity( CarFluid.COOLANT ) * target.GetFluidFraction( CarFluid.COOLANT ));
        float brakeReq = target.GetFluidCapacity( CarFluid.BRAKE ) - (target.GetFluidCapacity( CarFluid.BRAKE ) * target.GetFluidFraction( CarFluid.BRAKE ));
        target.Fill( CarFluid.FUEL, fuelReq );
        target.Fill( CarFluid.OIL, oilReq );
        target.Fill( CarFluid.COOLANT, coolantReq );
        target.Fill( CarFluid.BRAKE, brakeReq );
        Charge();
    }

    /// @brief Заряжаем АКБ в транспорте
    void Charge()
    {
        ref array<EntityAI> vehParts = new array<EntityAI>;
        TStringArray SlotNames = new TStringArray;
        string cfg_path = CFG_VEHICLESPATH + " " + target.GetType() + " attachments";
        KCItems.Log("Начинаем поиск слотов по пути:"+cfg_path);
        GetGame().ConfigGetTextArray(cfg_path, SlotNames);	
        
        foreach(string slotName : SlotNames)
        {
            EntityAI part = target.FindAttachmentBySlotName(slotName);
            if (part)
            {
                ComponentEnergyManager em = part.GetCompEM();
                if (em)
                {
                    float addEnergy = em.GetEnergyMax() - em.GetEnergy();
                    em.AddEnergy(addEnergy);
                    em.Synch();
                }
            } 
        }
    }

    /// @brief Получить инструмент для приложения импульса к объекту
    /// @return инструментарий по пинанию объекта
    KCItemsImpulseTool GetImpulseTool()
    {
        return new KCItemsImpulseTool(target);
    }

    /// @brief Установить время жизни лодки на 45 дней
    void SetLongLife()
    {
        target.SetLifetimeMax(3888000);
        target.SetLifetime(3888000);
    }

}
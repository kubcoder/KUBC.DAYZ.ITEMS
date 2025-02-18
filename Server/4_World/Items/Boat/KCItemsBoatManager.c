/// @brief Менеджер машин реализует различные манипуляции с транспортом
class KCItemsBoatManager
{
    /// @brief Какая лодка будет использоваться
    ///        при манипуляциях
    BoatScript target;

    void KCItemsBoatManager(BoatScript boat)
    {
        target = boat;
    }

    /// @brief Починить лодку
    /// @param inventory если ИСТИНА будет чинится и весь инвентарь
    void Repair(bool inventory)
    {
        KCItemsRepairTool tool = new KCItemsRepairTool(target);
        tool.Healt();
        tool.Atach();
        if (inventory)
        {
            tool.Child();
        }
    }


    /// @brief Заправить лодку топливом
    void Refuel()
    {
        float fuelReq = target.GetFluidCapacity(BoatFluid.FUEL) - (target.GetFluidCapacity(BoatFluid.FUEL) * target.GetFluidFraction(BoatFluid.FUEL));
        target.Fill(BoatFluid.FUEL, fuelReq);
        target.SetSynchDirty();
        target.Synchronize();	
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
/// @brief Менеджер машин реализует различные манипуляции с транспортом
class KCItemsCarManager
{
    /// @brief Какая лодка будет использоваться
    ///        при манипуляциях
    CarScript target;

    void KCItemsCarManager(CarScript boat)
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
        float fuelReq = target.GetFluidCapacity( CarFluid.FUEL ) - (target.GetFluidCapacity( CarFluid.FUEL ) * target.GetFluidFraction( CarFluid.FUEL ));
        float oilReq = target.GetFluidCapacity( CarFluid.OIL ) - (target.GetFluidCapacity( CarFluid.OIL ) * target.GetFluidFraction( CarFluid.OIL ));
        float coolantReq = target.GetFluidCapacity( CarFluid.COOLANT ) - (target.GetFluidCapacity( CarFluid.COOLANT ) * target.GetFluidFraction( CarFluid.COOLANT ));
        float brakeReq = target.GetFluidCapacity( CarFluid.BRAKE ) - (target.GetFluidCapacity( CarFluid.BRAKE ) * target.GetFluidFraction( CarFluid.BRAKE ));
        target.Fill( CarFluid.FUEL, fuelReq );
        target.Fill( CarFluid.OIL, oilReq );
        target.Fill( CarFluid.COOLANT, coolantReq );
        target.Fill( CarFluid.BRAKE, brakeReq );
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
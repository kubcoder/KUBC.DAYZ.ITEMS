/// @brief Поисковик машины
class KCItemsCarFinder : KCItemsItemsFinder
{
    /// @brief Найти машину по близости
    /// @param position вокруг какой точки искать
    /// @param radius радиус поиска объекта
    /// @return лодка, если таковая найдена
    CarScript GetCar(vector position, float radius)
    {
        CarScript car = CarScript.Cast(GetObject(position, radius));
        return car;
    }

    override bool IsTarget(Object obj)
    {
        CarScript car = CarScript.Cast(obj);
        return car != null;
    }

    /// @brief Найти машину рядом с игроком
    /// @param player возле какого игрока шукаем тачилу
    /// @param radius в каком радиусе от игрока шукать тачилу
    /// @return Найденный транспорт, или null если транспорт найти не удалось
    CarScript GetCar(PlayerBase player, float radius)
    {
        KCItems.Log("Начинаем поиск транспорта");
        CarScript car;
        HumanCommandVehicle hcv = player.GetCommand_Vehicle();
        if (hcv)
        {
            KCItems.Log("Транспорт найден:"+hcv);
            car = CarScript.Cast(hcv.GetTransport());
            return car;
        }
        return GetCar(player.GetPosition(), radius);
    }
}
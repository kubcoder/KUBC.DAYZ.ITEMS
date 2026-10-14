/// @brief Поисковик мотоцикла
class KCItemsMotoFinder : KCItemsItemsFinder
{
    /// @brief Найти машину по близости
    /// @param position вокруг какой точки искать
    /// @param radius радиус поиска объекта
    /// @return машина, если таковая найдена
    MotorbikeScript GetMoto(vector position, float radius)
    {
        MotorbikeScript moto = MotorbikeScript.Cast(GetObject(position, radius));
        return moto;
    }

    override bool IsTarget(Object obj)
    {
        MotorbikeScript car = MotorbikeScript.Cast(obj);
        return car != null;
    }

    /// @brief Найти мотоцикл рядом с игроком
    /// @param player возле какого игрока шукаем тачилу
    /// @param radius в каком радиусе от игрока шукать тачилу
    /// @return Найденный транспорт, или null если транспорт найти не удалось
    MotorbikeScript GetMoto(PlayerBase player, float radius)
    {
        KCItems.Log("Начинаем поиск транспорта");
        MotorbikeScript moto;
        HumanCommandVehicle hcv = player.GetCommand_Vehicle();
        if (hcv)
        {
            KCItems.Log("Транспорт найден:"+hcv);
            moto = MotorbikeScript.Cast(hcv.GetTransport());
            return moto;
        }
        return GetMoto(player.GetPosition(), radius);
    }


    
}
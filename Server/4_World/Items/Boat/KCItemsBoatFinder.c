/// @brief Поиск лодок
class KCItemsBoatFinder : KCItemsItemsFinder
{
    /// @brief Найти лодку по близости
    /// @param position вокруг какой точки искать
    /// @param radius радиус поиска объекта
    /// @return лодка, если таковая найдена
    BoatScript GetBoat(vector position, float radius)
    {
        BoatScript boat = BoatScript.Cast(GetObject(position, radius));
        return boat;
    }

    override bool IsTarget(Object obj)
    {
        BoatScript boat = BoatScript.Cast(obj);
        return boat != null;
    }
}
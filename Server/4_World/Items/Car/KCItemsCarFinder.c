/// @brief Поиск лодок
class KCItemsCarFinder : KCItemsItemsFinder
{
    /// @brief Найти машину по близости
    /// @param position вокруг какой точки искать
    /// @param radius радиус поиска объекта
    /// @return лодка, если таковая найдена
    CarScript GetCar(vector position, float radius)
    {
        CarScript boat = CarScript.Cast(GetObject(position, radius));
        return boat;
    }

    override bool IsTarget(Object obj)
    {
        CarScript boat = CarScript.Cast(obj);
        return boat != null;
    }
}
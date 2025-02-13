/// @brief Класс для поиска предметов в игре
class KCItemsItemsFinder
{
    /// @brief Найти объект
    /// @param position вокруг какой точки искать
    /// @param radius радиус поиска объекта
    /// @return объект, если таковой найден
    Object GetObject(vector position, float radius)
    {
        ref array<Object> nearest_objects = new array<Object>;
        ref array<CargoBase> proxy_cargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition (position, radius, nearest_objects, proxy_cargos);
        Object found;
        float distance = 15000;
        foreach(Object obj:nearest_objects)
        {
            if(IsTarget(obj))
            {
                if (found)
                {
                    float nDist = vector.Distance(position, obj.GetPosition());
                    if (nDist<distance)
                    {
                        found = obj;
                        distance = nDist;
                    }
                }
                else
                {
                    found = obj;
                    distance = vector.Distance(position, obj.GetPosition());
                }
            }
        }
        return found;
    }

    /// @brief Проверить что объект требуемый
    /// @param obj объект в зоне поиска
    /// @return истина если объект искомый
    bool IsTarget(Object obj)
    {
        return false;
    }
}
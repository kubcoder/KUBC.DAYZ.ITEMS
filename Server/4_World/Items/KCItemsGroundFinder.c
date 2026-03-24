/// @brief Инструмент поиска игровых предметов вокруг позиции
class KCItemsGroundFinder
{
    ref KCItemsSaveSettings options;

    void KCItemsGroundFinder(string settingFileName)
    {
        KCItemsSaveSettingsLoader loader = new KCItemsSaveSettingsLoader(settingFileName);
        options = loader.Load();
    }

    KCSaveItemCollection FindItems(PlayerBase player, float radius, bool relative)
    {
        KCSaveItemCollection result = new KCSaveItemCollection();
        if (!options.IsValid())
        {
            KCItems.Log("Настройки сохранения отсутсвуют, набор для сохраненения не сформирован", KCLogLevel.Error);
            return result;
        }
        ref array<Object> nearest_objects = new array<Object>;
        ref array<CargoBase> proxy_cargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition (player.GetPosition(), radius, nearest_objects, proxy_cargos);
        foreach(Object obj:nearest_objects)
        {
            if(options.IsSaveItem(obj.GetType()))
            {
                EntityAI eA = EntityAI.Cast(obj);
                if (eA)
                {
                    KCItemBuilder builder = new KCItemBuilder(eA);
                    builder.Build();
                    if (relative)
                    {
                        builder.AddOrientation(player);
                        builder.AddPosition(player);
                    }
                    else
                    {
                        builder.AddOrientation();
                        builder.AddPosition();
                    }
                    result.Insert(builder.ItemData);
                }
            }
        }
        return result;
    }

}
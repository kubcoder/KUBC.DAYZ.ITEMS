/** @brief Команда удаления игровых предметов*/
class KCItemsCMDDel : KCUserCMD
{
    /** @brief название команды*/
    static const string CMD_NAME = "del";
    /** @brief аргумент указывающий что нужно удалить итем из рук*/
    static const string ARG_INHAND = "h";
    /** @brief Дистанция удаления по умолчанию*/
    static const float DEFAULT_RADIUS = 3;

    override string GetName()
    {
        return KCItemsCMDDel.CMD_NAME;
    }
    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        float radius = DEFAULT_RADIUS;
        if (data.Arg.Count()>0)
        {
            if (data.Arg[0]==ARG_INHAND)
            {
                EntityAI itemHands = data.Player.GetItemInHands();
                if(itemHands)
                {
                    GetGame().ObjectDelete(itemHands);
                }
                return true;
            }
            radius = data.Arg[0].ToFloat();
        }
        if (radius==0)
        {
            radius = DEFAULT_RADIUS;
        }
        ref array<Object> nearest_objects = new array<Object>;
        ref array<CargoBase> proxy_cargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition ( data.Player.GetPosition(), radius, nearest_objects, proxy_cargos);
        foreach(Object obj:nearest_objects)
        {
            Delete(obj);
        } 
        return true;
    }

    /** @brief  Удаляем объект из мира, с проверкой 
    *           доступности удаления.
    *   @param  obj - Объект который в радиусе удаления
    *   @return истина если объект можно радостно грохнуть
    */
    bool Delete(Object obj)
	{
		if (obj.IsMan())
			return !obj.IsAlive();
		if (obj.IsStaticTransmitter())
			return false;
		if (obj.IsTree())
			return false;
		if (obj.IsRock())
			return false;
		if (obj.IsWoodBase())
			return false;
		if (obj.IsBush())
			return false;
		if (obj.IsBuilding())
			return false;
		if (obj.IsFuelStation())
			return false;
        if (GetGame().ObjectIsKindOf(obj, "HouseNoDestruct"))
            return false;
		GetGame().ObjectDelete(obj);
		return true;
	}
}
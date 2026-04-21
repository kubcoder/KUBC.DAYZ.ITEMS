class KCItemFabricBase
{
    /// @brief Изменить кол-во итема
    /// @param item - число которого нужно изменить
    /// @param cCount - какое число требуется
    /// @return Сколько по факту сейчас данного итема
    int SetCount(EntityAI item, int count)
    {
        if (!item.ConfigGetBool("canBeSplit"))
        {
            return 1;
        }
        Magazine_Base mb = Magazine_Base.Cast(item);
        if (mb)
        {
            return SetCount(mb, count);
        }
        float ms = item.ConfigGetFloat("varStackMax");
        int qm = item.ConfigGetInt("varQuantityMax");
        if (ms >= 1)
            qm = ms;    
        if (qm<1)
        {
            qm=1;
        }
        ItemBase itemBs = ItemBase.Cast(item);
        if (count>qm)
        {
            count = qm;
        }
        if (itemBs)
        {
            itemBs.SetQuantity(count);
            return count;
        }
        else
        {
            return qm;
        }             
    }

    private int SetCount(Magazine_Base mb, int count)
    {
        
        int qm = mb.GetAmmoMax();
        if (qm<1)
        {
            qm=1;
        }
        if (count> qm)
        {
            count = qm;
        }
        mb.ServerSetAmmoCount(count);
        return count;
    }

    vector RotationYaw(vector pos, float yaw)
	{
		vector result = pos;
		result[0] = pos[0]*Math.Cos(yaw)+pos[2]*Math.Sin(yaw);
		result[2] = pos[2]*Math.Cos(yaw)-pos[0]*Math.Sin(yaw);
		return result;
	}

    vector GetOrientation()
    {
        return vector.Zero;
    }

    vector GetPosition()
    {
        return vector.Zero;
    }

    /// @brief Получить координаты относительно игрока
    vector GetWorldPos(vector position)
    {
        float yaw = GetOrientation()[0] * Math.DEG2RAD;
        vector pos = RotationYaw(position, yaw);
        return pos + GetPosition();
    }

    vector GetWorldOrientation(vector orientaiton)
    {
        return Rotate(orientaiton, GetOrientation()[0]);
    }

    vector Rotate(vector orientaiton, float yaw)
    {
        vector o = orientaiton;
        o[0] = o[0] + yaw;
        if(o[0] > 180)
            o[0] = o[0] - 360;
        if(o[0] < -180)
            o[0] = o[0] + 360;
        return o;
    }

}
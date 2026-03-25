/// Фабрика игровых предметов
/// используется для создания предметов
/// в игровом мире из файла данных 
class KCItemFabric
{
    private PlayerBase player;

    void KCItemFabric(PlayerBase target)
    {
        player = target;
    }

    
    EntityAI Create(KCSaveItem itemData)
    {
        if (itemData.OnGorund())
        {
            return CreateOnGorund(itemData);
        }
        if (itemData.SlotID==0)
        {
            return CreateOnHands(itemData);
        }
        return Create(player, itemData);
    }

    EntityAI CreateOnGorund(KCSaveItem itemData)
    {
        EntityAI spawnItem;
        if (itemData.IsAbsolute)
        {
            auto obj = GetGame().CreateObject( itemData.ItemName, itemData.Position);
            spawnItem = EntityAI.Cast(obj);
            if (spawnItem)
            {
                spawnItem.SetPosition(itemData.Position);
                spawnItem.SetOrientation(itemData.Orientation);
                SetQuantity(spawnItem, itemData);
                Create(spawnItem, itemData.Child);
                return spawnItem;
            }
        }
        else
        {
            auto obj1 = GetGame().CreateObject( itemData.ItemName, GetWorldPos(itemData.Position));
            spawnItem = EntityAI.Cast(obj1);
            if (spawnItem)
            {
                spawnItem.SetPosition(GetWorldPos(itemData.Position));
                spawnItem.SetOrientation(GetWorldOrientation(itemData.Orientation));
                SetQuantity(spawnItem, itemData);
                Create(spawnItem, itemData.Child);
                return spawnItem;
            }
        }
        return NULL;
    }

    EntityAI Create(EntityAI parrent, KCSaveItem itemData)
    {
        if (itemData.SlotID==-1)
        {
            return CreateOnCargo(parrent, itemData);
        }
        return Attach(parrent, itemData);
    }

    EntityAI CreateOnHands(KCSaveItem itemData)
    {
        auto spawnItem = EntityAI.Cast(player.GetHumanInventory().CreateInHands(itemData.ItemName));
        if (spawnItem)
        {
            SetQuantity(spawnItem, itemData);
            Create(spawnItem, itemData.Child);
            return spawnItem;
        }
        return NULL;
    }

    private EntityAI Attach(EntityAI parrent, KCSaveItem itemData)
    {
        Weapon_Base weapon = Weapon_Base.Cast(parrent);
        if ((weapon)&&(GetGame().IsKindOf(itemData.ItemName, "Magazine_Base")))
        {
            Magazine mb = weapon.SpawnAttachedMagazine(itemData.ItemName);
            if (mb)
            {
                int qm = mb.GetAmmoMax();
                if (qm<1)
                {
                    qm=1;
                }
                if (itemData.Quantity<qm)
                {
                    mb.ServerSetAmmoCount(itemData.Quantity);
                }
            }
            return weapon;
        }
        EntityAI aItem = parrent.GetInventory().CreateAttachmentEx(itemData.ItemName, itemData.SlotID);
        if (aItem)
        {
            if (itemData.Quantity>1)
            {
                ItemBase ibItem = ItemBase.Cast(aItem);
                if (ibItem)
                {
                    SetQuantity(ibItem, itemData);
                }
            }
            Create(aItem, itemData.Child);
            return aItem;
        }
        return NULL;
    }

    private EntityAI CreateOnCargo(EntityAI parrent, KCSaveItem itemData)
    {
        InventoryLocation il = new InventoryLocation;
	    parrent.GetInventory().GetCurrentInventoryLocation(il);
        EntityAI cItem = parrent.GetInventory().CreateEntityInCargoEx(itemData.ItemName, il.GetIdx(), itemData.Row, itemData.Col, itemData.Flip);
        if (cItem)
        {
            SetQuantity(cItem, itemData);
            Create(cItem, itemData.Child);
            return cItem;
        }
        return NULL;
    }

    void Create(EntityAI parrent, KCSaveItemCollection childs)
    {
        foreach(KCSaveItem itemData:childs)
        {
            Create(parrent, itemData);
        }
    }

    /// @brief  Устанавливаем кол-во итема
    /// @param item Какой итем требует изменения кол-ва
    /// @return Кол-во итемов после изменений
    void SetQuantity(EntityAI item, KCSaveItem itemData)
    {
        if (itemData.Quantity==0)
        {
            return;
        }
        Magazine_Base mb = Magazine_Base.Cast(item);
        if (mb)
        {
            mb.ServerSetAmmoCount(itemData.Quantity);
            return;
        }
        ItemBase itemBs = ItemBase.Cast(item);
        if (itemBs)
        {
            if (itemData.LiquidType>-1)
            {
                itemBs.SetLiquidType(itemData.LiquidType);
            }
            itemBs.SetQuantity(itemData.Quantity);
            return;
        }
    }

    /// @brief Получить координаты относительно игрока
    /// @param player относительно какого игрока добавляем поворот
    vector GetWorldPos(vector position)
    {
        float yaw = player.GetOrientation()[0] * Math.DEG2RAD;
        vector pos = RotationYaw(position, yaw);
        return pos + player.GetPosition();
    }

    vector GetWorldOrientation(vector orientaiton)
    {
        vector o = orientaiton;
        o[0] = o[0] + player.GetOrientation()[0];
        if(o[0] > 180)
            o[0] = o[0] - 360;
        if(o[0] < -180)
            o[0] = o[0] + 360;
        return o;
    }

	
	vector RotationYaw(vector pos, float yaw)
	{
		vector result = pos;
		result[0] = pos[0]*Math.Cos(yaw)+pos[2]*Math.Sin(yaw);
		result[2] = pos[2]*Math.Cos(yaw)-pos[0]*Math.Sin(yaw);
		return result;
	}
}
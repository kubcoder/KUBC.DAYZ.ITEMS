#ifndef KC_SAVE_ITEM
/// @brief Описание итема для сохранения
class KCSaveItem
{
    /// @brief Класс итема
    string ItemName;
    
    /// @brief Здоровье итема
    float Healt;
    
    /// @brief Колличество итема
    float Quantity = 0;
    
    /// @brief Столбец размещения в инвентаре
    int Col;
    
    /// @brief Строка размещения в инвентаре
    int Row;
    
    /// @brief Признак что элемент перевернут в инвентаре
    bool Flip;
    
    /// @brief положение в мире
    vector Position;
    
    /// @brief Ориентация в мире
    vector Orientation;
    
    /// @brief Признак что координаты абсолютные
    bool IsAbsolute = false;
    
    /// @brief Дочерние элементы
    ref KCSaveItemCollection Child;
    
    /// @brief Слот в котором размещен итем
    int SlotID;
    
    /// @brief Тип жидкости, если доступно
    int LiquidType = -1;


    /// @brief Создать итем перед игроком, в направлении взгляда
    /// @param player игрок возле которого будет создан предмет
    /// @param Distance на какой дистанции создавать
    /// @return Игровой итем если получилось создать, иначе NULL
    EntityAI CreateOnRoute(PlayerBase player, float Distance)
    {
        EntityAI spawnItem;
        vector pos = player.GetPosition() + player.GetDirection()*Distance;
        auto obj1 = GetGame().CreateObject(ItemName, pos);
        spawnItem = EntityAI.Cast(obj1);
        if (spawnItem)
        {
            spawnItem.SetOrientation(GetWorldOrientation(player));
            spawnItem.PlaceOnSurface();
            SetQuantity(spawnItem);
            CreateChilds(spawnItem);
            return spawnItem;
        }
        return spawnItem;
    }

    /// @brief Создать итем
    /// @param parrent  родительский итем в который нужно разместить создаваемый
    ///                 или null если итем создается в мире. так же может быть игрок
    /// @return Игровой итем если получилось создать, иначе NULL
    EntityAI Create(EntityAI parrent)
    {
        EntityAI spawnItem;
        PlayerBase player;
        if ((Position)&&(Position!=vector.Zero))
        {
            if (IsAbsolute)
            {
                auto obj = GetGame().CreateObject( ItemName, Position);
                spawnItem = EntityAI.Cast(obj);
                if (spawnItem)
                {
                    spawnItem.SetPosition(Position);
                    spawnItem.SetOrientation(Orientation);
                    SetQuantity(spawnItem);
                    CreateChilds(spawnItem);
                    return spawnItem;
                }
            }
            else
            {
                player = PlayerBase.Cast(parrent);
                if (player)
                {
                    auto obj1 = GetGame().CreateObject( ItemName, GetWorldPos(player));
                    spawnItem = EntityAI.Cast(obj1);
                    if (spawnItem)
                    {
                        spawnItem.SetPosition(GetWorldPos(player));
                        spawnItem.SetOrientation(GetWorldOrientation(player));
                        SetQuantity(spawnItem);
                        CreateChilds(spawnItem);
                        return spawnItem;
                    }
                }
            }
        }
        else
        {
            player = PlayerBase.Cast(parrent);
            if (player)
            {
                spawnItem = EntityAI.Cast(player.GetHumanInventory().CreateInHands(ItemName));
                if (spawnItem)
                {
                    if(Child)
                    {
                        SetQuantity(spawnItem);
                        CreateChilds(spawnItem);
                    }
                    return spawnItem;
                }
            }
            else
            {
                if (SlotID!=-1)
                {
                    Weapon_Base weapon = Weapon_Base.Cast(parrent);
                    if ((weapon)&&(GetGame().IsKindOf(ItemName, "Magazine_Base")))
                    {
                        Magazine mb = weapon.SpawnAttachedMagazine(ItemName);
                        if (mb)
                        {
                            int qm = mb.GetAmmoMax();
                            if (qm<1)
                            {
                                qm=1;
                            }
                            if (Quantity<qm)
                            {
                                mb.ServerSetAmmoCount(Quantity);
                            }
                        }
                        return weapon;
                    }
                    else
                    {
                        EntityAI aItem = parrent.GetInventory().CreateAttachmentEx(ItemName, SlotID);
                        if (aItem)
                        {
                            if (Quantity>1)
                            {
                                ItemBase ibItem = ItemBase.Cast(aItem);
                                if (ibItem)
                                {
                                    SetQuantity(ibItem);
                                }
                            }
                            if (Child)
                            {
                                CreateChilds(aItem);
                            } 
                            return aItem;
                        }
                           
                    }
                }
                else
                {
                    InventoryLocation il = new InventoryLocation;
			        parrent.GetInventory().GetCurrentInventoryLocation( il );
                    EntityAI cItem = parrent.GetInventory().CreateEntityInCargoEx(ItemName, il.GetIdx(), Row, Col, Flip);
                    if (cItem)
                    {
                        SetQuantity(cItem);
                        if (Child)
                        {
                            CreateChilds(cItem);
                        }
                        return cItem;
                    }
                }
            }
        }
        return NULL;
    }

    /// @brief  Создаем дочерние итемы
    /// @param parrent итем в который запихиваем дочерние итемы
    void CreateChilds(EntityAI parrent)
    {
        if (Child)
        {
            foreach(KCSaveItem cChild : Child)
            {
                cChild.Create(parrent);
            }
        }
        
    }

    /// @brief  Устанавливаем кол-во итема
    /// @param item Какой итем требует изменения кол-ва
    /// @return Кол-во итемов после изменений
    int SetQuantity(EntityAI item)
    {
        if (Quantity==0)
        {
            return 0;
        }
        Magazine_Base mb = Magazine_Base.Cast(item);
        if (mb)
        {
            mb.ServerSetAmmoCount(Quantity);
            return Quantity;
        }
        ItemBase itemBs = ItemBase.Cast(item);
        if (itemBs)
        {
            if (LiquidType>-1)
            {
                itemBs.SetLiquidType(LiquidType);
            }
            itemBs.SetQuantity(Quantity);
            return Quantity;
        }
        return 0;
    }

    /// @brief получить итем для сохранения из машины
    /// @param car транспорт существующий в игровом мире
    /// @return Данные для сохранения на жестком диске
    static KCSaveItem FromCar(CarScript car)
    {
        KCSaveItem iData = new KCSaveItem();
        iData.ItemName = car.GetType();
        iData.Healt = car.GetHealth();
        GameInventory inventory = car.GetInventory();
        if (inventory)
        {
            iData.Child = new KCSaveItemCollection();
            array<EntityAI> itemsArray = new array<EntityAI>;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			for (int j = 0; j < itemsArray.Count(); j++)
			{
                EntityAI parent = itemsArray.Get(j).GetHierarchyParent();
                if ((itemsArray.Get(j)!=car)&&(parent == car))
                {
                    KCSaveItem childItem = KCSaveItem.FromItem(itemsArray.Get(j));
                    InventoryLocation il = new InventoryLocation;
			        itemsArray.Get(j).GetInventory().GetCurrentInventoryLocation( il );
                    childItem.Row = il.GetRow();
                    childItem.Col = il.GetCol();
                    childItem.Flip = il.GetFlip();
                    childItem.SlotID = il.GetSlot();
                    iData.Child.Insert(childItem);
                }
			}
        }
        return iData;
    }


    /// @brief Получаем описание итема для сохранения
    /// @param из какого итема создать описание
    /// @return Данные для сохранения
    static KCSaveItem FromItem(EntityAI item)
    {
        KCSaveItem iData = new KCSaveItem();
        iData.ItemName = item.GetType();
        iData.Healt = item.GetHealth();
        Magazine_Base mb = Magazine_Base.Cast(item);
        if (mb)
        {
            iData.Quantity = mb.GetAmmoCount();
        }
        else
        {
            iData.Quantity = item.GetQuantity();
        }
        ItemBase ib = ItemBase.Cast(item);
        if ((ib)&&(ib.IsLiquidContainer()))
        {
            iData.LiquidType = ib.GetLiquidType();
        }
        GameInventory inventory = item.GetInventory();
        if (inventory)
        {
            iData.Child = new KCSaveItemCollection();
            array<EntityAI> itemsArray = new array<EntityAI>;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			for (int j = 0; j < itemsArray.Count(); j++)
			{
                EntityAI parent = itemsArray.Get(j).GetHierarchyParent();
                if ((itemsArray.Get(j)!=item)&&(parent == item))
                {
                    KCSaveItem childItem = KCSaveItem.FromItem(itemsArray.Get(j));
                    InventoryLocation il = new InventoryLocation;
			        itemsArray.Get(j).GetInventory().GetCurrentInventoryLocation( il );
                    childItem.Row = il.GetRow();
                    childItem.Col = il.GetCol();
                    childItem.Flip = il.GetFlip();
                    childItem.SlotID = il.GetSlot();
                    iData.Child.Insert(childItem);
                }
			}
        }
        return iData;
    }

    /// @brief Добавить относительные координаты
    /// @param item итем координаты которого сохраняем
    /// @param player относительно какого игрока создаем относительную координату
    void AddPosition(EntityAI item, PlayerBase player)
    {
        float yaw = (0 - player.GetOrientation()[0]) * Math.DEG2RAD;
        Position = item.GetPosition() - player.GetPosition();
        Position = RotationYaw(Position, yaw);
    }

    /// @brief Добавить относительный разворот
    /// @param item итем разворот которого сохраняем
    /// @param player относительно какого игрока добавляем поворот
    void AddOrientation(EntityAI item, PlayerBase player)
    {
        Orientation = item.GetOrientation();
        Orientation[0] = Orientation[0]-player.GetOrientation()[0];
    }

    /// @brief Получить координаты относительно игрока
    /// @param player относительно какого игрока добавляем поворот
    vector GetWorldPos(PlayerBase player)
    {
        float yaw = player.GetOrientation()[0] * Math.DEG2RAD;
        vector pos = RotationYaw(Position, yaw);
        return pos + player.GetPosition();
    }
    vector GetWorldOrientation(PlayerBase player)
    {
        vector o = Orientation;
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

    /// @brief Создать итем на игроке
    /// @param player - на каком игроке создавать
    /// @param SetHealt - Востанавливать здоровье итема из файла
    /// @return Созданный предмет
    EntityAI CreateOnPlayer(PlayerBase player, bool SetHealt = false)
    {
        HumanInventory hInv = player.GetHumanInventory();
        EntityAI cItem;
        EntityAI oItem;
        if (SlotID!=-1)
        {
            if (InventorySlots.GetSlotName(SlotID) == "Hands")
            {
                oItem = hInv.GetEntityInHands();
                if (oItem)
                {
                    GetGame().ObjectDelete(oItem);
                }
                cItem = hInv.CreateInHands(ItemName);
            }
            else
            {
                oItem = hInv.FindAttachment(SlotID);
                if (oItem)
                {
                    GetGame().ObjectDelete(oItem);
                }
                cItem = hInv.CreateAttachmentEx(ItemName, SlotID);
            }
        }
        else
        {
            cItem = hInv.CreateInInventory(ItemName);
        }
        if (cItem)
        {
            SetQuantity(cItem);
            if (SetHealt)  
            {
                cItem.SetHealth(Healt);
            }
            if (Child)
            {
                CreateChilds(cItem);
            }      
        }
        return cItem;
    }
}

/// Коллекция сохраненных итемов
typedef array<ref KCSaveItem>	KCSaveItemCollection;
#define KC_SAVE_ITEM
#endif
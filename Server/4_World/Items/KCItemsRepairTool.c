/// @brief Базовый класс выполняющий ремонт
///        игрового предмета
class KCItemsRepairTool
{
    EntityAI tEntity;

    /// @brief Инициализируем починятор
    /// @param entity объект который будем чинить
    void KCItemsRepairTool(EntityAI entity)
    {
        tEntity = entity;
    }

    /// @brief Чиним предмет, включая все зоны повреждений
    void Healt()
    {
        if (!tEntity)
        {
            return;
        }
        ref array<string> damageZones;
        string cfgPath = CFG_VEHICLESPATH + " " + tEntity.GetType() + " DamageSystem";
        KCItems.Log("Начинаем поиск точек поломки по пути:"+cfgPath);
        if ( GetGame().ConfigIsExisting(cfgPath) )
        {
            KCItems.Log("Конфиг найден");
            damageZones = new array<string>;
            int dmgZoneCount = GetGame().ConfigGetChildrenCount(cfgPath);
            KCItems.Log("Найдено зон повреждения:" + dmgZoneCount);
            if ( dmgZoneCount > 0 )
            {
                for (int i = 0; i < dmgZoneCount; ++i)
                {
                    string parentClass;
                    GetGame().ConfigGetChildName(cfgPath, i, parentClass);
                    parentClass.ToLower();
                    if ( parentClass == "damagezones" )
                    {
                        int dmgZoneIndex = GetGame().ConfigGetChildrenCount(cfgPath + " DamageZones");
                        for (int j = 0; j < dmgZoneIndex; ++j)
                        {
                            string childZone;
                            GetGame().ConfigGetChildName(cfgPath + " DamageZones", j, childZone);
                            damageZones.Insert( childZone );
                        }
                    }
                }
            }
        }
        else
        {
            KCItems.Log("Конфиг не найден, прерываем",KCLogLevel.Error);
            return;
        }

        KCItems.Log("Здоровья у предмета:"+tEntity.GetHealth());
        if ( damageZones && damageZones.Count() > 0 )
        {
            foreach(string dmgZone: damageZones)
            {
                KCItems.Log("Обрабатываем зону:"+dmgZone);
                KCItems.Log("Здоровье " + dmgZone + ":" + tEntity.GetHealth(dmgZone,""));
                KCItems.Log("Максимум " + dmgZone + ":" + tEntity.GetMaxHealth(dmgZone, ""));
                tEntity.SetHealth(dmgZone, "", tEntity.GetMaxHealth(dmgZone, ""));
            }
        }
        KCItems.Log("Добавляем здоровья до уровня:"+tEntity.GetMaxHealth());
        tEntity.SetHealth("", "", tEntity.GetMaxHealth());
        tEntity.SetSynchDirty();
    }

    /// @brief Чиним все приатаченные итемы
    void Atach()
    {
        ref array<EntityAI> vehParts = new array<EntityAI>;
        TStringArray SlotNames = new TStringArray;
        string cfg_path = CFG_VEHICLESPATH + " " + tEntity.GetType() + " attachments";
        KCItems.Log("Начинаем поиск слотов по пути:"+cfg_path);
        GetGame().ConfigGetTextArray(cfg_path, SlotNames);	
        
        foreach(string slotName : SlotNames)
        {
            EntityAI part = tEntity.FindAttachmentBySlotName(slotName);
            if (part)
            {
                KCItems.Log("Нашли ["+part+"] в слоте: "+ slotName);
                vehParts.Insert(part);
            }
            else
            {
                KCItems.Log("Не нашли ни чего в слоте:"+slotName);
            }
            
        }
        foreach(EntityAI att : vehParts)
        {
            if (att != NULL)
            {
                KCItems.Log("Проверяем часть "+ att);
                string partType = att.GetType();
                partType.ToLower();
                if ( partType.Contains("_ruined") )
                {
                    partType.Replace("_ruined", "");
                    KCItems.Log("Часть уже уничтожена, заменяем на " + partType);
                    GetGame().ObjectDelete( att );
                    tEntity.GetInventory().CreateAttachment(partType);
                }
                else
                {
                    KCItems.Log("Часть чинимая, здоровья: " + att.GetHealth());
                    KCItemsRepairTool repairTool = new KCItemsRepairTool(att);
                    repairTool.Healt();
                    KCItems.Log("Вкатили ремонт: " +  att.GetHealth());
                }
            }
        }
    }

    /// @brief Починить все дочерние предметы
    void Child()
    {
        array<EntityAI> itemsArray = new array<EntityAI>;
        GameInventory inventory = tEntity.GetInventory();
        if (inventory)
        {
            inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
            foreach(EntityAI child: itemsArray)
            {
                if (child!=tEntity)
                {
                    KCItemsRepairTool repairTool = new KCItemsRepairTool(child);
                    repairTool.Healt();
                    repairTool.Child();
                }
                    
            }
        }
    }
}
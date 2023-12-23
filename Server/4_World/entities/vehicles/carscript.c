modded class CarScript
{
    void Repair()
    {
        ref array<string> damageZones;
        string cfgPath = CFG_VEHICLESPATH + " " + GetType() + " DamageSystem";
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
        KCItems.Log("Здоровья у тачилы:"+GetHealth());
        if ( damageZones && damageZones.Count() > 0 )
        {
            foreach(string dmgZone: damageZones)
            {
                KCItems.Log("Обрабатываем зону:"+dmgZone);
                KCItems.Log("Здоровье " + dmgZone + ":" + GetHealth(dmgZone,""));
                KCItems.Log("Максимум " + dmgZone + ":" + GetMaxHealth(dmgZone, ""));
                SetHealth(dmgZone, "", GetMaxHealth(dmgZone, ""));
            }
        }
        KCItems.Log("Добавляем здоровья машине до уровня:"+GetMaxHealth());
        SetHealth("", "", GetMaxHealth());
        SetSynchDirty();
        KCItems.Log("Здоровья у тачилы:"+GetHealth());

        ref array<EntityAI> vehParts = new array<EntityAI>;
        TStringArray SlotNames = new TStringArray;
        string cfg_path = CFG_VEHICLESPATH + " " + GetType() + " attachments";
        KCItems.Log("Начинаем поиск слотов по пути:"+cfg_path);
        GetGame().ConfigGetTextArray(cfg_path, SlotNames);	
        
        foreach(string carSlot : SlotNames)
        {
            EntityAI part = FindAttachmentBySlotName(carSlot);
            if (part)
            {
                KCItems.Log("Нашли ["+part+"] в слоте: "+ carSlot);
                vehParts.Insert(part);
            }
            else
            {
                KCItems.Log("Не нашли ни чего в слоте:"+carSlot);
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
                    GetInventory().CreateAttachment(partType);
                }
                else
                {
                    KCItems.Log("Часть чинимая, здоровья: " + att.GetHealth());
                    KCItems.RepairItem(att);
                    KCItems.Log("Вкатили ремонт: " +  att.GetHealth());
                }
            }
        }
        SetLifetimeMax(3888000);
        SetLifetime(3888000);
        CleanupEffects();
        m_EngineDestroyed = false;
        SetFullHealth();
        Synchronize();
        SetSynchDirty();
        
    }
}
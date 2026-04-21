/// @brief Базовый класс выполняющий ремонт
///        игрового предмета
class KCItemsRepairTool
{
    /// @brief Игровой предмент для починки
    EntityAI tEntity;

    /// @brief Инициализируем починятор
    /// @param entity объект который будем чинить
    void KCItemsRepairTool(EntityAI entity)
    {
        tEntity = entity;
    }

    void All()
    {
        Healt();
        Atach();
        Child();
    }

    /// @brief Чиним предмет, включая все зоны повреждений
    void Healt()
    {
        if (!tEntity)
        {
            return;
        }
        tEntity.SetFullHealth();
        tEntity.SetSynchDirty();
    }

    /// @brief Чиним все приатаченные итемы
    void Atach()
    {
        if (!tEntity)
        {
            return;
        }
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
        if (!tEntity)
        {
            return;
        }
        array<EntityAI> itemsArray = new array<EntityAI>;
        GameInventory inventory = tEntity.GetInventory();
        if (inventory)
        {
            inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
            KCItems.Log("Обнаружили в инвентаре обеъктов " + itemsArray.Count());
            foreach(EntityAI child: itemsArray)
            {
                if (child!=tEntity)
                {
                    KCItems.Log("Починяем объект" + child);
                    KCItemsRepairTool repairTool = new KCItemsRepairTool(child);
                    repairTool.Healt();
                    repairTool.Child();
                }
            }
        }
        else
        {
            KCItems.Log("Не нашли инвентраь для " + tEntity);
        }
    }
}
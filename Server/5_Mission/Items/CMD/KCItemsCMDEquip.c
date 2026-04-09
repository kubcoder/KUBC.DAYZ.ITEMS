/// @brief Команда работы с экипировкой
class KCItemsCMDEquip : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "equip";
    
    /// @brief аргумент сохранения экипировки
    const string ARG_SAVE = "save";
        
    /// @brief аргумент сброса всех итемов игрока на землю
    const string ARG_DROP = "drop";
    
    /// @brief аргумент удаления всей экипировки игрока
    const string ARG_CLEAR = "clear";
    
    /// @brief аргумент выдачи экипировки рядом с игроком
    const string AGR_GROUND = "g";
    
    

    override string GetName()
    {
        return KCItemsCMDEquip.CMD_NAME;
    }

    private ref KCItemsEquipDirectory directory;

    void KCItemsCMDEquip(KCItemsEquipDirectory setsDirectory)
    {
        directory = setsDirectory;
    }

    override bool Execute(KCTextCmd data)
    {
        auto equipManager = KCItemsEquipManager(data.GetTarget());
        if (data.ContainsArg(ARG_DROP))
        {
            equipManager.DropAll();
            data.Message("Сбросили всю экипировку под ноги");
            return true;
        }
        if (data.ContainsArg(ARG_CLEAR))
        {
            equipManager.DeleteAll();
            data.Message("Удалили всю экипировку");
            return true;
        }
        if (data.ContainsArg(ARG_SAVE))
        {
            return Save(data);
        }
        if (data.Arg.Count()==0)
        {
            data.MessageOwner("Не указано имя выдаваемого набора");
            return true;
        }
        string setFileName = directory.FindDataFile(data.Arg[0], data.Owner);
        if (setFileName=="")
        {
            data.MessageOwner("Экипировка ["+data.Arg[0]+"] не существует");
            return true;
        }
        KCItemSet itemSet = directory.LoadFile(setFileName);
        if (itemSet==NULL)
        {
            data.MessageOwner("Ошибка загрузки экипировки ["+data.Arg[0]+"]");
            return true;
        }
        if (equipManager.Equip(itemSet))
        {
            data.Message("Экипировка ["+data.Arg[0]+"] выдана");
        }
        else
        {
            data.MessageOwner("Возникли проблемы при выдаче экпипировки ["+data.Arg[0]+"], не все смогли выдать");
        }
        return true;
    }

    bool Save(KCTextCmd data)
    {
         auto saveManager = new KCItemSaveManager(directory, data);
        saveManager.InitName(1);
        if (saveManager.GetName() == "")
        {
            data.MessageOwner("Вы не указали имя экипировки, сохранение не выполнено");
            return true;
        }
        if (!saveManager.CanBeSave())
        {
            data.MessageOwner("Экипировка уже существует, сохранение не выполнено!");
            return true;
        }
        GameInventory inventory = data.GetTarget().GetInventory();
        if (inventory==NULL)
        {
            data.MessageOwner("Не смогли получить доступ к инвенторю игрока!");
            return true;
        }
        array<EntityAI> itemsArray = new array<EntityAI>;
		inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
        foreach(EntityAI child: itemsArray)
        {
            EntityAI parent = child.GetHierarchyParent();
            if (parent == data.GetTarget())
            {
                auto builder = new KCItemBuilder(child);
                builder.Build();
                if (builder.ItemData)
                {
                    InventoryLocation il = new InventoryLocation;
                    child.GetInventory().GetCurrentInventoryLocation(il);
                    builder.ItemData.Row = il.GetRow();
                    builder.ItemData.Col = il.GetCol();
                    builder.ItemData.Flip = il.GetFlip();
                    builder.ItemData.SlotID = il.GetSlot();
                    saveManager.Add(builder.ItemData);
                }
                else
                {
                    Log("Не смогли создать описание итема:" + child);
                }
            }
        }
        saveManager.Save();
        return true;
    }
}
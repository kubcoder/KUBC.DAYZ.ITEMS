/// @brief Команда сохранения набора итемов
class KCItemsCMDSave : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "save";
    
    
    /// @brief аргумент записи набора вокруг игрока
    const string ARG_GROUND = "g";
    
    /// @brief аргумент записи набора вокруг игрока с сохренением абсолютных координат
    const string ARG_ABSGROUND = "a";
    
    /// @brief Растояние поиска предметов по умолчанию
    const float DEF_DISTANCE = 3.0;

    private ref KCItemsSetsDirectory directory;

    void KCItemsCMDSave(KCItemsSetsDirectory setsDirectory)
    {
        directory = setsDirectory;
    }

    override string GetName()
    {
        return KCItemsCMDSave.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        auto manager = new KCItemSaveManager(directory, data);
        manager.InitName(0);
        if (manager.GetName() == "")
        {
            data.MessageOwner("Вы не указали имя набора, сохранение не выполнено");
            return true;
        }
        if (!manager.CanBeSave())
        {
            data.MessageOwner("Набор уже существует, сохранение не выполнено!");
            return true;
        }
        
        AddItems(data, manager);
        if (!manager.Save())
        {
            data.MessageOwner("Отсутсвуют предметы для сохранения, сохранение не выполнено!");
            return true;
        }
        
        data.MessageOwner("Набор " + manager.GetName() + " сохранен!");
        return true;
    }

    private void AddItems(KCTextCmd data, KCItemSaveManager manager)
    {
        if (!IsOnGround(data))
        {
            KCSaveItem itemData = GetHands(data.Owner);
            if (itemData)
            {
                manager.Add(itemData);
            }
        }
        else
        {
            KCItemsGroundFinder finder = new KCItemsGroundFinder(directory.GetItemSetOptionsFile());
            manager.Add(finder.FindItems(data.Owner, GetRadius(data), !data.ContainsArg(ARG_ABSGROUND)));
        }
    }

    private float GetRadius(KCTextCmd data)
    {
        float result = data.GetFloat(ARG_GROUND, -1);
        if (result > -1)
        {
            return result;
        }
        result = data.GetFloat(ARG_ABSGROUND, -1);
        if (result > -1)
        {
            return result;
        }
        return DEF_DISTANCE;
    } 

    private KCSaveItem GetHands(PlayerBase player)
    {
        ItemBase itemHands = player.GetItemInHands();
        if (itemHands)
        {
            KCItemBuilder builder = new KCItemBuilder(itemHands);
            builder.Build();
            builder.ItemData.SlotID = 0;
            return builder.ItemData;
        }
        KCPlayer.SendMessage(player,"", "В руках не найден предмет для сохранеения");
        return NULL;
    }

    private bool  IsOnGround(KCTextCmd data)
    {
        if (data.ContainsArg(ARG_GROUND))
        {
            return true;
        }
        if (data.ContainsArg(ARG_ABSGROUND))
        {
            return true;
        }
        return false;
    }

}
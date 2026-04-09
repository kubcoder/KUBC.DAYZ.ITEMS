class KCItemsCMDBox : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "box";

    const string DEFAULT_BOX = "WoodenCrate";

    override string GetName()
    {
        return KCItemsCMDBox.CMD_NAME;
    }

    override bool Execute(KCTextCmd data)
    {
        if (data.Arg.Count()==0)
        {
            data.MessageOwner("Не указано название предмета для создания");
            return true;
        }
        string itemName = data.Arg[0];
        auto target = data.GetTarget();
        auto itemFabric = new KCItemFabric(target);
        if (!itemFabric.CanBeSpawn(itemName))
        {
            data.MessageOwner("Пердемет ["+itemName+"] не может быть создан");
            return true;
        }
        string boxName = DEFAULT_BOX;
        if (data.Arg.Count()>1)
        {
            boxName = data.Arg[1];
        }
        if (!itemFabric.CanBeSpawn(boxName))
        {
            data.MessageOwner("Пердемет ["+boxName+"] не может быть создан");
            return true;
        }
        auto box = itemFabric.CreateInHands(boxName);
        if (box==NULL)
        {
            data.MessageOwner("Не смогли создать ящик ["+boxName+"] в руках игрока");
            return true;
        }
        EntityAI item = itemFabric.Create(box, itemName);
        int count = 0;
        while(item!=null)
        {
            count++;
            item = itemFabric.Create(box, itemName);
        }
        if (count==0)
        {
            data.MessageOwner("Ящик ["+boxName+"] создан, однако не смогли добавить в него ["+itemName+"]");
            return true;
        }
        data.Message("Выдали ящик ["+boxName+"] в который положили ["+itemName+"] - "+ count.ToString()+" шт.");
        return true;
    }
}

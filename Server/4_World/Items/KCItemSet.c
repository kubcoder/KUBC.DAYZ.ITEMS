/** @brief описание набора итемов созданного игроком*/
class KCItemSet
{
    /** @brief никнейм игрока который аффтор данного набора*/
    string NickName;
    /** @brief SteamID игрока который это создал*/
    string SteamID;
    /** @brief  Примечания к набору. В игре не используются
    *           испольузются в веб-модуле управления
    */
    string Notes;
    /** @brief Итемы включенные в набор*/
    ref KCSaveItemCollection Items = new KCSaveItemCollection();

    /** @brief Выдаем экипировку. Если экипировка полная то весь имеющийся лут удаляется.
    *   @param player - кому выдать
    *   @param SetHealth - устанавливать здоровье итемов
    */
    void CreateEquip(PlayerBase player, bool SetHealt = false)
    {
        if(Items.Count()>0)
        {
            KCItems.Log("Удаляем всю экипировку игрока");
            DeleteAll(player);
            foreach(KCSaveItem eItem:Items)
            {
                KCItems.Log("Выдаем итем: " + eItem.ItemName);
                EntityAI ei = eItem.CreateOnPlayer(player, SetHealt);
                if (!ei)
                {
                    KCItems.Log("Не смогли выдать итем:" + eItem.ItemName, KCLogLevel.Error);
                }
            }
        }
        else
        {
            KCItems.Log("Список итемов пустой", KCLogLevel.Error);   
        }
    }   

    /** @brief Удалить все игровые предметы у игрока
    *   @param player игрок которого нужно раздеть
    */
    static void DeleteAll(PlayerBase player)
    {
        GameInventory inventory = player.GetInventory();
		if (inventory)
		{
			array<EntityAI> itemsArray = new array<EntityAI>;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			foreach(EntityAI item:itemsArray)
            {
                EntityAI parent = item.GetHierarchyParent();
                if (parent == player)
                {
                    GetGame().ObjectDelete(item);
                    player.SetSynchDirty();
                }
            }
		}
    }
    /** @brief Сбросить на землю все игровые предметы у игрока
    *   @param player игрок которого нужно раздеть
    */
    static void DropAll(PlayerBase player)
    {
        GameInventory inventory = player.GetInventory();
		if (inventory)
		{
			array<EntityAI> itemsArray = new array<EntityAI>;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
            foreach(EntityAI item:itemsArray)
            {
                EntityAI parent = item.GetHierarchyParent();
                if (parent == player)
                {
                    inventory.DropEntity(InventoryMode.SERVER, parent, item);
                    player.SetSynchDirty();
                }
            }
		}
    }
}
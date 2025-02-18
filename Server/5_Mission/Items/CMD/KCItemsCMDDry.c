/// @brief Команда ускоренной сушки игрока
class KCItemsCMDDry : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "dry";

    override string GetName()
    {
        return KCItemsCMDDry.CMD_NAME;
    }
    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        GameInventory inventory = data.Player.GetInventory();
		if (inventory)
		{
			array<EntityAI> itemsArray = new array<EntityAI>;
			ItemBase item;
			inventory.EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			foreach(EntityAI child: itemsArray)
            {
                child.SetWet(0);
                child.SetWeightDirty();
            }
		}
        KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Вашу одежду подсушили");
        return true;
    }
}
/// @brief Команда ускоренной сушки игрока
class KCItemsCMDDry : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "dry";

    override string GetName()
    {
        return KCItemsCMDDry.CMD_NAME;
    }
    override bool Execute(KCTextCmd data)
    {
        
        GameInventory inventory = data.GetTarget().GetInventory();
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
        data.Message("Одежду подсушили");
        return true;
    }
}
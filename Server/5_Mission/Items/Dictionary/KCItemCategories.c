/// @brief Справочник категорий
class KCItemCategories : array<ref KCItemCategory>
{
    /// @brief Заполнить массив значениями по умолчанию
    void Default()
    {
        Insert(GetWeapon());
        Insert(GetZombies());
        Insert(GetAnimals());
        Insert(GetEdible());
        Insert(GetClothing());
        Insert(GetTransport());
    }

    /// @brief Получить категорию оружия
    private KCItemCategory GetWeapon()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Оружие";
        c.BaseClass = "weapon_base";
        c.Priority = 0;
        return c;
    }
    
    /// @brief Получить категорию зомбиков
    private KCItemCategory GetZombies()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Зомби";
        c.BaseClass = "ZombieBase";
        c.Priority = 1;
        return c;
    }
    
    /// @brief Получить категорию животных
    private KCItemCategory GetAnimals()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Животные";
        c.BaseClass = "dz_lightai";
        c.Priority = 2;
        return c;
    }
    
    /// @brief Получить категорию еды
    private KCItemCategory GetEdible()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Еда";
        c.BaseClass = "edible_base";
        c.Priority = 3;
        return c;
    }
    
    /// @brief Получить категорию одежды
    private KCItemCategory GetClothing()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Одежда";
        c.BaseClass = "clothing_base";
        c.Priority = 4;
        return c;
    }
    
    /// @brief Получить категорию транспорта
    private KCItemCategory GetTransport()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Транспорт";
        c.BaseClass = "transport";
        c.Priority = 5;
        return c;
    }
}
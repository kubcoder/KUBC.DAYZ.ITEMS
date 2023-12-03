/** @brief Категория игровых итемов*/
class KCItemCategory
{
    /** @brief отображаемое имя категории*/
    string ShowName;
    /** @brief Имя базового класса от которого наследуются итемы данной категории*/
    string BaseClass;
    /** @brief приоритет обработк*/
    int Priority;
    
    /** @brief Имя файла настроек категорий*/
    static const string FILE_NAME = "categories.json";
    
    /** @briefПолное имя файла настроек категорий*/
    static string GetFileName()
    {
        return KCItems.GetDictonaryPath() + "\\" + FILE_NAME;
    }
    /** @brief Загрузить файл категорий*/
    static KCItemCategories GetCategories()
    {
        string fName = GetFileName();
        if (FileExist(fName))
        {
            KCItemCategories result;
            JsonFileLoader<KCItemCategories>.JsonLoadFile( fName, result);
            if(result)
                return result;
            KCItems.Log("Не смогли загрузить файл " + fName + ", хотя он существует. Возможно в нем ошибки.", KCLogLevel.Error);
            return new KCItemCategories();
        }
        else
        {
            return GetDefault();
        }
    }
    /** @brief Получить категории по умолчанию*/
    static KCItemCategories GetDefault()
    {
        KCItems.Log("Создаем категории справочника по умолчанию");
        KCItemCategories cats = new KCItemCategories();
        cats.Insert(GetWeapon());
        cats.Insert(GetZombies());
        cats.Insert(GetAnimals());
        cats.Insert(GetEdible());
        cats.Insert(GetClothing());
        cats.Insert(GetTransport());
        JsonFileLoader<KCItemCategories>.JsonSaveFile(GetFileName(), cats);
        return cats;
    }
    /** @brief Получить категорию оружия*/
    static KCItemCategory GetWeapon()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Оружие";
        c.BaseClass = "weapon_base";
        c.Priority = 0;
        return c;
    }
    /** @brief Получить категорию зомбиков*/
    static KCItemCategory GetZombies()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Зомби";
        c.BaseClass = "ZombieBase";
        c.Priority = 1;
        return c;
    }
    /** @brief Получить категорию животных*/
    static KCItemCategory GetAnimals()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Животные";
        c.BaseClass = "dz_lightai";
        c.Priority = 2;
        return c;
    }
    /** @brief Получить категорию еды*/
    static KCItemCategory GetEdible()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Еда";
        c.BaseClass = "edible_base";
        c.Priority = 3;
        return c;
    }
    /** @brief Получить категорию одежды*/
    static KCItemCategory GetClothing()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Одежда";
        c.BaseClass = "clothing_base";
        c.Priority = 4;
        return c;
    }
    /** @brief Получить категорию транспорта*/
    static KCItemCategory GetTransport()
    {
        KCItemCategory c = new KCItemCategory();
        c.ShowName = "Транспорт";
        c.BaseClass = "transport";
        c.Priority = 5;
        return c;
    }
}
/** @brief Массив категорий*/
typedef array<ref KCItemCategory>	KCItemCategories;
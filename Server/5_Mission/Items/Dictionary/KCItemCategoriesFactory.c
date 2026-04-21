/// @brief Инструменты для работы с настройками категорий справочника
class KCItemCategoriesFactory
{
    private string fileName;

    void  KCItemCategoriesFactory(string file)
    {
        fileName = file;
        CreateDefault();
    }

    /// @brief Если файла настроек нет, то данный метод 
    ///        создает файл настроек по умолчанию
    private void CreateDefault()
    {
        if(FileExist(fileName))
        {
            return ;
        }
        KCItems.Log("Файл настройки категорий справочника не существует, создаем со значениями по умолчанию");
        KCItemCategories  categories = new KCItemCategories();
        categories.Default();
        JsonFileLoader<KCItemCategories>.JsonSaveFile(fileName, categories);
    }

    /// @brief Загрузить настройки категорий 
    /// @return массив настроек, или NULL если не смогли загрузить файл
    KCItemCategories Load()
    {
        KCItems.Log("Загружаем Файл настройки категорий справочника");
        KCItemCategories result;
        JsonFileLoader<KCItemCategories>.JsonLoadFile( fileName, result);
        if(result)
            return result;
        KCItems.Log("Не смогли загрузить файл " + fileName + ", хотя он существует. Возможно в нем ошибки.", KCLogLevel.Error);
        return NULL;
    }

}
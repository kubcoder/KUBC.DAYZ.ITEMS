/// @brief Описание итема в справочнике
class KCItemDesc
{
    /// @brief Категория итема
    string Category;
    
    /// @brief Описание итема на языке котором запущен сервер
    string Description;
    
    
}

/// @brief Справочник итемов
typedef map<string, ref KCItemDesc>	KCItemDictionary;
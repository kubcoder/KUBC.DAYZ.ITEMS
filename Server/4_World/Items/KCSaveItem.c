#ifndef KC_SAVE_ITEM
/// @brief Описание итема для сохранения
class KCSaveItem
{
    /// @brief Класс итема
    string ItemName;
    
    /// @brief Здоровье итема
    float Healt;
    
    /// @brief Колличество итема
    float Quantity = 0;
    
    /// @brief Столбец размещения в инвентаре
    int Col;
    
    /// @brief Строка размещения в инвентаре
    int Row;
    
    /// @brief Признак что элемент перевернут в инвентаре
    bool Flip;
    
    /// @brief положение в мире
    vector Position;
    
    /// @brief Ориентация в мире
    vector Orientation;
    
    /// @brief Признак что координаты абсолютные
    bool IsAbsolute = false;
    
    /// @brief Дочерние элементы
    ref KCSaveItemCollection Child;
    
    /// @brief Слот в котором размещен итем
    int SlotID;
    
    /// @brief Тип жидкости, если доступно
    int LiquidType = -1;

    bool OnGorund()
    {
        return (Position!=vector.Zero);
    }
}
/// Коллекция сохраненных итемов
typedef array<ref KCSaveItem>	KCSaveItemCollection;
#define KC_SAVE_ITEM
#endif
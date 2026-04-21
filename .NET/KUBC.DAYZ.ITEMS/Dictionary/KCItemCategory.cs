using System;
using System.Collections.Generic;
using System.Text;

namespace KUBC.DAYZ.ITEMS.Dictionary;

/// <summary>
/// Категория игровых предметов
/// </summary>
public class KCItemCategory
{
    /// <summary>
    /// Отображаемое имя
    /// </summary>
    public string ShowName { get; set; } = string.Empty;

    /// <summary>
    /// Базовый класс игрового предмета
    /// </summary>
    public string BaseClass { get; set; } = string.Empty;

    /// <summary>
    /// Приоритет в формировании справочника
    /// </summary>
    public int Priority { get; set; } = 0;
}

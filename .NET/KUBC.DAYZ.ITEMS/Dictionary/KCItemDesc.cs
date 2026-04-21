using System;
using System.Collections.Generic;
using System.Text;

namespace KUBC.DAYZ.ITEMS.Dictionary;

/// <summary>
/// Описание игрового предмета
/// </summary>
public class KCItemDesc
{
    /// <summary>
    /// Категория игрового предмета
    /// </summary>
    public string Category {  get; set; } = string.Empty;

    /// <summary>
    /// Описание игрового предмета в локализации на которой запущен сервер
    /// </summary>
    public string Description {  get; set; } = string.Empty;
}

using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Text;
using RM = KUBC.DAYZ.ITEMS.Resources.Dictionary.ClearTool; 
namespace KUBC.DAYZ.ITEMS.Dictionary;

/// <summary>
/// Инструмент очистки словаря игровых предметов
/// </summary>
/// <param name="logger">Журнал приложения</param>
public class ClearTool(ILogger logger)
{
    /// <summary>
    /// Очищать строчки с пустым описанием
    /// </summary>
    public bool ClearEmptyDescription = true;

    /// <summary>
    /// Очистить строчки содержащие Proxy предметов
    /// </summary>
    public bool ClearProxy = true;

    /// <summary>
    /// Удалять не работающие предметы
    /// Фильтр ориентируется на название $UINT$
    /// </summary>
    public bool ClearNotFuncional = true;

    /// <summary>
    /// Удалить сущности игроков
    /// </summary>
    public bool ClearSurvivors = true;

    /// <summary>
    /// Очистить словарь в соответсвии с настройками
    /// </summary>
    /// <param name="dictionary">Словарь для очистки</param>
    public void Clear(KCDictionary dictionary)
    {
        logger.LogInformation(RM.StartClear, dictionary.Count);
        int removeCount = 0;
        foreach (var row in dictionary)
        {
            if (MustBeRemove(row.Key, row.Value))
            {
                dictionary.Remove(row.Key);
                removeCount++;
            }
        }
        logger.LogInformation(RM.EndClear, removeCount);

    }

    private bool MustBeRemove(string key, KCItemDesc value)
    {
        if (RemoveByEmptyDescription(key,value))
            return true;
        if (RemoveProxy(key))
            return true;
        if (RemoveNotFuncional(key, value))
            return true;
        return RemoveSurvivor(key);
    }

    private bool RemoveByEmptyDescription(string key, KCItemDesc value)
    {
        if (!ClearEmptyDescription)
            return false;
        if (string.IsNullOrWhiteSpace(value.Description))
        {
            logger.LogInformation(RM.RemoveByEmptyDescription, key);
            return true;
        }
        return false;
    }

    private bool RemoveProxy(string key)
    {
        if (!ClearProxy)
            return false;
        if (key.StartsWith("Proxy"))
        {
            logger.LogInformation(RM.RemoveProxy, key);
            return true;
        }
        return false;
    }

    private bool RemoveNotFuncional(string key, KCItemDesc value)
    {
        if (!ClearProxy)
            return false;
        if (value.Description.StartsWith("$UNT$"))
        {
            logger.LogInformation(RM.RemoveNotFuncional, key);
            return true;
        }
        return false;
    }

    private bool RemoveSurvivor(string key)
    {
        if (!ClearProxy)
            return false;
        if (key.StartsWith("Survivor"))
        {
            logger.LogInformation(RM.RemoveSurvivor, key);
            return true;
        }
        return false;
    }
}

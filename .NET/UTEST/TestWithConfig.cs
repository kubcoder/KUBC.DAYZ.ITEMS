using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Text;

namespace KUBC.DAYZ.ITEMS;

/// <summary>
/// Класс теста с загрузкой конфигурации
/// </summary>
public abstract class TestWithConfig
{
    /// <summary>
    /// Имя файла конфигурации для проекта
    /// </summary>
    public const string ConfigFileName = "config.json";

    /// <summary>
    /// Конфигурация теста
    /// </summary>
    public readonly IConfiguration Configuration;

    /// <summary>
    /// Инициализация конфигурации теста
    /// </summary>
    public TestWithConfig()
    {
        Configuration = LoadConfig();
    }

    private IConfiguration LoadConfig()
    {
        var configBuilder = new ConfigurationBuilder();
        Assert.True(File.Exists(ConfigFileName));
        configBuilder.AddJsonFile(ConfigFileName);
        var testConfigFiles = GetConfigFiles();
        foreach (var configFile in testConfigFiles)
        {
            configBuilder.AddJsonFile(configFile);
        }
        return configBuilder.Build();
    }

    /// <summary>
    /// Получить имена файлов конфигурации для тестов
    /// </summary>
    /// <returns>Список имен файлов конфигурации которые нужно загрузить</returns>
    protected virtual string[] GetConfigFiles() => [];
}

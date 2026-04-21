using KUBC.DAYZ.ITEMS.Dictionary;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Unicode;

namespace KUBC.DAYZ.ITEMS;

public class TDictionary : TestWithServices
{
    public override DirectoryInfo SampleDirectory => new DirectoryInfo(Path.Combine(base.SampleDirectory.FullName, "Dictionary"));

    private FileManager sampleFileManager => new(SampleDirectory);

    private FileManager outputFileManager
    {
        get
        {
            var directory = new DirectoryInfo("Results");
            if (!directory.Exists)
            {
                directory.Create();
            }
            return new(directory);
        }
    }


    /// <summary>
    /// Тестируем загрузку данных из файла категорий
    /// </summary>
    /// <returns></returns>
    [Fact]
    public async Task LoadCategories()
    {
        var categories = await sampleFileManager.LoadCategoriesAsync(TestContext.Current.CancellationToken);
        Assert.NotNull(categories);
        Assert.NotEmpty(categories);
        await outputFileManager.Save(categories, jsonOptions, TestContext.Current.CancellationToken);
        
    }

    /// <summary>
    /// Тестируем загрузку данных из файла категорий
    /// </summary>
    /// <returns></returns>
    [Fact]
    public async Task LoadDictionary()
    {
        var dictionary = await sampleFileManager.LoadDictionaryAsync(TestContext.Current.CancellationToken);
        Assert.NotNull(dictionary);
        Assert.NotEmpty(dictionary);
        await outputFileManager.Save(dictionary, jsonOptions, TestContext.Current.CancellationToken);
    }

    [Fact]
    public async Task Clear()
    {
        var dictionary = await sampleFileManager.LoadDictionaryAsync(TestContext.Current.CancellationToken);
        Assert.NotNull(dictionary);
        Assert.NotEmpty(dictionary);
        var cleaner = new ClearTool(ServiceProvider.GetRequiredService<ILogger<ClearTool>>())
        {
            ClearEmptyDescription = true
        };
        cleaner.Clear(dictionary);
        await outputFileManager.Save(dictionary, jsonOptions, TestContext.Current.CancellationToken);
    }

    private JsonSerializerOptions jsonOptions => new JsonSerializerOptions()
    {
        Encoder = JavaScriptEncoder.Create(UnicodeRanges.BasicLatin, UnicodeRanges.Cyrillic),
        WriteIndented = true
    };
}

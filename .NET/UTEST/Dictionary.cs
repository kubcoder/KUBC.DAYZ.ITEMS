using KUBC.DAYZ.ITEMS.Dictionary;
using System;
using System.Collections.Generic;
using System.Text;

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
        await outputFileManager.Save(categories, new System.Text.Json.JsonSerializerOptions() { WriteIndented = true }, TestContext.Current.CancellationToken);
        
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
        await outputFileManager.Save(dictionary, new System.Text.Json.JsonSerializerOptions() { WriteIndented = true }, TestContext.Current.CancellationToken);
    }

}

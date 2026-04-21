using System;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;

namespace KUBC.DAYZ.ITEMS.Dictionary;

/// <summary>
/// Менеджер файлов словаря 
/// игровых предметов
/// </summary>
/// <param name="dictionaryPath">Директория размещения словаря</param>
public class FileManager(DirectoryInfo dictionaryPath)
{
    /// <summary>
    /// Имя файла категорий
    /// </summary>
    public const string CategoryFileName = "categories.json";

    /// <summary>
    /// Имя файла справочника
    /// </summary>
    public const string DictionaryFileName = "items.json";

    /// <summary>
    /// Файл категорий
    /// </summary>
    public FileInfo CategoriesFile => GetFile(CategoryFileName);

    /// <summary>
    /// Файл справочника
    /// </summary>
    public FileInfo DictionaryFile => GetFile(DictionaryFileName);

    /// <summary>
    /// Загрузить справочник игровых предметов
    /// </summary>
    /// <returns>Справочник игровых предметов</returns>
    public async Task<KCDictionary?> LoadDictionaryAsync(CancellationToken cancelationToken = default)
    {
        using FileStream fileStream = DictionaryFile.OpenRead();
        return await JsonSerializer.DeserializeAsync<KCDictionary>(fileStream, cancellationToken:cancelationToken);
    }

    /// <summary>
    /// Сохранить файл справочника
    /// </summary>
    /// <param name="dictionary">Данные справочника</param>
    /// <param name="cancelationToken">Токен отмены асинхронной операции</param>
    /// <param name="options">Опции сохранения файла</param>
    /// <returns></returns>
    public async Task Save(KCDictionary dictionary, JsonSerializerOptions? options = default, CancellationToken cancelationToken = default)
    {
        using FileStream fileStream = DictionaryFile.Create();
        await JsonSerializer.SerializeAsync(fileStream, dictionary, options, cancelationToken );
        await fileStream.FlushAsync(cancelationToken);
    }

    /// <summary>
    /// Загрузить справочник категорий
    /// </summary>
    /// <returns>Справочник игровых предметов</returns>
    public async Task<KCItemCategories?> LoadCategoriesAsync(CancellationToken cancelationToken = default)
    {
        using FileStream fileStream = CategoriesFile.OpenRead();
        return await JsonSerializer.DeserializeAsync<KCItemCategories>(fileStream, cancellationToken: cancelationToken);
    }

    /// <summary>
    /// Сохранить файл категорий
    /// </summary>
    /// <param name="categories">Данные справочника</param>
    /// <param name="cancelationToken">Токен отмены асинхронной операции</param>
    /// <param name="options">Опции сохранения файла</param>
    /// <returns></returns>
    public async Task Save(KCItemCategories categories, JsonSerializerOptions? options = default, CancellationToken cancelationToken = default)
    {
        using FileStream fileStream = CategoriesFile.Create();
        await JsonSerializer.SerializeAsync(fileStream, categories, options, cancelationToken);
        await fileStream.FlushAsync(cancelationToken);
    }

    private FileInfo GetFile(string fileName)
    {
        return new FileInfo(Path.Combine(dictionaryPath.FullName, fileName));
    }


}

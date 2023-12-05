using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Unicode;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS.Dictonary
{
    /// <summary>
    /// Список категорий
    /// </summary>
    public class Categories:List<ItemCategory>
    {
        /// <summary>
        /// Имя файла категорий
        /// </summary>
        public const string FILENAME = "categories.json";

        /// <summary>
        /// Сохранить данные справочника в файл
        /// </summary>
        /// <param name="file">В какой файл сохранять</param>
        /// <returns>null если сохранение прошло успешно, иначе исключение которое возникло при сохранения</returns>
        public Exception? Save(FileInfo file)
        {
            try
            {
                var o = new JsonSerializerOptions() 
                { 
                    WriteIndented = true,
                    Encoder = JavaScriptEncoder.Create(UnicodeRanges.BasicLatin, UnicodeRanges.Cyrillic)
                };
                using (var stream = file.CreateText())
                {
                    JsonSerializer.Serialize<List<ItemCategory>>(stream.BaseStream, this, o);
                    stream.Close();
                }
                return null;
            }
            catch (Exception ex) { return ex; }
        }

        /// <summary>
        /// Загрузить справочник категорий из файла
        /// </summary>
        /// <param name="file">Файл из которого нужно грузить</param>
        /// <returns>Список категорий если файл загружен успешно</returns>
        public static Categories? Load(FileInfo file)
        {
            try
            {
                if (!file.Exists)
                    return null;
                Categories? res;
                using (var reader = file.OpenText())
                {
                    res = JsonSerializer.Deserialize<Categories>(reader.BaseStream);
                    reader.Close();
                }
                return res;
            }
            catch { return null; }
        }
    }
}

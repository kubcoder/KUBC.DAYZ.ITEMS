using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS.Dictionary
{
    /// <summary>
    /// Список известных итемов
    /// </summary>
    public class ItemsCollection:Dictionary<string, ItemDescription>
    {
        /// <summary>
        /// Имя файла категорий
        /// </summary>
        public const string FILENAME = "items.json";

        /// <summary>
        /// Загрузить справочник категорий из файла
        /// </summary>
        /// <param name="file">Файл из которого нужно грузить</param>
        /// <returns>Список категорий если файл загружен успешно</returns>
        public static ItemsCollection? Load(FileInfo file)
        {
            try
            {
                if (!file.Exists)
                    return null;
                ItemsCollection? res;
                using (var reader = file.OpenText())
                {
                    res = JsonSerializer.Deserialize<ItemsCollection>(reader.BaseStream);
                    reader.Close();
                }
                return res;
            }
            catch { return null; }
        }
        /// <summary>
        /// Рассчитать сколько итемов в каждой категории
        /// </summary>
        /// <returns>Словарь категорий с указанием кол-ва игровых итемов</returns>
        public Dictionary<string, int> CalculateCategories()
        {
            var r = new Dictionary<string, int>();
            foreach(var i in this)
            {
                if (r.TryGetValue(i.Value.Category, out int value))
                    r[i.Value.Category] = ++value;
                else
                {
                    r.Add(i.Value.Category, 1);
                }
            }
            return r;
        }

    }
}

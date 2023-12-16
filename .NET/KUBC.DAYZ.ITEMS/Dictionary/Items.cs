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
    public class Items:List<ItemDescription>
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
        public static Items? Load(FileInfo file)
        {
            try
            {
                if (!file.Exists)
                    return null;
                Items? res;
                using (var reader = file.OpenText())
                {
                    res = JsonSerializer.Deserialize<Items>(reader.BaseStream);
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
                if (r.ContainsKey(i.Category))
                    r[i.Category]++;
                else
                {
                    r.Add(i.Category, 1);
                }
            }
            return r;
        }

    }
}

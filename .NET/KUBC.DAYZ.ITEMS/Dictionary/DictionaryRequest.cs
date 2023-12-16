using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS.Dictionary
{
    /// <summary>
    /// Данные запроса списка итемов
    /// </summary>
    /// <remarks>
    /// Данный класс используется для выборки 
    /// списка итемов по различным условиям.
    /// </remarks>
    public class DictionaryRequest
    {
        /// <summary>
        /// Первая строчка для ответа
        /// </summary>
        public int Start { get; set; } = 0;
        /// <summary>
        /// Сколько итемов показывать
        /// </summary>
        public int Count { get; set; } = 20;
        /// <summary>
        /// Строчка для поиска итема
        /// </summary>
        /// <remarks>
        /// Если поле пустое или null то будут отбираться 
        /// все итемы. Если тут что то указано то в ответ 
        /// будут включаться только итемы которые содержат данный текст
        /// </remarks>
        public string? Find { get; set; }
        /// <summary>
        /// Какие категории отображать
        /// </summary>
        /// <remarks>
        /// Если данный список пустой, то в ответ 
        /// будут включены все подходящие итемы вне зависимости
        /// какая у них категория
        /// </remarks>
        public string[] Cats { get; set; } = [];



        /// <summary>
        /// Получить ответ на данный запрос
        /// </summary>
        /// <param name="path">Описание папочки в которой будем искать нужные файлики</param>
        /// <returns>Данные ответа, или null если в целевой папочке не нашли нифига</returns>
        public DictionaryResponse? GetResponse(DirectoryInfo path)
        {
            var categories = Categories.Load(new FileInfo($"{path.FullName}\\{Categories.FILENAME}"));
            if (categories == null) return null;
            var items = ItemsCollection.Load(new FileInfo($"{path.FullName}\\{ItemsCollection.FILENAME}"));
            if (items == null) return null;
            DictionaryResponse response = new();
            int i = 0;
            while(i< items.Count ) 
            {
                var ci = items.ElementAt(i);
                if (InSearchCondition(ci.Key, ci.Value))
                    i++;
                else
                    items.Remove(ci.Key);

            }
            response.SummaryCount = items.Count;
            response.Categories = items.CalculateCategories();
            foreach(var c in categories)
            {
                if (!response.Categories.ContainsKey(c.ShowName))
                {
                    response.Categories.Add(c.ShowName, 0);
                }
            }
            var ri = items.OrderBy(x => x.Key).Skip(Start).Take(Count);
            foreach(var zy in ri)
            {
                response.Items.Add(zy.Key, zy.Value);
            }
            return response;
        }
        /// <summary>
        /// Определить входит ли итем в условия поиска
        /// </summary>
        /// <param name="itemName">Имя итема</param>
        /// <param name="itemDesc">Описание итема</param>
        /// <returns></returns>
        private bool InSearchCondition(string itemName, ItemDescription itemDesc)
        {
            if (Cats.Length > 0)
            {
                if (!Cats.Contains(itemDesc.Category))
                    return false;
            }
            if (!string.IsNullOrEmpty(Find))
            {
                if (itemName.Contains(Find, StringComparison.OrdinalIgnoreCase))
                    return true;
                if (itemDesc.Description.Contains(Find, StringComparison.OrdinalIgnoreCase))
                    return true;
                return false;
            }
            return true;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS.Dictionary
{
    /// <summary>
    /// Ответ на запрос <see cref="DictionaryRequest"/> с информацией о игровых итемах
    /// </summary>
    public class DictionaryResponse
    {
        /// <summary>
        /// Сумарное кол-во итемов
        /// </summary>
        public int SummaryCount { get; set; } = 0;
        /// <summary>
        /// С какого итема выдали
        /// </summary>
        public int StartItem { get; set; } = 0;
        /// <summary>
        /// Категории итемов с указанием кол-ва
        /// </summary>
        public Dictionary<string, int> Categories { get; set; } = [];
        /// <summary>
        /// Итемы которые отвечают запросу
        /// </summary>
        public ItemsCollection Items {  get; set; } = [];
    }
}

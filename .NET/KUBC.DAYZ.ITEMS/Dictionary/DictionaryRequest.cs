using System;
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

    }
}

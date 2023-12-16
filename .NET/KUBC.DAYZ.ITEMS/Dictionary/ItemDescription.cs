using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS.Dictionary
{
    /// <summary>
    /// Элемент описания итема
    /// </summary>
    public class ItemDescription
    {
        /// <summary>
        /// Категория итема
        /// </summary>
        public string Category { get; set; } = string.Empty;

        /// <summary>
        /// Отображаемое в игре имя итема
        /// </summary>
        public string Description { get; set; } = string.Empty;
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS.Dictonary
{
    /// <summary>
    /// Категория итемов справочника
    /// </summary>
    public class ItemCategory
    {
        /// <summary>
        /// Отображаемое имя категории
        /// </summary>
        /// <remarks>
        /// Это поле нужно для того что бы пользователь понимал что это такое.
        /// </remarks>
        public string ShowName {  get; set; } = string.Empty;
        /// <summary>
        /// Базовый класс игровых итемов
        /// </summary>
        /// <remarks>
        /// При обработке игровых итемов, в данную категорию будут включены
        /// все итемы которые наследуются от данного класса.
        /// </remarks>
        public string BaseClass { get; set; } = string.Empty;
        /// <summary>
        /// Приоритет обработки данной категории.
        /// </summary>
        /// <remarks>
        /// Приоритет при обработке. Т.е. сначала
        /// обрабатываются категории с наименьшим Priority. Да я понимаю что это звучит не логично, 
        /// да я понимаю что я лажанулся с названием поля, но это было давно и менять лениво.
        /// </remarks>
        public int Priority { get; set; } = 0;

    }
}

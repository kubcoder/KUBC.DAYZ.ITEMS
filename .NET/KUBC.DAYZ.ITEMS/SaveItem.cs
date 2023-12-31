using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS
{
    /// <summary>
    /// Описание сохраненного игрового предмета
    /// </summary>
    public class SaveItem
    {
        /// <summary>
        /// Класс игрового предмета
        /// </summary>
        public string ItemName { get; set; } = string.Empty;
        /// <summary>
        /// Здоровье итема
        /// </summary>
        public float Healt { get; set; } = 0;
        /// <summary>
        /// Колличество
        /// </summary>
        public float Quantity { get; set; } = 0;
        /// <summary>
        /// Столбец размещения в инвентаре
        /// </summary>
        public int Col { get; set; } = 0;
        /// <summary>
        /// Строка размещения в инвентаре
        /// </summary>
        public int Row { get; set; } = 0;
        /// <summary>
        /// Признак перевернутости итема
        /// </summary>
        public int Flip { get; set; } = 0;
        /// <summary>
        /// Игровой предмет перевернут в инвентаре
        /// </summary>
        [JsonIgnore]
        public bool IsFlip
        {
            get
            {
                return Flip > 0;
            }
            set
            {
                if (value)
                { 
                    Flip = 1;
                }
                else
                {
                    Flip = 0;
                }
            }
        }
        /// <summary>
        /// Положение в мире
        /// </summary>
        public DAYZ.GAME.Vector Position { get; set; } = new();
        /// <summary>
        /// Ориентация в мире
        /// </summary>
        public GAME.Vector Orientation {  get; set; } = new();  
        /// <summary>
        /// Признак что указаные координаты абсолютные в мире
        /// </summary>
        public int IsAbsolute { get; set; } = 0;
        /// <summary>
        /// Вложенные итемы
        /// </summary>
        public SaveItemCollection Child { get; set; } = new();
        /// <summary>
        /// Слот в котором размещен предмет
        /// </summary>
        public int SlotID { get; set; } = 0;
        /// <summary>
        /// Жидкость которая налита в предмет (если доступно)
        /// </summary>
        public int LiquidType { get; set; } = -1;

    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS.Dictionary
{
    /// <summary>
    /// Словарь итемов
    /// </summary>
    public class Dictionary 
    {
        /// <summary>
        /// Папка разработчика модов
        /// </summary>
        public const string DEVPATH = "KUBC";
        /// <summary>
        /// Папка данных мода
        /// </summary>
        public const string MODPATH = "ITEMS";
        /// <summary>
        /// Папка словаря игровых итемов
        /// </summary>
        public const string DICTPATH = "Dictionary";
        /// <summary>
        /// Загружаем справочник
        /// </summary>
        /// <param name="profiles">К папке профилей сервера</param>
        public Dictionary(DirectoryInfo profiles)
        {
            var fullPath = $"{profiles.FullName}\\{DEVPATH}\\{MODPATH}\\{DICTPATH}";
            categoriesFile = new($"{fullPath}\\{Categories.FILENAME}");
            categories = Categories.Load(categoriesFile);
            items = ItemsCollection.Load(new FileInfo($"{fullPath}\\{ItemsCollection.FILENAME}"));
        }

        /// <summary>
        /// Файл категорий
        /// </summary>
        private FileInfo categoriesFile;
        /// <summary>
        /// Категории справочника
        /// </summary>
        private Categories? categories;
        /// <summary>
        /// Категории справочника
        /// </summary>
        public Categories Categories
        {
            get
            {
                if (categories == null)
                {
                    categories = new Categories();
                }
                return categories;
            }
        }
        /// <summary>
        /// Сохранить список категорий
        /// </summary>
        /// <returns>Исключение если была ошибка при записи, при успешной записи возвращается null</returns>
        public Exception? SaveCategories()
        {
            return Categories.Save(categoriesFile);
        }

        
        /// <summary>
        /// Список игровых итемов
        /// </summary>
        private ItemsCollection? items;
        /// <summary>
        /// Список игровых итемов
        /// </summary>
        public ItemsCollection Items
        {
            get
            {
                if (items == null)
                    items = new();
                return items;
            }
        }
        

    }
}

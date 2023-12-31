using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS
{
    /// <summary>
    /// Список файлов сохраненных итемов
    /// </summary>
    public class ItemSetList
    {
        /// <summary>
        /// Список наборов по игрокам
        /// </summary>
        public Dictionary<long, IEnumerable<FileInfo>> Players = [];
        /// <summary>
        /// Список общих наборов
        /// </summary>
        public IEnumerable<FileInfo> Shared = [];
        /// <summary>
        /// Создание пустого справочника сохраненных наборов
        /// </summary>
        public ItemSetList() { }

        /// <summary>
        /// Инициализация с поиском сохранненых файлов.
        /// </summary>
        /// <param name="path">Папка поиска, например сохраненых наборов <see cref="Paths.GetSets(DirectoryInfo)"/></param>
        public ItemSetList(DirectoryInfo path)
        {
            if(path.Exists)
            {
                var directories = path.GetDirectories();
                if (directories!=null)
                {
                    foreach(var playerDirectory in directories) 
                    {
                        AddPlayerPath(playerDirectory);
                    }
                }
                var files = path.GetFiles("*.json");
                if (files!=null)
                    Shared = files;
            }
        }
        /// <summary>
        /// Добавить папочку игрока
        /// </summary>
        /// <param name="playerDirectory"></param>
        private void AddPlayerPath(DirectoryInfo playerDirectory)
        {
            if (long.TryParse(playerDirectory.Name, out var playerID))
            {
                var files = playerDirectory.GetFiles("*.json");
                if (files!=null)
                {
                    Players.Add(playerID, files);
                }
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS
{
    /// <summary>
    /// Константы с именами папочек
    /// </summary>
    public class Paths
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
        /// Папка с наборами игровых итемов
        /// </summary>
        public const string SetsPATH = "Sets";
        /// <summary>
        /// Папка с наборами сохраненых машин
        /// </summary>
        public const string CarsPATH = "Cars";
        /// <summary>
        /// Папка с наборами экипировок
        /// </summary>
        public const string EquipPATH = "Equip";

        /// <summary>
        /// Получить папочку мода в папке профилей
        /// </summary>
        /// <param name="profiles">Папка профилей</param>
        /// <returns>Папка мода</returns>
        public static DirectoryInfo GetModPath(DirectoryInfo profiles)
        {
            return new DirectoryInfo($"{profiles.FullName}\\{DEVPATH}\\{MODPATH}");
        }

        /// <summary>
        /// Получить папочку с сохранеными наборами
        /// </summary>
        /// <param name="profiles">Папка профилей сервера</param>
        /// <returns>Папка с сохранеными наборами</returns>
        public static DirectoryInfo GetSets(DirectoryInfo profiles)
        {
            return new DirectoryInfo($"{GetModPath(profiles)}\\{SetsPATH}");
        }

        /// <summary>
        /// Получить папочку с сохранеными машинами
        /// </summary>
        /// <param name="profiles">Папка профилей сервера</param>
        /// <returns>Папка с сохранеными машинами</returns>
        public static DirectoryInfo GetCars(DirectoryInfo profiles)
        {
            return new DirectoryInfo($"{GetModPath(profiles)}\\{CarsPATH}");
        }

        /// <summary>
        /// Получить папочку с сохранеными экипировками
        /// </summary>
        /// <param name="profiles">Папка профилей сервера</param>
        /// <returns>Папка с сохранеными экипировками</returns>
        public static DirectoryInfo GetEquips(DirectoryInfo profiles)
        {
            return new DirectoryInfo($"{GetModPath(profiles)}\\{EquipPATH}");
        }
    }
}

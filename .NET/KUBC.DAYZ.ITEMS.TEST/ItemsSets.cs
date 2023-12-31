﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS.TEST
{
    /// <summary>
    /// Класс тестирования различных сохраненок итемов
    /// </summary>
    [TestClass]
    public class ItemsSets
    {
        /// <summary>
        /// Тестируем настройки сохранения наборов
        /// </summary>
        [TestMethod]
        public void SaveSettings()
        {
            var path = new DirectoryInfo("Profiles");
            var settings = KUBC.DAYZ.ITEMS.ItemsSaveSettings.FromJson(path);
            var tFile = new FileInfo("ItemsSetOptionsTest.json");
            var ex = settings.Save(tFile);
            using(var fReader = tFile.OpenText()) 
            {
                Console.WriteLine(fReader.ReadToEnd());
                fReader.Close();
            }
        }
        /// <summary>
        /// Тестируем загрузку сохранение итемов
        /// </summary>
        [TestMethod]
        public void ItemSet()
        {
            var testFile = new FileInfo("Profiles\\KUBC\\ITEMS\\Sets\\76561198054180540\\bronik.json");
            var set = ITEMS.ItemSet.FromJson(testFile);
            set.Save();
        }

        /// <summary>
        /// Тестируем поиск и загрузку наборов
        /// </summary>
        [TestMethod]
        public void FindFiles()
        {
            var path = new DirectoryInfo("Profiles");
            var sets = ITEMS.Paths.GetSets(path);
            var setsFiles = new ItemSetList(sets);
        }
    }
}

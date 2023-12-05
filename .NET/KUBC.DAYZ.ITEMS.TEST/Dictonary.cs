using KUBC.DAYZ.ITEMS.Dictonary;
namespace KUBC.DAYZ.ITEMS.TEST
{
    [TestClass]
    public class Dictonary
    {
        [TestMethod]
        public void LoadItemsCategory()
        {
            var tFile = new FileInfo($"Profiles\\KUBC\\ITEMS\\Dictonary\\{Categories.FILENAME}");
            var categories = Categories.Load(tFile);
            Assert.IsNotNull(categories, "Не смогли прочитать данные из файла");
            foreach( var category in categories ) 
            {
                Console.WriteLine($"{category.Priority}:{category.ShowName}[{category.BaseClass}]");
            }
            var oFile = new FileInfo($"TestFiles\\wcat.json");
            var ex = categories.Save(oFile);
            if (ex != null )
            {
                Assert.Fail(ex.Message);
            }
        }
        [TestMethod]
        public void LoadItems()
        {
            var tFile = new FileInfo($"Profiles\\KUBC\\ITEMS\\Dictonary\\{Items.FILENAME}");
            var items = Items.Load(tFile);
            Assert.IsNotNull(items, "Не смогли прочитать данные из файла");
            Console.WriteLine($"Загрузили справочник из {items.Count} игровых итемов");
        }
        /// <summary>
        /// Получить справочник
        /// </summary>
        /// <returns></returns>
        private static ITEMS.Dictonary.Dictonary GetDictonary()
        {
            return new ITEMS.Dictonary.Dictonary(new DirectoryInfo("Profiles"));
        }

        [TestMethod]
        public void CatStat()
        {
            var d = GetDictonary();
            var countByCategories = d.Items.CalculateCategories();
            foreach(var counter in countByCategories)
            {
                Console.WriteLine($"{counter.Key}:{counter.Value}");
            }

        }
    }
}
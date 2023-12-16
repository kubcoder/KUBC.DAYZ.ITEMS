using KUBC.DAYZ.ITEMS.Dictionary;
using System.IO;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Unicode;
namespace KUBC.DAYZ.ITEMS.TEST
{
    [TestClass]
    public class Dictionary
    {
        /// <summary>
        /// Проверяем что файл тупо загружается.
        /// </summary>
        [TestMethod]
        public void LoadDictionary()
        {
            var fi = new FileInfo("Profiles\\KUBC\\ITEMS\\Dictionary\\items.json");
            var dict = ItemsCollection.Load(fi);
            Assert.IsNotNull(dict);
        }
        /// <summary>
        /// Тестируем работу запроса
        /// </summary>
        [TestMethod]
        public void TestRequest()
        {
            var req = new DictionaryRequest() { Cats = ["Животные", "Еда"], Find="mUs" };
            var resp = req.GetResponse(new DirectoryInfo("Profiles\\KUBC\\ITEMS\\Dictionary"));
            Assert.IsNotNull(resp);
            var o = new JsonSerializerOptions()
            {
                WriteIndented = true,
                Encoder = JavaScriptEncoder.Create(UnicodeRanges.BasicLatin, UnicodeRanges.Cyrillic)
            };
            Console.WriteLine(JsonSerializer.Serialize<DictionaryResponse>(resp, o));
        }
    }
}
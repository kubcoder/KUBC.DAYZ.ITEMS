using KUBC.DAYZ.ITEMS.Dictionary;
namespace KUBC.DAYZ.ITEMS.TEST
{
    [TestClass]
    public class Dictionary
    {
        /// <summary>
        /// ��������� ��� ���� ���� �����������.
        /// </summary>
        [TestMethod]
        public void LoadDictionary()
        {
            var fi = new FileInfo("Profiles\\KUBC\\ITEMS\\Dictionary\\items.json");
            var dict = ItemsCollection.Load(fi);
            Assert.IsNotNull(dict);
        }
    }
}
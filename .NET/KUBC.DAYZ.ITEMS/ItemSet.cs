using KUBC.DAYZ.ITEMS.Resources;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Unicode;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS
{
    /// <summary>
    /// Сохраненный набор итемов
    /// </summary>
    public class ItemSet
    {
        /// <summary>
        /// никнейм игрока который аффтор данного набора
        /// </summary>
        public string NickName { get; set; } = string.Empty;
        /// <summary>
        /// SteamID игрока который это создал
        /// </summary>
        public string SteamID { get; set; } = string.Empty;
        /// <summary>
        /// Примечания к набору итемов
        /// </summary>
        public string Notes { get; set; } = string.Empty;
        /// <summary>
        /// Коллекция итемов набора
        /// </summary>
        public SaveItemCollection Items { get; set; } = new();
        /// <summary>
        /// Файл из которого была загрузка
        /// </summary>
        private FileInfo? file;

        /// <summary>
        /// Загрузить настройки из JSON файла
        /// </summary>
        /// <param name="File">Файл из которого грузим</param>
        /// <remarks>
        /// Может вызывать различные исключения, связанные как с отсутвием файлов
        /// так и с кривостью файла. в нутри метода не экранируем, что бы во внешнем приложении
        /// можно было ловить краш и понять что именно пошло не так.
        /// </remarks>
        /// <returns>Данные файла</returns>
        public static ItemSet FromJson(FileInfo File)
        {

            using (var reader = File.OpenText())
            {
                var res = JsonSerializer.Deserialize<ItemSet>(reader.BaseStream);
                reader.Close();
                if (res != null)
                {
                    res.file = File;
                    return res;
                }
                else
                {
                    throw new Exception(Resources.ItemSet.NullFile);
                }
            }
        }

        /// <summary>
        /// Сохранить настройки в файл
        /// </summary>
        /// <param name="file">В какой файл сохранять</param>
        /// <returns>null если сохранение прошло успешно, иначе исключение которое возникло при сохранения</returns>
        public Exception? Save(FileInfo file)
        {
            try
            {
                var o = new JsonSerializerOptions()
                {
                    WriteIndented = true,
                    Encoder = JavaScriptEncoder.Create(UnicodeRanges.BasicLatin, UnicodeRanges.Cyrillic)
                };
                using (var stream = file.CreateText())
                {
                    JsonSerializer.Serialize<ItemSet>(stream.BaseStream, this, o);
                    stream.Close();
                }
                return null;
            }
            catch (Exception ex) { return ex; }
        }

        /// <summary>
        /// Если файл был загружен, то данный метод сохраняет в файл
        /// из которого была загрузка
        /// </summary>
        /// <returns>null если сохранение прошло успешно, иначе исключение которое возникло при сохранения</returns>
        public Exception? Save()
        {
            if (file != null)
                return Save(file);
            return new Exception(Resources.ItemSet.NoFile);
        }
    }
}

using KUBC.DAYZ.ITEMS.Dictionary;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Text.Unicode;
using System.Threading.Tasks;

namespace KUBC.DAYZ.ITEMS
{
    /// <summary>
    /// Класс описания разрешенных/запрещенных 
    /// игровых предметов к сохранению в виде наборов
    /// </summary>
    public class ItemsSaveSettings
    {
        /// <summary>
        /// Как читать <see cref="BaseClasses"/>. Если установлено true
        /// то в набор не будут включены все итемы которые наследуются от классов в <see cref="BaseClasses"/>
        /// Если указано false то при сохранении набора будут включаться итемы которые наследуются 
        /// от классов указанных в <see cref="BaseClasses"/>
        /// </summary>
        [JsonIgnore]
        public bool IsBlackList
        {
            get
            {
                return BackListAsInt > 0;
            }
            set
            {
                if (value)
                {
                    BackListAsInt = 1;
                }
                else
                {
                    BackListAsInt = 0;
                }
            }
        }

        /// <summary>
        /// Костыль для преобразования значений true/false в 0/1 и наоборот
        /// </summary>
        [JsonPropertyName("IsBlackList")]
        public int BackListAsInt { get; set; } = 1;

        /// <summary>
        /// Список базовых классов
        /// </summary>
        public List<string> BaseClasses { get; set; } = [];

        /// <summary>
        /// Имя файла из которого была загрузка
        /// </summary>
        private FileInfo? file;

        /// <summary>
        /// Имя файла которое знает мод
        /// </summary>
        public const string FileName = "ItemsSetOptions.json";

        /// <summary>
        /// Получить полный путь к файлу настроек сохранения
        /// </summary>
        /// <param name="Profiles">Путь к папке профилей сервера</param>
        public static FileInfo GetFullName(DirectoryInfo Profiles)
        {
            return new FileInfo($"{Profiles.FullName}\\{Paths.DEVPATH}\\{Paths.MODPATH}\\{FileName}");
        }

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
        public static ItemsSaveSettings FromJson(FileInfo File)
        {
            
            using (var reader = File.OpenText())
            {
                var res = JsonSerializer.Deserialize<ItemsSaveSettings>(reader.BaseStream);
                reader.Close();
                if (res!= null) 
                {
                    res.file = File;
                    return res;
                }
                else
                {
                    throw new Exception(Resources.ItemsSaveSettings.NullFile);
                }
            }
        }
        /// <summary>
        /// Загрузить настройки из JSON файла
        /// </summary>
        /// <param name="profiles">Папка профилей сервера</param>
        /// <remarks>
        /// Может вызывать различные исключения, связанные как с отсутвием файлов
        /// так и с кривостью файла. в нутри метода не экранируем, что бы во внешнем приложении
        /// можно было ловить краш и понять что именно пошло не так.
        /// </remarks>
        /// <returns>Данные файла</returns>
        public static ItemsSaveSettings FromJson(DirectoryInfo profiles)
        {
            return FromJson(GetFullName(profiles));
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
                    JsonSerializer.Serialize<ItemsSaveSettings>(stream.BaseStream, this, o);
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
            if (file!=null)
                return Save(file);
            return new Exception(Resources.ItemsSaveSettings.NoFile);
        }

    }
}

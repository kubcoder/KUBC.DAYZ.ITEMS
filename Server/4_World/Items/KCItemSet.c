/** @brief описание набора итемов созданного игроком*/
class KCItemSet
{
    /** @brief никнейм игрока который аффтор данного набора*/
    string NickName;
    /** @brief SteamID игрока который это создал*/
    string SteamID;
    /** @brief  Примечания к набору. В игре не используются
    *           испольузются в веб-модуле управления
    */
    string Notes;
    /** @brief Итемы включенные в набор*/
    ref KCSaveItemCollection Items = new KCSaveItemCollection();
}
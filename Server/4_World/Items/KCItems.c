class KCItems
{
    static const string MOD_NAME = "KUBC.ITEMS";

    static void Log(string Message, KCLogLevel Level = KCLogLevel.Info)
    {
        KCLog.Write(MOD_NAME, Message, Level);
    }
}
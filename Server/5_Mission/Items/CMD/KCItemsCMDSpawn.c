/// @brief Команда спавна игрового итема
class KCItemsCMDSpawn : KCUserCMD
{
    /// @brief название команды
    static const string CMD_NAME = "spawn";
    
    /// @brief аргумент задающий кол-во создаваемых итемов
    static const string PARAM_COUNT = "c";
    
    /// @brief аргумент задающий размещение игрового итема на земле
    static const string PARAM_GROUND = "g";
    
    override string GetName()
    {
        return KCItemsCMDSpawn.CMD_NAME;
    }

    override bool OnExecute(PlayerBase user, KCTextCmd data)
    {
        if (!data.Player)
        {
            data.Player = user;
        }
        if(GetGame().IsKindOf(data.Arg[0],"dz_lightai"))
        {
            KCPlayer.SendMessage(user,"","Нельзя спавнить животных и зомби, смотри специальные команды");
            return false;
        }
        float distance = -1;
        int count = 0;
        int summaryCount;
        EntityAI eItem;
        //Расшифровываем дополнительные аргументы при наличии
        if (data.Arg.Count()>1)
        {
            for(int i=1;i<data.Arg.Count(); i++)
            {
                if (data.Arg[i][0]==PARAM_COUNT)
                {
                    TStringArray cToken = new TStringArray;
                    data.Arg[i].Split("=", cToken);
                    if (cToken.Count()>1)
                    {
                        count = cToken[1].ToInt();
                    }
                }
                if (data.Arg[i][0]==PARAM_GROUND)
                {
                    TStringArray gToken = new TStringArray;
                    data.Arg[i].Split("=", gToken);
                    if (gToken.Count()>1)
                    {
                        distance = gToken[1].ToFloat();
                        
                    }
                    if (distance < 0)
                    {
                        distance = 0;
                    }
                }

            }
        }
        if (distance<0)
        {
            if (count>0)
            {
                summaryCount = 0;
                while(summaryCount<count)
                {
                    eItem =SpawnInInventory(data.Player,data.Arg[0] );
                    if (eItem)
                    {
                        summaryCount += SetCount(eItem, count-summaryCount);                     
                    }
                    else
                    {
                        KCPlayer.SendMessage(user,"","Походу предмет " +data.Arg[0] + " несуществует в игре" );
                        return false;
                    }
                } 
                KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Предмет " +data.Arg[0] + " выдано " + count + " шт." );     
                return true;          
            }
            else
            {
                eItem = SpawnInInventory(data.Player,data.Arg[0] );
                if (eItem)
                {
                    KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Предмет " +data.Arg[0] + " выдан" );
                    return true;
                }
                else
                {
                    KCPlayer.SendMessage(user,"","Походу предмет " +data.Arg[0] + " несуществует в игре" );   
                    return false;                 
                }
            }
        }
        else
        {
            if(count>0)
            {
                summaryCount = 0;
                while(summaryCount<count)
                {
                    eItem =SpawnOnSurface(data.Player, distance, data.Arg[0] );
                    if (eItem)
                    {
                        summaryCount += SetCount(eItem, count-summaryCount);                     
                    }
                    else
                    {
                        KCPlayer.SendMessage(user,"","Походу, предмет " +data.Arg[0] + " несуществует в игре" );
                        return false;
                    }
                } 
                KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Предмет " +data.Arg[0] + " положили на земле, на дистанции " + distance + "м. " + count + " шт." );   
                return true;  
            }
            else
            {
                eItem = SpawnOnSurface(data.Player, distance ,data.Arg[0] );
                if (eItem)
                {
                    KCPlayer.SendMessage(data.Player,user.GetIdentity().GetName(),"Предмет " +data.Arg[0] + " положили на земле, на дистанции " + distance + "м." );
                    return true;
                }
                else
                {
                    KCPlayer.SendMessage(user,"","Походу предмет " +data.Arg[0] + " несуществует в игре" );   
                    return false;                 
                }

            }
        }
    }

    /// @brief Разместить предмет на поверхности
    /// @param player - рядом с каким игроком размещать предметик
    /// @param distance - на каком расстоянии от игрока спавнить предмет
    /// @param ItemName - класс предмета для создания
    /// @return Созданный итем
    EntityAI SpawnOnSurface(PlayerBase player, float distance, string ItemName)
    {
        vector pos = player.GetPosition() + player.GetDirection()*distance + vector.RandomDir2D()*Math.RandomFloatInclusive(0,0.2);
        pos[1] = GetGame().SurfaceY(pos[0],pos[2]);
        EntityAI spawnItem = EntityAI.Cast(GetGame().CreateObject(ItemName, pos,false));
        return spawnItem;
    }
    
    /// @brief Разместить предмет в инвенторе игрока
    /// @param player - рядом с каким игроком размещать предметик
    /// @param ItemName - класс предмета для создания
    /// @return Созданный итем
    EntityAI SpawnInInventory(PlayerBase player, string ItemName)
    {
        return EntityAI.Cast(player.GetHumanInventory().CreateInInventory(ItemName));
    }

    /// @brief Изменить кол-во итема
    /// @param item - число которого нужно изменить
    /// @param cCount - какое число требуется
    /// @return Сколько по факту сейчас данного итема
    int SetCount(EntityAI item, int cCount)
    {
        if (item.ConfigGetBool("canBeSplit"))
        {
            Magazine_Base mb = Magazine_Base.Cast(item);
            int qm = 0;
            if (mb)
            {
                qm = mb.GetAmmoMax();
                if (qm<1)
                {
                    qm=1;
                }
                if (cCount<qm)
                {
                    mb.ServerSetAmmoCount(cCount);
                    return cCount;
                }
                else
                {
                    return qm;                   
                }
            }
            else
            {
                float ms = item.ConfigGetFloat("varStackMax");
                if (ms<1)
                    qm = item.ConfigGetInt("varQuantityMax");
                else
                    qm = ms;
                if (qm<1)
                {
                    qm=1;
                }
                if (cCount<qm)
                {
                    ItemBase itemBs = ItemBase.Cast(item);
                    if (itemBs)
                    {
                        itemBs.SetQuantity(cCount);
                        return cCount;
                    }
                    else
                    {
                        return qm;
                    }
                }
                else
                {
                    return qm;
                }     
            }            
        }
        else
        {
            return 1;
        }
    }
}
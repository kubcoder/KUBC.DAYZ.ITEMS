class KCItemsSpawner:KCItemFabricBase
{
    PlayerBase player;

    const int MAX_ITERATION = 100;

    int Count = 1;

    float Distance = -1;

    string ItemName = "";

    private float angle = 0;

    void KCItemsSpawner(PlayerBase target)
    {
        player = target;
    }

    int Spawn()
    {
        auto eai = SpawnEntity();
        if (eai==NULL)
        {
            return 0;
        }
        int summaryCount = 0;
        int iteration = 0;
        while(iteration < MAX_ITERATION)
        {
            int setCount = Count-summaryCount;
            if (setCount <= 0)
            {
                return summaryCount;
            }
            summaryCount = summaryCount + SetCount(eai, setCount);
            if (summaryCount < Count)
            {
                eai = SpawnEntity();
                if (eai==NULL)
                {
                    return summaryCount;
                }
            }
            else
            {
                return summaryCount;
            }
            iteration++;
        }
        return summaryCount;
    }

    private EntityAI SpawnEntity()
    {
        if (Distance>-1)
        {
            return SpawnOnGround();
        }
        auto eai = EntityAI.Cast(player.GetHumanInventory().CreateInInventory(ItemName));
        if (eai==NULL)
        {
            KCItems.Log("Не смогли создать предмет ["+ItemName+"]", KCLogLevel.Error);
        }
        return eai;
    }

    private EntityAI SpawnOnGround()
    {
        vector pos = GetPosition() + RotationYaw(player.GetDirection(), angle)*Distance;
        pos[1] = GetGame().SurfaceRoadY(pos[0], pos[2], RoadSurfaceDetection.LEGACY);
        auto eai = EntityAI.Cast(GetGame().CreateObject(ItemName, pos));
        if (eai==NULL)
        {
            KCItems.Log("Не смогли создать предмет на земле ["+ItemName+"]", KCLogLevel.Error);
            return null;
        }
        eai.PlaceOnSurface();
        eai.SetOrientation(Rotate(GetOrientation(), angle * Math.RAD2DEG));
        angle = angle + 0.261799;
        return eai;
    }

    override vector GetOrientation()
    {
        return player.GetOrientation();
    }

    override vector GetPosition()
    {
        return player.GetPosition();
    }
    
}
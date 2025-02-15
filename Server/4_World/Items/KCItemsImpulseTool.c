class KCItemsImpulseTool
{
    /// @brief Игровой предмет к которому прикладываем импульс
    EntityAI tEntity;    

    
    void KCItemsImpulseTool(EntityAI entity)
    {
        tEntity = entity;
    }

    /// @brief Применить импульс по направлению движения объекта
    /// @param power сила импульса
    void FrontImpulse(float power)
    {
        ApplyImpulse(power, 0);
    }

    /// @brief Применить импульс обратно направлению движения объекта
    /// @param power сила импульса
    void BackImpulse(float power)
    {
        ApplyImpulse(power, 180);
    }

    /// @brief Применить импульс слева  к  объекту
    /// @param power сила импульса
    void LeftImpulse(float power)
    {
        ApplyImpulse(power, 90);
    }

    // @brief Применить импульс справа  к  объекту
    /// @param power сила импульса
    void RightImpulse(float power)
    {
        ApplyImpulse(power, -90);
    }


    /// @brief Применить импульс
    /// @param power сила импульса
    /// @param angle угол поворота относительно направления объекта
    void ApplyImpulse(float power, float angle)
    {
        vector pVector = vector.RotateAroundZeroDeg(tEntity.GetDirection(), vector.Up, angle);
        pVector = pVector * power;
        dBodyApplyImpulse(tEntity, pVector);        
    }
}
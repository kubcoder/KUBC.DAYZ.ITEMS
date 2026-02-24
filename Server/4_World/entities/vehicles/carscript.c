modded class CarScript
{
    void ClearEngineDamage()
    {
        SetSynchDirty();
        m_EngineDestroyed = false;
        if (m_WheelSmokeFx)
        {
            for (int i = 0; i < m_WheelSmokeFx.Count(); i++ )
            {
                Effect ps = m_WheelSmokeFx.Get(i);
                if (ps)
                {
                    SEffectManager.DestroyEffect(ps);
                }
            }
            m_WheelSmokeFx.Clear();
        }
        if (m_WheelSmokePtcFx)
        {
            m_WheelSmokePtcFx.Clear();
        }
		if (m_coolantFx)
        {
            KCItems.Log("Эффект m_coolantFx существует");
            SEffectManager.DestroyEffect(m_coolantFx);
        }
        else
        {
            KCItems.Log("Эффект m_coolantFx НЕ существует");
        }
        if (m_exhaustFx)
        {
            KCItems.Log("Эффект m_exhaustFx существует");
            SEffectManager.DestroyEffect(m_exhaustFx);
        }
        else
        {
            KCItems.Log("Эффект m_exhaustFx НЕ существует");
        }
		if (m_engineFx)
        {
            KCItems.Log("Эффект m_engineFx существует");
            SEffectManager.DestroyEffect(m_engineFx);
        }
        else
        {
            KCItems.Log("Эффект m_engineFx НЕ существует");
        }
        SEffectManager.DestroyEffect(m_engineFx);
	
		SEffectManager.DestroyEffect(m_CrashSoundLight);
		SEffectManager.DestroyEffect(m_CrashSoundHeavy);
		SEffectManager.DestroyEffect(m_WindowSmall);
		SEffectManager.DestroyEffect(m_WindowLarge);
		CleanupSound(m_CarHornSoundEffect);
        SetSynchDirty();
        KCItems.Log("Попытались удалить все эффекты");
    }

    override void CreateCarDestroyedEffect()
	{
        super.CreateCarDestroyedEffect();
        KCItems.Log("Вызван эффект дыма мотора");
        if (m_engineFx)
        {
            KCItems.Log("Эффект m_engineFx существует");
        }
        else
        {
            KCItems.Log("Эффект m_engineFx НЕ существует");
        }
	}
}
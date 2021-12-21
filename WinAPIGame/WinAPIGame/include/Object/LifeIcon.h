#pragma once
#include "UIObj.h"
class LifeIcon :
    public UIObj
{
private:
    friend class Obj;
    friend class PlayerLifeUI;

public:
    LifeIcon();
    LifeIcon(const LifeIcon& ui);
    ~LifeIcon();

private:
    bool m_bEnable;

    // Set ÇÔ¼ö
public:
    void SetEnable(bool bEnable)
    {
        m_bEnable = bEnable;
        SetTextureByEnable();
    }
    void SetTextureByEnable();

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);
    virtual LifeIcon* Clone();
};


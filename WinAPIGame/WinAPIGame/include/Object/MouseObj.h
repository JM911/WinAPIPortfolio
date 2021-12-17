#pragma once
#include "UIObj.h"

class MouseObj :
    public UIObj
{
private:
    friend class Obj;
    friend class Scene;

private:
    MouseObj();
    MouseObj(const MouseObj& mouse);
    ~MouseObj();

private:
    POSITION    m_tClientPos;

    // Get ÇÔ¼ö
public:
    POSITION GetClientPos() const
    {
        return m_tClientPos;
    }

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);
    virtual MouseObj* Clone();
};


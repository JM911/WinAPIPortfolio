#pragma once
#include "Obj.h"
class UIObj :
    public Obj
{
protected:
    UIObj();
    UIObj(const UIObj& ui);
    ~UIObj();

public:
    virtual bool Init() = 0;
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);
    virtual UIObj* Clone() = 0;
};


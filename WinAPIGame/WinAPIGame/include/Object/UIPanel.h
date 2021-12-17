#pragma once
#include "UIObj.h"

class UIPanel :
    public UIObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    UIPanel();
    UIPanel(const UIPanel& ui);
    ~UIPanel();

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);
    virtual UIPanel* Clone();
};


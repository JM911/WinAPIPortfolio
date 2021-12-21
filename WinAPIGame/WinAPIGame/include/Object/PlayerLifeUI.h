#pragma once
#include "UIObj.h"

class PlayerLifeUI :
    public UIObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    PlayerLifeUI();
    PlayerLifeUI(const PlayerLifeUI& ui);
    ~PlayerLifeUI();

private:
    vector<class LifeIcon*> m_vecLifeIcon;
    int m_iPrevLife;

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);
    virtual PlayerLifeUI* Clone();
};


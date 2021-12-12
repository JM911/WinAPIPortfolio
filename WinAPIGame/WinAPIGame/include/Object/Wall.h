#pragma once
#include "StaticObj.h"

class Wall :
    public StaticObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    Wall();
    Wall(const Wall& ground);
    ~Wall();

protected:
    int m_iHeight;

public:
    virtual bool Init();
    bool Init(int tHeight);
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Wall* Clone();
};


#pragma once
#include "StaticObj.h"

class TestPlatform :
    public StaticObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    TestPlatform();
    TestPlatform(const TestPlatform& platform);
    ~TestPlatform();

public:
    virtual bool Init();
    bool Init(POSITION tPos, _SIZE tSize);
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual TestPlatform* Clone();
};


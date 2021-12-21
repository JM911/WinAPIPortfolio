#pragma once
#include "StaticObj.h"

class StageClearObj :
    public StaticObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    StageClearObj();
    StageClearObj(const StageClearObj& clear);
    ~StageClearObj();

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual StageClearObj* Clone();
};


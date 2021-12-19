#pragma once
#include "TilePlatform.h"

class Needle :
    public TilePlatform
{
private:
    friend class Obj;
    friend class Scene;

protected:
    Needle();
    Needle(const Needle& needle);
    ~Needle();

public:
    virtual bool Init();
    virtual bool Init(POSITION tPos, int iTileNumX, int iTileNumY);
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Needle* Clone();
};


#pragma once
#include "StaticObj.h"

class TilePlatform :
    public StaticObj
{
private:
    friend class Obj;

protected:
    TilePlatform();
    TilePlatform(const TilePlatform& tilePlatform);
    virtual ~TilePlatform();

private:
    vector<class Tile*> m_vecTile;

public:
    virtual bool Init();
    virtual bool Init(POSITION tPos, int iTileNumX, int iTileNumY);
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual TilePlatform* Clone();
};


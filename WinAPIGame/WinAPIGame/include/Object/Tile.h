#pragma once
#include "StaticObj.h"

class Tile :
    public StaticObj
{
private:
    friend class Obj;
    friend class TilePlatform;

protected:
    Tile();
    Tile(const Tile& tile);
    ~Tile();

    // TODO: Init함수 새로 만들어서 다른 텍스쳐도 불러올 수 있도록 설정.

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Tile* Clone();
};


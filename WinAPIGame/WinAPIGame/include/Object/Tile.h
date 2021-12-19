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

    // TODO: Init�Լ� ���� ���� �ٸ� �ؽ��ĵ� �ҷ��� �� �ֵ��� ����.

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Tile* Clone();
};


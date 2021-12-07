#pragma once
#include "Creature.h"

class Player :
    public Creature
{
private:
    friend class Obj;   // 왜 있는지는 모르겠는데 일단 가져옴
    friend class Scene;

public:     // TODO: 테스트 끝나면 protected로 수정
    Player();
    Player(const Player& player);
    ~Player();

// TODO: 방향 등 필요한 요소 추가

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual MoveObj* Clone();
};


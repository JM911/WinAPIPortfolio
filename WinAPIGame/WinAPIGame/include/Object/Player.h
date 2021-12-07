#pragma once
#include "Creature.h"

class Player :
    public Creature
{
private:
    friend class Obj;   // �� �ִ����� �𸣰ڴµ� �ϴ� ������
    friend class Scene;

public:     // TODO: �׽�Ʈ ������ protected�� ����
    Player();
    Player(const Player& player);
    ~Player();

// TODO: ���� �� �ʿ��� ��� �߰�

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual MoveObj* Clone();
};

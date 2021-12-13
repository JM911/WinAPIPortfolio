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
private:
    int m_iDir;

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual MoveObj* Clone();

    // �Ʒ��δ� �÷��̾� ���� ���� ����, �Լ�
private:
    float   m_fDashTime;
    bool    m_bJumpEnable;
    bool    m_bDashEnable;

    bool    m_bDashRight;
    bool    m_bDashLeft;
    bool    m_bDashUp;
    bool    m_bDashDown;

    bool    m_bDashUpRight;
    bool    m_bDashUpLeft;
    bool    m_bDashDownRight;
    bool    m_bDashDownLeft;

    float   fWallJumpTime;
    bool    m_bWallCliff;
    bool    m_bOnWall;
    bool    m_bLeftWallJumpEnable;
    bool    m_bLeftWallJumping;
    bool    m_bRightWallJumpEnable;
    bool    m_bRightWallJumping;

private:
    void DashRight(float fDeltaTime);
    void DashLeft(float fDeltaTime);
    void DashUp(float fDeltaTime);
    void DashDown(float fDeltaTime);

    void DashUpRight(float fDeltaTime);
    void DashUpLeft(float fDeltaTime);
    void DashDownRight(float fDeltaTime);
    void DashDownLeft(float fDeltaTime);

private:
    void StandOnGround(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
    void CollisionWithPlatform(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
    void OffWall(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
};


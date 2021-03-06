#pragma once
#include "Creature.h"

class Player :
    public Creature
{
private:
    friend class Obj;
    friend class Scene;

public:     // TODO: 테스트 끝나면 protected로 수정
    Player();
    Player(const Player& player);
    ~Player();

    // TODO: 방향 등 필요한 요소 추가
private:
    int m_iDir;
    static int m_iLife;

    // Get 함수
public:
    static int GetLife()
    {
        return m_iLife;
    }

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual MoveObj* Clone();

    // 아래로는 플레이어 조작 관련 변수, 함수
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

    PLAYER_ANI_STATUS m_eAniStatus;

    float   m_fJumpTime;
    bool    m_bWalking;
    bool    m_bOnGround;
    bool    m_bJumping;

private:
    void DashRight(float fDeltaTime);
    void DashLeft(float fDeltaTime);
    void DashUp(float fDeltaTime);
    void DashDown(float fDeltaTime);

    void DashUpRight(float fDeltaTime);
    void DashUpLeft(float fDeltaTime);
    void DashDownRight(float fDeltaTime);
    void DashDownLeft(float fDeltaTime);

    void Die();

    // 충돌함수
private:
    void StandOnGround(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
    void OffGround(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
    
    void CollisionWithPlatform(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
    void OffWall(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
    
    void CollisionWithNeedle(class Collider* pSrc, class Collider* pDest, float fDeltaTime);

    void CollisionWithDashball(class Collider* pSrc, class Collider* pDest, float fDeltaTime);

    void CollisionWithStageClear(class Collider* pSrc, class Collider* pDest, float fDeltaTime);

    void CollisionWithStrawberry(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
};


#pragma once
#include "StaticObj.h"
class Dashball :
    public StaticObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    Dashball();
    Dashball(const Dashball& ball);
    ~Dashball();

private:
    bool    m_bEnable;
    float   m_fReviveTime;
    float   m_fTime;

    // Get 함수
public:
    bool GetEnable()    const
    {
        return m_bEnable;
    }

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Dashball* Clone();

    // TODO: 충돌함수 추가 - 플레이어와 충돌하면 사라지고(텍스쳐를 빈 화면으로 출력) Enable = false 설정
    void CollisionWithPlayer(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
};


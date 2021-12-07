#pragma once
#include "Obj.h"

class MoveObj :
    public Obj
{
protected:
    MoveObj();
    MoveObj(const MoveObj& obj);
    ~MoveObj();

protected:
    // TODO: 움직임에 필요한 변수들 추가
    float       m_fMass;
    POSITION    m_tSpeed;
    POSITION    m_tAccel;

// Get 함수
public:
    float GetMass()     const
    {
        return m_fMass;
    }
    POSITION GetSpeed() const
    {
        return m_tSpeed;
    }
    POSITION GetAccel() const
    {
        return m_tAccel;
    }

// Set 함수
public:
    void SetMass(float fMass)
    {
        m_fMass = fMass;
    }
    void SetSpeed(POSITION tSpeed)
    {
        m_tSpeed = tSpeed;
    }
    void SetSpeed(float fSpeedX, float fSpeedY)
    {
        m_tSpeed.x = fSpeedX;
        m_tSpeed.y = fSpeedY;
    }
    void SetAccel(POSITION tAccel)
    {
        m_tAccel = tAccel;
    }
    void SetAccel(float fAccelX, float fAccelY)
    {
        m_tAccel.x = fAccelX;
        m_tAccel.y = fAccelY;
    }

public:
    // TODO: 움직임 함수 추가

public:
    virtual bool Init() = 0;
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual MoveObj* Clone() = 0;
};


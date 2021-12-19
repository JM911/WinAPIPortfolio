#include "MoveObj.h"

MoveObj::MoveObj()  :  // TODO: 변수들 모두 초기화했는지 확인!
    m_fMass(0.f),
    m_tSpeed(0.f, 0.f),
    m_tAccel(0.f, 2000.f)
{
}

MoveObj::MoveObj(const MoveObj& obj)    :    // TODO: 변수들 모두 복사or초기화 됐는지 확인!
    Obj(obj)
{
    m_fMass = obj.m_fMass;
    m_tSpeed = obj.m_tSpeed;
    m_tAccel = obj.m_tAccel;
}

MoveObj::~MoveObj()
{
}

void MoveObj::Input(float fDeltaTime)
{
    Obj::Input(fDeltaTime);
}

int MoveObj::Update(float fDeltaTime)
{
    m_tSpeed.x += m_tAccel.x * fDeltaTime;
    m_tSpeed.y += m_tAccel.y * fDeltaTime;

    m_tPos.x += m_tSpeed.x * fDeltaTime;
    m_tPos.y += m_tSpeed.y * fDeltaTime;

    if (m_tPos.y > 1080)    // 임시 제한
    {
        m_tPos.y = 1080;
        m_tSpeed.y = 0;
    }

    // TODO: 종단속도 처리
    if (m_tSpeed.y > 600)
        m_tSpeed.y = 600;

    Obj::Update(fDeltaTime);
    return 0;
}

int MoveObj::LateUpdate(float fDeltaTime)
{
    Obj::LateUpdate(fDeltaTime);
    return 0;
}

void MoveObj::Collision(float fDeltaTime)
{
    Obj::Collision(fDeltaTime);
}

void MoveObj::Render(HDC hDC, float fDeltaTime)
{
    Obj::Render(hDC, fDeltaTime);

    // TODO: 움직임 상태 변수가 있다면 여기서 false 대입
}

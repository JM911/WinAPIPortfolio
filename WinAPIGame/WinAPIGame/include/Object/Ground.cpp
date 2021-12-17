#include "Ground.h"
#include "../Core.h"
#include "../Collider/ColliderRect.h"

Ground::Ground()	:
	m_iHeight(100)
{
}

Ground::Ground(const Ground& ground)	:
	StaticObj(ground)
{
	m_iHeight = ground.m_iHeight;
}

Ground::~Ground()
{
}

bool Ground::Init()
{
	// 월드 좌우로 100 튀어나오고 월드 아래로 100 튀어나오게 만듦
	SetPos(-100.f, (float)GETWORLDRES.iH - m_iHeight);
	SetSize(GETWORLDRES.iW + 200.f, m_iHeight + 100.f);
	SetPivot(0.0f, 0.0f);

	// 똑같은 크기의 RECT 충돌체 설정
	EraseCollider("GroundBody");

	ColliderRect* pRC = AddCollider<ColliderRect>("GroundBody");
	pRC->SetRect(0, 0, (int)m_tSize.x, (int)m_tSize.y);

	SAFE_RELEASE(pRC);

	return true;
}

bool Ground::Init(int tHeight)
{
	m_iHeight = tHeight;
	Init();

	return true;
}

void Ground::Input(float fDeltaTime)
{
	StaticObj::Input(fDeltaTime);
}

int Ground::Update(float fDeltaTime)
{
	StaticObj::Update(fDeltaTime);
	return 0;
}

int Ground::LateUpdate(float fDeltaTime)
{
	StaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void Ground::Collision(float fDeltaTime)
{
	StaticObj::Collision(fDeltaTime);
}

void Ground::Render(HDC hDC, float fDeltaTime)
{
	StaticObj::Render(hDC, fDeltaTime);
}

Ground* Ground::Clone()
{
	return new Ground(*this);
}

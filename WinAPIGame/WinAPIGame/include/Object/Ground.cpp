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

void Ground::SetGroundInfo(float fStartX, int iWidth, int iHeight)
{
	m_fStartX = fStartX;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	
	SetPos(m_fStartX, (float)GETWORLDRES.iH - m_iHeight);
	SetSize((float)m_iWidth, m_iHeight + 100.f);

	// 똑같은 크기의 RECT 충돌체 설정
	ColliderRect* pRC = AddCollider<ColliderRect>("GroundBody");
	pRC->SetRect(0, 0, (int)m_tSize.x, (int)m_tSize.y);

	SAFE_RELEASE(pRC);
}

bool Ground::Init()
{
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

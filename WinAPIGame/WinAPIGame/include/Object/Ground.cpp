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
	// ���� �¿�� 100 Ƣ����� ���� �Ʒ��� 100 Ƣ����� ���� => ���߿� �¿� ���� ����� �Ǹ� ������ ���ڰ� ������ ���� ����
	SetPos(-100.f, GETWORLDRES.iH - m_iHeight);
	SetSize(GETWORLDRES.iW + 200.f, m_iHeight + 100.f);
	SetPivot(0.0f, 0.0f);

	// �Ȱ��� ũ���� RECT �浹ü ����
	ColliderRect* pRC = AddCollider<ColliderRect>("GroundBody");
	pRC->SetRect(0, 0, m_tSize.x, m_tSize.y);

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

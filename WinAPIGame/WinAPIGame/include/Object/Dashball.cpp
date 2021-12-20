#include "Dashball.h"
#include "../Collider/ColliderCircle.h"

Dashball::Dashball()	:
	m_bEnable(true),
	m_fReviveTime(2.f),
	m_fTime(0.f)
{
}

Dashball::Dashball(const Dashball& ball)	:
	StaticObj(ball)
{
	m_bEnable = true;
}

Dashball::~Dashball()
{
}

bool Dashball::Init()
{
	SetPivot(0.5f, 0.5f);
	SetSize(32, 32);
	SetTexture("DashballTex", L"Interactive/Dashball.bmp");
	SetColorKey(255, 255, 255);

	ColliderCircle* pCC = AddCollider<ColliderCircle>("DashballBody");
	pCC->SetCircle(POSITION(0.f, 0.f), GetSize().x / 2);

	pCC->AddCollisionFunction(COL_STATE::ENTER, this, &Dashball::CollisionWithPlayer);

	SAFE_RELEASE(pCC);

	return true;
}

void Dashball::Input(float fDeltaTime)
{
	StaticObj::Input(fDeltaTime);
}

int Dashball::Update(float fDeltaTime)
{
	StaticObj::Update(fDeltaTime);

	if (!m_bEnable)
	{
		if (m_fTime < m_fReviveTime)
		{
			SetTexture("UnableBallTex", L"Interactive/Unable.bmp");
			SetColorKey(255, 255, 255);
			m_fTime += fDeltaTime;
		}
		else
		{
			SetTexture("DashballTex", L"Interactive/Dashball.bmp");
			SetColorKey(255, 255, 255);
			m_fTime = 0.f;
			m_bEnable = true;
		}
	}

	return 0;
}

int Dashball::LateUpdate(float fDeltaTime)
{
	StaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void Dashball::Collision(float fDeltaTime)
{
	StaticObj::Collision(fDeltaTime);
}

void Dashball::Render(HDC hDC, float fDeltaTime)
{
	StaticObj::Render(hDC, fDeltaTime);
}

Dashball* Dashball::Clone()
{
	return new Dashball(*this);
}

void Dashball::CollisionWithPlayer(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "PlayerBody")
	{
		m_bEnable = false;
	}
}
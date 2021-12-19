#include "Needle.h"
#include "../Collider/ColliderRect.h"

Needle::Needle()
{
}

Needle::Needle(const Needle& needle)	:
	TilePlatform(needle)
{
}

Needle::~Needle()
{
}

bool Needle::Init()
{
	return true;
}

bool Needle::Init(POSITION tPos, int iTileNumX, int iTileNumY)
{
	TilePlatform::SetPlatform(tPos, iTileNumX, iTileNumY);

	EraseCollider("PlatformBody");

	ColliderRect* pRC = AddCollider<ColliderRect>("NeedleBody");
	pRC->SetRect(0, 0, (int)m_tSize.x, (int)m_tSize.y);
	SAFE_RELEASE(pRC);

	return true;
}

void Needle::Input(float fDeltaTime)
{
	TilePlatform::Input(fDeltaTime);
}

int Needle::Update(float fDeltaTime)
{
	TilePlatform::Update(fDeltaTime);
	return 0;
}

int Needle::LateUpdate(float fDeltaTime)
{
	TilePlatform::LateUpdate(fDeltaTime);
	return 0;
}

void Needle::Collision(float fDeltaTime)
{
	TilePlatform::Collision(fDeltaTime);
}

void Needle::Render(HDC hDC, float fDeltaTime)
{
	TilePlatform::Render(hDC, fDeltaTime);
}

Needle* Needle::Clone()
{
	return new Needle(*this);
}

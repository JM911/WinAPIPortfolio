#include "TestPlatform.h"
#include "../Collider/ColliderRect.h"

TestPlatform::TestPlatform()
{
}

TestPlatform::TestPlatform(const TestPlatform& platform)	:
	StaticObj(platform)
{
}

TestPlatform::~TestPlatform()
{
}

bool TestPlatform::Init()
{
	return true;
}

bool TestPlatform::Init(POSITION tPos, _SIZE tSize)
{
	SetPos(tPos);
	SetSize(tSize);
	SetPivot(0.f, 0.f);

	ColliderRect* pRC = AddCollider<ColliderRect>("PlatformBody");	
	pRC->SetRect(0, 0, (int)m_tSize.x, (int)m_tSize.y);

	SAFE_RELEASE(pRC);

	return true;
}

void TestPlatform::Input(float fDeltaTime)
{
	StaticObj::Input(fDeltaTime);
}

int TestPlatform::Update(float fDeltaTime)
{
	StaticObj::Update(fDeltaTime);
	return 0;
}

int TestPlatform::LateUpdate(float fDeltaTime)
{
	StaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void TestPlatform::Collision(float fDeltaTime)
{
	StaticObj::Collision(fDeltaTime);
}

void TestPlatform::Render(HDC hDC, float fDeltaTime)
{
	StaticObj::Render(hDC, fDeltaTime);
}

TestPlatform* TestPlatform::Clone()
{
	return new TestPlatform(*this);
}

#include "Strawberry.h"
#include "../Collider/ColliderCircle.h"

Strawberry::Strawberry()	:
	m_bEnable(true)
{
}

Strawberry::Strawberry(const Strawberry& berry)	:
	StaticObj(berry)
{
	m_bEnable = berry.m_bEnable;
}

Strawberry::~Strawberry()
{
}

bool Strawberry::Init()
{
	// TODO: 사이즈, 텍스처 등 설정
	SetSize(32, 32);
	SetPivot(0.5f, 0.5f);
	SetTexture("StrawberryTex", L"Interactive/Strawberry.bmp");
	SetColorKey(255, 255, 255);

	// TODO: 충돌체 설정
	ColliderCircle* pCC = AddCollider<ColliderCircle>("StrawberryBody");

	pCC->AddCollisionFunction(COL_STATE::ENTER, this, &Strawberry::CollisionWithPlayer);

	SAFE_RELEASE(pCC);

	return true;
}

void Strawberry::Input(float fDeltaTime)
{
	StaticObj::Input(fDeltaTime);
}

int Strawberry::Update(float fDeltaTime)
{
	StaticObj::Update(fDeltaTime);
	return 0;
}

int Strawberry::LateUpdate(float fDeltaTime)
{
	StaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void Strawberry::Collision(float fDeltaTime)
{
	StaticObj::Collision(fDeltaTime);
}

void Strawberry::Render(HDC hDC, float fDeltaTime)
{
	StaticObj::Render(hDC, fDeltaTime);
}

Strawberry* Strawberry::Clone()
{
	return new Strawberry(*this);
}

void Strawberry::CollisionWithPlayer(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "PlayerBody")
	{
		m_bEnable = false;
		SetTexture("UnableBerryTex", L"Interactive/Unable.bmp");
		SetColorKey(255, 255, 255);
	}
}

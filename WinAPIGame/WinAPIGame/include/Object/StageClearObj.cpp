#include "StageClearObj.h"
#include "../Collider/ColliderRect.h"

StageClearObj::StageClearObj()
{
}

StageClearObj::StageClearObj(const StageClearObj& clear)	:
	StaticObj(clear)
{
}

StageClearObj::~StageClearObj()
{
}

bool StageClearObj::Init()
{
	SetPos(3720, 550);	// 임시 위치(Scene에서도 수정 가능)
	SetSize(50, 80);
	// TODO: 텍스처 설정?
	SetTexture("StageClearTex", L"Interactive/StageClear.bmp");
	SetColorKey(255, 255, 255);

	ColliderRect* pRC = AddCollider<ColliderRect>("StageClearBody");
	pRC->SetRect(0, 0, (int)GetSize().x, (int)GetSize().y);
	SAFE_RELEASE(pRC);

	return true;
}

void StageClearObj::Input(float fDeltaTime)
{
	StaticObj::Input(fDeltaTime);
}

int StageClearObj::Update(float fDeltaTime)
{
	StaticObj::Update(fDeltaTime);
	return 0;
}

int StageClearObj::LateUpdate(float fDeltaTime)
{
	StaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void StageClearObj::Collision(float fDeltaTime)
{
	StaticObj::Collision(fDeltaTime);
}

void StageClearObj::Render(HDC hDC, float fDeltaTime)
{
	StaticObj::Render(hDC, fDeltaTime);
}

StageClearObj* StageClearObj::Clone()
{
	return new StageClearObj(*this);
}

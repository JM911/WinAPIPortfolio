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
	SetPos(1500, 600);	// �ӽ� ��ġ(Scene������ ���� ����)
	SetSize(30, 30);
	// TODO: �ؽ�ó ����?

	ColliderRect* pRC = AddCollider<ColliderRect>("StageClearBody");
	pRC->SetRect(0, 0, 30, 30);
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

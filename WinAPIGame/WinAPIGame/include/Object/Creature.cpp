#include "Creature.h"

Creature::Creature()	// TODO: 변수들 모두 초기화했는지 확인!
{
}

Creature::Creature(const Creature& creature)	:	// TODO: 변수들 모두 복사or초기화 됐는지 확인!
	MoveObj(creature)
{
}

Creature::~Creature()
{
}

void Creature::Input(float fDeltaTime)
{
	MoveObj::Input(fDeltaTime);
}

int Creature::Update(float fDeltaTime)
{
	MoveObj::Update(fDeltaTime);
	return 0;
}

int Creature::LateUpdate(float fDeltaTime)
{
	MoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void Creature::Collision(float fDeltaTime)
{
	MoveObj::Collision(fDeltaTime);
}

void Creature::Render(HDC hDC, float fDeltaTime)
{
	MoveObj::Render(hDC, fDeltaTime);
}

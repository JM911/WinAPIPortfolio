#include "Creature.h"

Creature::Creature()	// TODO: ������ ��� �ʱ�ȭ�ߴ��� Ȯ��!
{
}

Creature::Creature(const Creature& creature)	:	// TODO: ������ ��� ����or�ʱ�ȭ �ƴ��� Ȯ��!
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

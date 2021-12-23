#include "Creature.h"
#include "../Core/CInput.h"

Creature::Creature()	:	// TODO: 변수들 모두 초기화했는지 확인!
	m_bStarted(false)
{
}

Creature::Creature(const Creature& creature)	:	// TODO: 변수들 모두 복사or초기화 됐는지 확인!
	MoveObj(creature)
{
	m_bStarted = false;
}

Creature::~Creature()
{
}

void Creature::Input(float fDeltaTime)
{
	if (KEYPRESS("MoveRight") || KEYPRESS("MoveLeft"))
		m_bStarted = true;

	MoveObj::Input(fDeltaTime);
}

int Creature::Update(float fDeltaTime)
{
	if (!m_bStarted)
		m_tPos.y = 500;

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

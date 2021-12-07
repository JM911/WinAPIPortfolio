#include "Player.h"

Player::Player()	// TODO: 변수들 모두 초기화했는지 확인!
{
}

Player::Player(const Player& player)	:	// TODO: 변수들 모두 복사or초기화 됐는지 확인!
	Creature(player)
{
}

Player::~Player()
{
}

bool Player::Init()
{
	SetPos(200.f, 100.f);
	SetSize(100.f, 100.f);
	SetSpeed(0.f, 0.f);
	SetPivot(0.5f, 0.5f);

	return true;
}

void Player::Input(float fDeltaTime)
{
	Creature::Input(fDeltaTime);
}

int Player::Update(float fDeltaTime)
{
	Creature::Update(fDeltaTime);
	return 0;
}

int Player::LateUpdate(float fDeltaTime)
{
	Creature::LateUpdate(fDeltaTime);
	return 0;
}

void Player::Collision(float fDeltaTime)
{
	Creature::Collision(fDeltaTime);
}

void Player::Render(HDC hDC, float fDeltaTime)
{
	Creature::Render(hDC, fDeltaTime);

	POSITION tPos;
	tPos.x = m_tPos.x - m_tSize.x * m_tPivot.x;
	tPos.y = m_tPos.y - m_tSize.y * m_tPivot.y;

	Rectangle(hDC, (int)tPos.x, (int)tPos.y, (int)(tPos.x + m_tSize.x), (int)(tPos.y + m_tSize.y));
}

MoveObj* Player::Clone()
{
	return new Player(*this);
}

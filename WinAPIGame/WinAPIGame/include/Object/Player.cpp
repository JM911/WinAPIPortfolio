#include "Player.h"
#include "../Core/CInput.h"
#include "../Resources/Texture.h"
#include "../Animation/Animation.h"

Player::Player()	:	// TODO: 변수들 모두 초기화했는지 확인!
	m_iDir(1),
	fDashTime(0.f)
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
	SetSize(32.f, 32.f);
	SetSpeed(0.f, 0.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Player", L"Base_1.bmp");
	SetColorKey(255, 0, 255);

	Animation* pAni = CreateAnimation("PlayerAnimation");

	// 애니메이션 추가 (프레임 타입)
	vector<wstring> vecFileName;

	for (int i = 0; i < 12; i++)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"PlayerWalk/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClipFrame("WalkRight", ANI_OPTION::LOOP, 1.f, 12, 0.f, _SIZE(32.f, 32.f), "PlayerWalkRight", vecFileName);
	SetAnimationClipColorKey("WalkRight", 255, 255, 255);

	return true;
}

void Player::Input(float fDeltaTime)
{
	Creature::Input(fDeltaTime);

	if (KEYPRESS("MoveLeft"))		// 왼쪽 방향키
	{
		m_tPos.x -= 200 * fDeltaTime;
		m_iDir = -1;
	}

	if (KEYPRESS("MoveRight"))		// 오른쪽 방향키
	{
		m_tPos.x += 200 * fDeltaTime;
		m_iDir = 1;
	}

	if (KEYDOWN("Jump"))			// Z
	{
		m_tSpeed.y = -1000.f;
	}

	if (KEYPRESS("DashRight"))		// → + X
	{
		fDashTime += fDeltaTime;
		if (fDashTime <= 0.1f)
			m_tPos.x += 2000 * fDeltaTime;
	}

	if (KEYUP("DashRight"))
	{
		fDashTime = 0.f;
	}

	if (KEYPRESS("DashLeft"))		// ← + X
	{
		fDashTime += fDeltaTime;
		if (fDashTime <= 0.1f)
			m_tPos.x -= 2000 * fDeltaTime;
	}

	if (KEYUP("DashLeft"))
	{
		fDashTime = 0.f;
	}
	
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

	/*POSITION tPos;
	tPos.x = m_tPos.x - m_tSize.x * m_tPivot.x;
	tPos.y = m_tPos.y - m_tSize.y * m_tPivot.y;*/

	//Rectangle(hDC, (int)tPos.x, (int)tPos.y, (int)(tPos.x + m_tSize.x), (int)(tPos.y + m_tSize.y));
}

MoveObj* Player::Clone()
{
	return new Player(*this);
}
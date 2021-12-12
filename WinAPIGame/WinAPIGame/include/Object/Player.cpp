#include "Player.h"
#include "../Core/CInput.h"
#include "../Resources/Texture.h"
#include "../Animation/Animation.h"
#include "../Collider/ColliderRect.h"

Player::Player()	:	// TODO: 변수들 모두 초기화했는지 확인!
	m_iDir(1),
	fDashTime(0.f),
	bJumpEnable(true),
	bDashEnable(true)
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


	// 충돌체 추가 (Rect 타입)
	ColliderRect* pRC = AddCollider<ColliderRect>("PlayerBody");

	pRC->SetRect(-16, -16, 16, 16);
	// TODO: 충돌이 일어났을 때의 함수 추가 및 AddCollisionFunction 호출
	pRC->AddCollisionFunction(COL_STATE::ENTER, this, &Player::StandOnGround);
	pRC->AddCollisionFunction(COL_STATE::STAY, this, &Player::StandOnGround);

	SAFE_RELEASE(pRC);

	return true;
}

void Player::Input(float fDeltaTime)
{
	Creature::Input(fDeltaTime);

	// TODO: 움직임 하드코딩 한 거 함수 따로 만들어서 호출, 숫자 하드코딩 전부 변수로 변경
	if (KEYPRESS("MoveLeft"))		// 왼쪽 방향키
	{
		m_tPos.x -= 200 * fDeltaTime;
		//m_tSpeed.x = -200;
		m_iDir = -1;
	}

	if (KEYUP("MoveLeft"))
	{
		//m_tSpeed.x += 200;
	}

	if (KEYPRESS("MoveRight"))		// 오른쪽 방향키
	{
		m_tPos.x += 200 * fDeltaTime;
		m_iDir = 1;
	}

	if (KEYUP("MoveRight"))
	{
		//m_tSpeed.x -= 200;
	}

	if (KEYDOWN("Jump") && bJumpEnable)			// C
	{
		m_tSpeed.y = -700.f;
		bJumpEnable = false;
	}

	if (KEYPRESS("DashRight") && bDashEnable)		// → + X
	{
		m_tSpeed.x = 2000;
		m_tSpeed.y = 0;
		fDashTime += fDeltaTime;
		if (fDashTime > 0.1f)
		{
			m_tSpeed.x -= 2000;
			bDashEnable = false;
		}
	}

	if (KEYUP("DashRight"))
	{
		fDashTime = 0.f;
		m_tSpeed.x = 0;
		bDashEnable = false;
	}

	if (KEYPRESS("DashLeft") && bDashEnable)		// ← + X
	{
		m_tSpeed.x = -2000;
		m_tSpeed.y = 0;
		fDashTime += fDeltaTime;
		if (fDashTime > 0.1f)
		{
			m_tSpeed.x += 2000;
			bDashEnable = false;
		}
	}

	if (KEYUP("DashLeft"))
	{
		fDashTime = 0.f;
		m_tSpeed.x = 0;
		bDashEnable = false;
	}

	if (KEYPRESS("DashUp") && bDashEnable)		// ↑ + X
	{
		m_tSpeed.y = -2000;
		fDashTime += fDeltaTime;
		if (fDashTime > 0.1f)
		{
			m_tSpeed.y += 2000;
			bDashEnable = false;
		}
	}

	if (KEYUP("DashUp"))
	{
		fDashTime = 0.f;
		m_tSpeed.y = 0;
		bDashEnable = false;
	}

	if (KEYPRESS("DashDown") && bDashEnable)		// ↓ + X
	{
		m_tSpeed.y = 2000;
		fDashTime += fDeltaTime;
		if (fDashTime > 0.1f)
		{
			m_tSpeed.y -= 2000;
			bDashEnable = false;
		}
	}

	if (KEYUP("DashDown"))
	{
		fDashTime = 0.f;
		m_tSpeed.y = 0;
		bDashEnable = false;
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

void Player::StandOnGround(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
	if (pDest->GetObj()->GetTag() == "Ground")
	{
		RECT tRC = { 0, 0, 0, 0 };
		list<Collider*>::iterator iter;
		list<Collider*>::iterator iterEnd = m_ColliderList.end();

		for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter)->GetTag() == "PlayerBody")
			{
				tRC = ((ColliderRect*)(*iter))->GetIntersectInfo();
				break;
			}
		}

		//int iInterW = tRC.right - tRC.left;
		int iInterH = tRC.bottom - tRC.top;

		m_tPos.y -= iInterH;
		m_tSpeed.y = 0.f;

		bJumpEnable = true;
		bDashEnable = true;
	}
}
#include "Player.h"
#include "../Core/CInput.h"
#include "../Resources/Texture.h"
#include "../Animation/Animation.h"
#include "../Collider/ColliderRect.h"

Player::Player()	:	// TODO: 변수들 모두 초기화했는지 확인!
	m_iDir(1),
	m_fDashTime(0.f), fWallJumpTime(0.f),
	m_bJumpEnable(true), m_bDashEnable(true),
	m_bDashRight(false), m_bDashLeft(false), m_bDashUp(false), m_bDashDown(false),
	m_bDashUpRight(false), m_bDashUpLeft(false), m_bDashDownRight(false), m_bDashDownLeft(false),
	m_bWallCliff(false), m_bOnWall(false), m_bLeftWallJumpEnable(false), m_bRightWallJumpEnable(false),
	m_bLeftWallJumping(false), m_bRightWallJumping(false)
{
}

Player::Player(const Player& player)	:	// TODO: 변수들 모두 복사or초기화 됐는지 확인!
	Creature(player)
{
	m_iDir				= player.m_iDir;
	m_fDashTime			= 0.f;

	m_bJumpEnable		= player.m_bJumpEnable;
	m_bDashEnable		= player.m_bDashEnable;

	m_bDashRight		= player.m_bDashRight;
	m_bDashLeft			= player.m_bDashLeft;
	m_bDashUp			= player.m_bDashUp;
	m_bDashDown			= player.m_bDashDown;

	m_bDashUpRight		= player.m_bDashUpRight;
	m_bDashUpLeft		= player.m_bDashUpLeft;
	m_bDashDownRight	= player.m_bDashDownRight;
	m_bDashDownLeft		= player.m_bDashDownLeft;

	m_bWallCliff		= player.m_bWallCliff;
	m_bOnWall			= player.m_bOnWall;
	m_bLeftWallJumping	= player.m_bLeftWallJumping;
	m_bRightWallJumping = player.m_bRightWallJumping;
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

	pRC->AddCollisionFunction(COL_STATE::ENTER, this, &Player::CollisionWithPlatform);
	pRC->AddCollisionFunction(COL_STATE::STAY, this, &Player::CollisionWithPlatform);
	pRC->AddCollisionFunction(COL_STATE::LEAVE, this, &Player::OffWall);

	SAFE_RELEASE(pRC);

	return true;
}

void Player::Input(float fDeltaTime)
{
	Creature::Input(fDeltaTime);

	// TODO: 움직임 하드코딩 한 거 함수 따로 만들어서 호출, 숫자 하드코딩 전부 변수로 변경
	// 벽점프
	if (KEYDOWN("Jump") && m_bLeftWallJumpEnable)
	{
		m_tSpeed.y = -700.f;
		m_bLeftWallJumping = true;
		m_bLeftWallJumpEnable = false;
	}
	if (m_bLeftWallJumping)
	{
		if (fWallJumpTime < 0.1f)
		{
			m_tPos.x -= 600.f * fDeltaTime;
			fWallJumpTime += fDeltaTime;
		}
		else
		{
			m_bLeftWallJumping = false;
			fWallJumpTime = 0.f;
		}
	}
	
	if (KEYDOWN("Jump") && m_bRightWallJumpEnable)
	{
		m_tSpeed.y = -700.f;
		m_bRightWallJumping = true;
		m_bRightWallJumpEnable = false;
	}
	if (m_bRightWallJumping)
	{
		if (fWallJumpTime < 0.1f)
		{
			m_tPos.x += 600.f * fDeltaTime;
			fWallJumpTime += fDeltaTime;
		}
		else
		{
			m_bRightWallJumping = false;
			fWallJumpTime = 0.f;
		}
	}
	
	// 기본 움직임
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

	if (KEYDOWN("Jump") && m_bJumpEnable)			// C
	{
		m_tSpeed.y = -700.f;
		m_bJumpEnable = false;
	}

	// 대각선 4방향 대시 (키입력 메커니즘 때문에 앞쪽에 코딩)
	if (KEYDOWN("DashUp") && KEYDOWN("DashRight") && m_bDashEnable)
	{
		m_bDashUpRight = true;
		m_bDashEnable = false;
	}
	if (m_bDashUpRight)
		DashUpRight(fDeltaTime);

	if (KEYDOWN("DashUp") && KEYDOWN("DashLeft") && m_bDashEnable)
	{
		m_bDashUpLeft = true;
		m_bDashEnable = false;
	}
	if (m_bDashUpLeft)
		DashUpLeft(fDeltaTime);

	if (KEYDOWN("DashDown") && KEYDOWN("DashRight") && m_bDashEnable)
	{
		m_bDashDownRight = true;
		m_bDashEnable = false;
	}
	if (m_bDashDownRight)
		DashDownRight(fDeltaTime);

	if (KEYDOWN("DashDown") && KEYDOWN("DashLeft") && m_bDashEnable)
	{
		m_bDashDownLeft = true;
		m_bDashEnable = false;
	}
	if (m_bDashDownLeft)
		DashDownLeft(fDeltaTime);

	// 4방향 대시
	if (KEYDOWN("DashRight") && m_bDashEnable)
	{
		 m_bDashRight = true;
		 m_bDashEnable = false;
	}
	if (m_bDashRight)
		DashRight(fDeltaTime);

	if (KEYDOWN("DashLeft") && m_bDashEnable)
	{
		 m_bDashLeft = true;
		 m_bDashEnable = false;
	}
	if (m_bDashLeft)
		DashLeft(fDeltaTime);

	if (KEYDOWN("DashUp") && m_bDashEnable)
	{
		m_bDashUp = true;
		m_bDashEnable = false;
	}
	if (m_bDashUp)
		DashUp(fDeltaTime);

	if (KEYDOWN("DashDown") && m_bDashEnable)
	{
		m_bDashDown = true;
		m_bDashEnable = false;
	}
	if (m_bDashDown)
		DashDown(fDeltaTime);

	// 벽잡기
	if (KEYPRESS("WallCliff"))
	{
		m_bWallCliff = true;
	}
	if (KEYUP("WallCliff"))
	{
		m_bWallCliff = false;
		m_tAccel.y = 2000.f;
	}

	if (KEYPRESS("WallCliffUp") && m_bOnWall)
	{
		m_tPos.y -= 200 * fDeltaTime;
	}
	if (KEYPRESS("WallCliffDown") && m_bOnWall)
	{
		m_tPos.y += 200 * fDeltaTime;
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

void Player::DashRight(float fDeltaTime)
{
	if (m_fDashTime == 0.f)
	{
		m_tSpeed.x = 2000.f;
	}

	m_fDashTime += fDeltaTime;
	m_tSpeed.y = 0.f;

	if (m_fDashTime >= 0.1f)
	{
		m_bDashRight = false;
		m_tSpeed.x = 0.f;
		m_fDashTime = 0;
	}
}
void Player::DashLeft(float fDeltaTime)
{
	if (m_fDashTime == 0.f)
	{
		m_tSpeed.x = -2000.f;
	}

	m_fDashTime += fDeltaTime;
	m_tSpeed.y = 0.f;

	if (m_fDashTime >= 0.1f)
	{
		m_bDashLeft = false;
		m_tSpeed.x = 0.f;
		m_fDashTime = 0;
	}
}
void Player::DashUp(float fDeltaTime)
{
	if (m_fDashTime == 0.f)
	{
		m_tSpeed.y = -3000.f;
	}

	m_fDashTime += fDeltaTime;
	m_tSpeed.x = 0.f;

	if (m_fDashTime >= 0.1f)
	{
		m_bDashUp = false;
		m_tSpeed.y = 0.f;
		m_fDashTime = 0;
	}
}
void Player::DashDown(float fDeltaTime)
{
	if (m_fDashTime == 0.f)
	{
		m_tSpeed.y += 1000.f;
	}

	m_fDashTime += fDeltaTime;
	m_tSpeed.x = 0.f;

	if (m_fDashTime >= 0.1f)
	{
		m_bDashDown = false;
		m_tSpeed.y -= 1000.f;
		m_fDashTime = 0;
	}
}

void Player::DashUpRight(float fDeltaTime)
{
	if (m_fDashTime == 0.f)
	{
		m_tSpeed.x = 1000.f;
		m_tSpeed.y = -2000.f;
	}

	m_fDashTime += fDeltaTime;

	if (m_fDashTime >= 0.1f)
	{
		m_bDashUpRight = false;
		m_tSpeed.x = 0.f;
		m_tSpeed.y = 0.f;
		m_fDashTime = 0;
	}
}
void Player::DashUpLeft(float fDeltaTime)
{
	if (m_fDashTime == 0.f)
	{
		m_tSpeed.x = -1000.f;
		m_tSpeed.y = -2000.f;
	}

	m_fDashTime += fDeltaTime;

	if (m_fDashTime >= 0.1f)
	{
		m_bDashUpLeft = false;
		m_tSpeed.x = 0.f;
		m_tSpeed.y = 0.f;
		m_fDashTime = 0;
	}
}
void Player::DashDownRight(float fDeltaTime)
{
	if (m_fDashTime == 0.f)
	{
		m_tSpeed.x = 1000.f;
		m_tSpeed.y = 800.f;
	}

	m_fDashTime += fDeltaTime;

	if (m_fDashTime >= 0.1f)
	{
		m_bDashDownRight = false;
		m_tSpeed.x = 0.f;
		m_tSpeed.y = 0.f;
		m_fDashTime = 0;
	}
}
void Player::DashDownLeft(float fDeltaTime)
{
	if (m_fDashTime == 0.f)
	{
		m_tSpeed.x = -1000.f;
		m_tSpeed.y = 800.f;
	}

	m_fDashTime += fDeltaTime;

	if (m_fDashTime >= 0.1f)
	{
		m_bDashDownLeft = false;
		m_tSpeed.x = 0.f;
		m_tSpeed.y = 0.f;
		m_fDashTime = 0;
	}
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

		m_bJumpEnable = true;
		m_bDashEnable = true;

		if (m_bDashDown || m_bDashDownLeft || m_bDashDownRight)
		{
			m_bDashDown = false;
			m_bDashDownLeft = false;
			m_bDashDownRight = false;
			m_fDashTime = 0.f;
			m_tSpeed.x = 0.f;
		}
	}
}

void Player::CollisionWithPlatform(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "PlatformBody")
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

		//RECT playerRect = ((ColliderRect*)pSrc)->GetWorldInfo();
		RECT platformRect = ((ColliderRect*)pDest)->GetWorldInfo();

		int iInterW = tRC.right - tRC.left;
		int iInterH = tRC.bottom - tRC.top;

		if (iInterW > iInterH)	// (플랫폼 기준) 위아래에서 충돌
		{
			m_tSpeed.y = 0.f;
			m_bJumpEnable = true;
			m_bDashEnable = true;

			if (tRC.top == platformRect.top)	// 위에서 충돌
			{
				m_tPos.y -= iInterH;
			}
			else if (tRC.bottom == platformRect.bottom)	// 아래에서 충돌
			{
				m_tPos.y += iInterH;
			}
		}

		if (iInterW < iInterH)	// (플랫폼 기준) 좌우에서 충돌
		{
			m_tSpeed.x = 0.f;
			
			if (tRC.left == platformRect.left)	// 왼쪽에서 충돌
			{
				m_bLeftWallJumpEnable = true;
				m_tPos.x -= iInterW;
				++m_tPos.x;
			}
			else if (tRC.right == platformRect.right)	// 오른쪽에서 충돌
			{
				m_bRightWallJumpEnable = true;
				m_tPos.x += iInterW;
				--m_tPos.x;
			}

			if (m_bWallCliff)
			{
				m_tSpeed.y = 0.f;
				m_tAccel.y = 0.f;
				m_bOnWall = true;
			}
		}
	}
}

void Player::OffWall(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "PlatformBody")
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

		m_bOnWall = false;
		m_bLeftWallJumpEnable = false;
		m_bRightWallJumpEnable = false;
		m_tAccel.y = 2000.f;
	}
}

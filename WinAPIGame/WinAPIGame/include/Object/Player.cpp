#include "Player.h"
#include "../Core/CInput.h"
#include "../Resources/Texture.h"
#include "../Animation/Animation.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"
#include "../Scene/SceneManager.h"
#include "../Scene/GameOverScene.h"
#include "../Scene/TestScene.h"
#include "Dashball.h"

Player::Player() :	// TODO: 변수들 모두 초기화했는지 확인!
	m_iDir(1),
	m_fDashTime(0.f), fWallJumpTime(0.f), m_fJumpTime(0.f),
	m_bJumpEnable(true), m_bDashEnable(true), m_eAniStatus(PLAYER_ANI_STATUS::IDLE_RIGHT),
	m_bDashRight(false), m_bDashLeft(false), m_bDashUp(false), m_bDashDown(false),
	m_bDashUpRight(false), m_bDashUpLeft(false), m_bDashDownRight(false), m_bDashDownLeft(false),
	m_bWallCliff(false), m_bOnWall(false), m_bLeftWallJumpEnable(false), m_bRightWallJumpEnable(false),
	m_bLeftWallJumping(false), m_bRightWallJumping(false),
	m_bWalking(false), m_bOnGround(false), m_bJumping(false)
{
}

Player::Player(const Player& player) :	// TODO: 변수들 모두 복사or초기화 됐는지 확인!
	Creature(player)
{
	m_iDir = player.m_iDir;
	m_fDashTime = 0.f;

	m_bJumpEnable = player.m_bJumpEnable;
	m_bDashEnable = player.m_bDashEnable;

	m_bDashRight = player.m_bDashRight;
	m_bDashLeft = player.m_bDashLeft;
	m_bDashUp = player.m_bDashUp;
	m_bDashDown = player.m_bDashDown;

	m_bDashUpRight = player.m_bDashUpRight;
	m_bDashUpLeft = player.m_bDashUpLeft;
	m_bDashDownRight = player.m_bDashDownRight;
	m_bDashDownLeft = player.m_bDashDownLeft;

	m_bWallCliff = player.m_bWallCliff;
	m_bOnWall = player.m_bOnWall;
	m_bLeftWallJumping = player.m_bLeftWallJumping;
	m_bRightWallJumping = player.m_bRightWallJumping;
}

Player::~Player()
{
}

bool Player::Init()
{
	SetPos(200.f, 100.f);
	SetSize(64.f, 64.f);
	SetSpeed(0.f, 0.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Player", L"Base_1.bmp");
	SetColorKey(255, 0, 255);

	Animation* pAni = CreateAnimation("PlayerAnimation");

	// 애니메이션 추가 (프레임 타입)
	// 오른쪽 idle
	AddAnimationClipAtlas("RightIdle", ANI_OPTION::LOOP, 1.f, 3, 9, 0.f, _SIZE(64.f, 64.f), "PlayerRightIdle", L"Player/Idle/Right/atlas.bmp");
	SetAnimationClipColorKey("RightIdle", 255, 255, 255);

	// 왼쪽 idle
	AddAnimationClipAtlas("LeftIdle", ANI_OPTION::LOOP, 1.f, 3, 9, 0.f, _SIZE(64.f, 64.f), "PlayerLeftIdle", L"Player/Idle/Left/atlas.bmp");
	SetAnimationClipColorKey("LeftIdle", 255, 255, 255);

	// 왼쪽 걷기
	AddAnimationClipAtlas("WalkLeft", ANI_OPTION::LOOP, 1.f, 4, 12, 0.f, _SIZE(64.f, 64.f), "PlayerWalkLeft", L"Player/Walk/Left/atlas.bmp");
	SetAnimationClipColorKey("WalkLeft", 255, 255, 255);

	// 오른쪽 걷기
	vector<wstring> vecFileName;

	for (int i = 0; i < 12; i++)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Walk/Right/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClipFrame("WalkRight", ANI_OPTION::LOOP, 1.f, 12, 0.f, _SIZE(64.f, 64.f), "PlayerWalkRight", vecFileName);
	SetAnimationClipColorKey("WalkRight", 255, 255, 255);

	// 오른쪽 점프
	AddAnimationClipAtlas("JumpRight", ANI_OPTION::ONCE_RETURN, 0.6f, 4, 4, 0.f, _SIZE(64.f, 64.f), "PlayerJumpRight", L"Player/Jump/Right/atlas.bmp");
	SetAnimationClipColorKey("JumpRight", 255, 255, 255);

	// 왼쪽 점프
	AddAnimationClipAtlas("JumpLeft", ANI_OPTION::ONCE_RETURN, 0.6f, 4, 4, 0.f, _SIZE(64.f, 64.f), "PlayerJumpLeft", L"Player/Jump/Left/atlas.bmp");
	SetAnimationClipColorKey("JumpLeft", 255, 255, 255);

	// 오른쪽 추락
	AddAnimationClipAtlas("FallingRight", ANI_OPTION::LOOP, 0.5f, 8, 8, 0.f, _SIZE(64.f, 64.f), "PlayerFallingRight", L"Player/Falling/Right/atlas.bmp");
	SetAnimationClipColorKey("FallingRight", 255, 255, 255);

	// 왼쪽 추락
	AddAnimationClipAtlas("FallingLeft", ANI_OPTION::LOOP, 0.5f, 8, 8, 0.f, _SIZE(64.f, 64.f), "PlayerFallingLeft", L"Player/Falling/Left/atlas.bmp");
	SetAnimationClipColorKey("FallingLeft", 255, 255, 255);

	// 왼쪽 벽타기
	vecFileName.clear();

	for (int i = 0; i < 14; i++)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Climb/LeftWall/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClipFrame("LeftWallClimb", ANI_OPTION::LOOP, 1.f, 14, 0.f, _SIZE(64.f, 64.f), "PlayerLeftWallClimb", vecFileName);
	SetAnimationClipColorKey("LeftWallClimb", 255, 255, 255);

	// 오른쪽 벽타기
	AddAnimationClipAtlas("RightWallClimb", ANI_OPTION::LOOP, 1.f, 4, 14, 0.f, _SIZE(64.f, 64.f), "PlayerRightWallClimb", L"Player/Climb/RightWall/atlas.bmp");
	SetAnimationClipColorKey("RightWallClimb", 255, 255, 255);

	// 충돌체 추가 (Rect 타입)
	ColliderRect* pRC = AddCollider<ColliderRect>("PlayerBody");

	pRC->SetRect(-14, -5, 12, 32);
	pRC->AddCollisionFunction(COL_STATE::ENTER, this, &Player::StandOnGround);
	pRC->AddCollisionFunction(COL_STATE::STAY, this, &Player::StandOnGround);
	pRC->AddCollisionFunction(COL_STATE::LEAVE, this, &Player::OffGround);

	pRC->AddCollisionFunction(COL_STATE::ENTER, this, &Player::CollisionWithPlatform);
	pRC->AddCollisionFunction(COL_STATE::STAY, this, &Player::CollisionWithPlatform);
	pRC->AddCollisionFunction(COL_STATE::LEAVE, this, &Player::OffWall);

	pRC->AddCollisionFunction(COL_STATE::ENTER, this, &Player::CollisionWithNeedle);

	pRC->AddCollisionFunction(COL_STATE::ENTER, this, &Player::CollisionWithDashball);

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
			m_iDir = 1;
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
			m_iDir = -1;
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
		m_bWalking = true;
		if (!m_bJumping && m_bOnGround)
		{
			m_pAnimation->ChangeClip("WalkLeft");
			m_pAnimation->SetDefaultClip("LeftIdle");
		}
	}
	if (KEYUP("MoveLeft"))
		m_bWalking = false;

	if (KEYPRESS("MoveRight"))		// 오른쪽 방향키
	{
		m_tPos.x += 200 * fDeltaTime;
		m_iDir = 1;
		m_bWalking = true;
		if (!m_bJumping && m_bOnGround)
		{
			m_pAnimation->ChangeClip("WalkRight");
			m_pAnimation->SetDefaultClip("RightIdle");
		}
	}
	if (KEYUP("MoveRight"))
		m_bWalking = false;

	if (KEYDOWN("Jump") && m_bJumpEnable)			// C
	{
		m_tSpeed.y = -700.f;
		m_bJumpEnable = false;
		m_bJumping = true;
	}
	if (m_bJumping)
	{
		if (m_iDir == 1)
		{
			m_pAnimation->ChangeClip("JumpRight");
			m_pAnimation->SetDefaultClip("FallingRight");
		}

		if (m_iDir == -1)
		{
			m_pAnimation->ChangeClip("JumpLeft");
			m_pAnimation->SetDefaultClip("FallingLeft");
		}

		m_fJumpTime += fDeltaTime;
		if (m_fJumpTime > 0.6f)
		{
			m_bJumping = false;
			m_fJumpTime = 0.f;
		}
	}

	// 대각선 4방향 대시 (키입력 메커니즘 때문에 앞쪽에 코딩)
	if (KEYDOWN("DashUp") && KEYDOWN("DashRight") && m_bDashEnable)
	{
		m_bJumpEnable = false;
		m_bDashUpRight = true;
		m_bDashEnable = false;
	}
	if (m_bDashUpRight)
		DashUpRight(fDeltaTime);

	if (KEYDOWN("DashUp") && KEYDOWN("DashLeft") && m_bDashEnable)
	{
		m_bJumpEnable = false;
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
		m_bJumpEnable = false;
		m_bDashRight = true;
		m_bDashEnable = false;
	}
	if (m_bDashRight)
		DashRight(fDeltaTime);

	if (KEYDOWN("DashLeft") && m_bDashEnable)
	{
		m_bJumpEnable = false;
		m_bDashLeft = true;
		m_bDashEnable = false;
	}
	if (m_bDashLeft)
		DashLeft(fDeltaTime);

	if (KEYDOWN("DashUp") && m_bDashEnable)
	{
		m_bJumpEnable = false;
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
		if (m_iDir == -1 && m_bOnWall)
		{
			m_pAnimation->ChangeClip("RightWallClimb");
			m_pAnimation->SetDefaultClip("RightIdle");
		}

		else if(m_iDir == 1 && m_bOnWall)
		{
			m_pAnimation->ChangeClip("LeftWallClimb");
			m_pAnimation->SetDefaultClip("LeftIdle");
		}
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

	if (!m_bWalking && !m_bOnWall)
		m_pAnimation->ReturnClip();

	return 0;
}

int Player::LateUpdate(float fDeltaTime)
{
	Creature::LateUpdate(fDeltaTime);

	if (m_tPos.x < 0)
		m_tPos.x = 0;
	if (m_tPos.x > GETWORLDRES.iW)
		m_tPos.x = (float)GETWORLDRES.iW;

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
		m_tSpeed.y = -2000.f;
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
		m_tSpeed.x = 1400.f;
		m_tSpeed.y = -1400.f;
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
		m_tSpeed.x = -1400.f;
		m_tSpeed.y = -1400.f;
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

void Player::Die()
{
	if (m_pScene->GetSceneTag() == "Stage1")
		GET_SINGLE(SceneManager)->CreateScene<TestScene>(SCENE_TYPE::NEXT);
	else
		GET_SINGLE(SceneManager)->CreateScene<GameOverScene>(SCENE_TYPE::NEXT);
}

void Player::StandOnGround(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "GroundBody")
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

		RECT groundRect = ((ColliderRect*)pDest)->GetWorldInfo();

		int iInterW = tRC.right - tRC.left;
		int iInterH = tRC.bottom - tRC.top;

		if (iInterW >= iInterH)	// 위아래에서 충돌
		{

			m_tPos.y -= iInterH;
			m_tPos.y++;
			m_tSpeed.y = 0.f;

			m_bJumpEnable = true;
			m_bDashEnable = true;
			m_bOnGround = true;


			if (m_iDir == 1) m_pAnimation->SetDefaultClip("RightIdle");
			if (m_iDir == -1) m_pAnimation->SetDefaultClip("LeftIdle");

			if (m_bDashDown || m_bDashDownLeft || m_bDashDownRight)
			{
				m_bDashDown = false;
				m_bDashDownLeft = false;
				m_bDashDownRight = false;
				m_fDashTime = 0.f;
				m_tSpeed.x = 0.f;
			}
		}

		if (iInterW < iInterH)	// 좌우에서 충돌
		{
			m_tSpeed.x = 0.f;

			if (tRC.left == groundRect.left)	// 왼쪽에서 충돌
			{
				m_tPos.x -= iInterW;
				++m_tPos.x;
			}
			else if (tRC.right == groundRect.right)	// 오른쪽에서 충돌
			{
				m_tPos.x += iInterW;
				--m_tPos.x;
			}
		}
	}
}

void Player::OffGround(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
	if (pDest->GetObj()->GetTag() == "Ground")
	{
		m_bOnGround = false;
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
			m_bOnGround = true;

			if (m_iDir == 1) m_pAnimation->SetDefaultClip("RightIdle");
			if (m_iDir == -1) m_pAnimation->SetDefaultClip("LeftIdle");

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
		m_bOnGround = false;
		m_tAccel.y = 2000.f;
	}
}

void Player::CollisionWithNeedle(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "NeedleBody")
	{
		Die();
	}
}

void Player::CollisionWithDashball(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "DashballBody")
	{
		if(((Dashball*)pDest->GetObj())->GetEnable())
			m_bDashEnable = true;
	}
}

#include "Player.h"
#include "../Core/CInput.h"
#include "../Resources/Texture.h"
#include "../Animation/Animation.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Camera.h"

Player::Player()	:	// TODO: ������ ��� �ʱ�ȭ�ߴ��� Ȯ��!
	m_iDir(1),
	m_fDashTime(0.f), fWallJumpTime(0.f),
	m_bJumpEnable(true), m_bDashEnable(true), m_eStatus(PLAYER_STATUS::IDLE_RIGHT),
	m_bDashRight(false), m_bDashLeft(false), m_bDashUp(false), m_bDashDown(false),
	m_bDashUpRight(false), m_bDashUpLeft(false), m_bDashDownRight(false), m_bDashDownLeft(false),
	m_bWallCliff(false), m_bOnWall(false), m_bLeftWallJumpEnable(false), m_bRightWallJumpEnable(false),
	m_bLeftWallJumping(false), m_bRightWallJumping(false)
{
}

Player::Player(const Player& player)	:	// TODO: ������ ��� ����or�ʱ�ȭ �ƴ��� Ȯ��!
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
	SetSize(64.f, 64.f);
	SetSpeed(0.f, 0.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Player", L"Base_1.bmp");
	SetColorKey(255, 0, 255);

	Animation* pAni = CreateAnimation("PlayerAnimation");

	// �ִϸ��̼� �߰� (������ Ÿ��)
	// ������ �ȱ�
	vector<wstring> vecFileName;

	for (int i = 0; i < 12; i++)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Walk/Right/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClipFrame("WalkRight", ANI_OPTION::LOOP, 1.f, 12, 0.f, _SIZE(64.f, 64.f), "PlayerWalkRight", vecFileName);
	SetAnimationClipColorKey("WalkRight", 255, 255, 255);

	// ���� ��Ÿ��
	vecFileName.clear();

	for (int i = 0; i < 14; i++)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Climb/LeftWall/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClipFrame("LeftWallClimb", ANI_OPTION::LOOP, 1.f, 14, 0.f, _SIZE(64.f, 64.f), "PlayerLeftWallClimb", vecFileName);
	SetAnimationClipColorKey("LeftWallClimb", 255, 255, 255);


	// �浹ü �߰� (Rect Ÿ��)
	ColliderRect* pRC = AddCollider<ColliderRect>("PlayerBody");

	pRC->SetRect(-18, -5, 10, 32);
	// TODO: �浹�� �Ͼ�� ���� �Լ� �߰� �� AddCollisionFunction ȣ��
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

	// TODO: ������ �ϵ��ڵ� �� �� �Լ� ���� ���� ȣ��, ���� �ϵ��ڵ� ���� ������ ����
	// ������
	if (KEYDOWN("Jump") && m_eStatus == PLAYER_STATUS::ON_LEFTWALL)
	{
		m_tSpeed.y = -700.f;
		m_eStatus = PLAYER_STATUS::JUMP_LEFTWALL;
	}
	if (m_eStatus == PLAYER_STATUS::JUMP_LEFTWALL)
	{
		if (fWallJumpTime < 0.1f)
		{
			m_tPos.x -= 600.f * fDeltaTime;
			fWallJumpTime += fDeltaTime;
		}
		else
		{
			m_eStatus = PLAYER_STATUS::FALLING_LEFT;
			fWallJumpTime = 0.f;
		}
	}
	
	if (KEYDOWN("Jump") && m_eStatus == PLAYER_STATUS::ON_RIGHTWALL)
	{
		m_tSpeed.y = -700.f;
		m_eStatus = PLAYER_STATUS::JUMP_RIGHTWALL;
	}
	if (m_eStatus == PLAYER_STATUS::JUMP_RIGHTWALL)
	{
		if (fWallJumpTime < 0.1f)
		{
			m_tPos.x += 600.f * fDeltaTime;
			fWallJumpTime += fDeltaTime;
		}
		else
		{
			m_eStatus = PLAYER_STATUS::FALLING_RIGHT;
			fWallJumpTime = 0.f;
		}
	}
	
	// �⺻ ������
	if (KEYPRESS("MoveLeft"))		// ���� ����Ű
	{
		m_eStatus = PLAYER_STATUS::WALK_LEFT;
		m_tPos.x -= 200 * fDeltaTime;
		m_iDir = -1;
	}

	if (KEYPRESS("MoveRight"))		// ������ ����Ű
	{
		m_eStatus = PLAYER_STATUS::WALK_RIGHT;
		m_tPos.x += 200 * fDeltaTime;
		m_iDir = 1;
	}

	if (KEYDOWN("Jump") && m_bJumpEnable)			// C
	{
		if(m_iDir == -1)	m_eStatus = PLAYER_STATUS::JUMP_LEFT;
		if(m_iDir == 1)		m_eStatus = PLAYER_STATUS::JUMP_RIGHT;

		m_tSpeed.y = -700.f;
		m_bJumpEnable = false;
	}

	// �밢�� 4���� ��� (Ű�Է� ��Ŀ���� ������ ���ʿ� �ڵ�)
	if (KEYDOWN("DashUp") && KEYDOWN("DashRight") && m_bDashEnable)
	{
		m_eStatus = PLAYER_STATUS::DASH_UPRIGHT;
		m_bDashEnable = false;
	}
	if (m_eStatus == PLAYER_STATUS::DASH_UPRIGHT)
		DashUpRight(fDeltaTime);

	if (KEYDOWN("DashUp") && KEYDOWN("DashLeft") && m_bDashEnable)
	{
		m_eStatus = PLAYER_STATUS::DASH_UPLEFT;
		m_bDashEnable = false;
	}
	if (m_eStatus == PLAYER_STATUS::DASH_UPLEFT)
		DashUpLeft(fDeltaTime);

	if (KEYDOWN("DashDown") && KEYDOWN("DashRight") && m_bDashEnable)
	{
		m_eStatus = PLAYER_STATUS::DASH_DOWNRIGHT;
		m_bDashEnable = false;
	}
	if (m_eStatus == PLAYER_STATUS::DASH_DOWNRIGHT)
		DashDownRight(fDeltaTime);

	if (KEYDOWN("DashDown") && KEYDOWN("DashLeft") && m_bDashEnable)
	{
		m_eStatus = PLAYER_STATUS::DASH_DOWNLEFT;
		m_bDashEnable = false;
	}
	if (m_eStatus == PLAYER_STATUS::DASH_DOWNLEFT)
		DashDownLeft(fDeltaTime);

	// 4���� ���
	if (KEYDOWN("DashRight") && m_bDashEnable)
	{
		m_eStatus = PLAYER_STATUS::DASH_RIGHT;
		m_bDashEnable = false;
	}
	if (m_eStatus == PLAYER_STATUS::DASH_RIGHT)
		DashRight(fDeltaTime);

	if (KEYDOWN("DashLeft") && m_bDashEnable)
	{
		m_eStatus = PLAYER_STATUS::DASH_LEFT;
		m_bDashEnable = false;
	}
	if (m_eStatus == PLAYER_STATUS::DASH_LEFT)
		DashLeft(fDeltaTime);

	if (KEYDOWN("DashUp") && m_bDashEnable)
	{
		m_eStatus = PLAYER_STATUS::DASH_UP;
		m_bDashEnable = false;
	}
	if (m_eStatus == PLAYER_STATUS::DASH_UP)
		DashUp(fDeltaTime);

	if (KEYDOWN("DashDown") && m_bDashEnable)
	{
		m_eStatus = PLAYER_STATUS::DASH_DOWN;
		m_bDashEnable = false;
	}
	if (m_eStatus == PLAYER_STATUS::DASH_DOWN)
		DashDown(fDeltaTime);

	// �����
	if (KEYPRESS("WallCliff"))
	{
		m_bWallCliff = true;
		m_pAnimation->ChangeClip("LeftWallClimb");
		m_pAnimation->SetDefaultClip("WalkRight");
	}
	if (KEYUP("WallCliff"))
	{
		m_bWallCliff = false;
		m_tAccel.y = 2000.f;
	}

	if (KEYPRESS("WallCliffUp") && (m_eStatus == PLAYER_STATUS::ON_LEFTWALL || m_eStatus == PLAYER_STATUS::ON_RIGHTWALL))
	{
		m_tPos.y -= 200 * fDeltaTime;
	}
	if (KEYPRESS("WallCliffDown") && (m_eStatus == PLAYER_STATUS::ON_LEFTWALL || m_eStatus == PLAYER_STATUS::ON_RIGHTWALL))
	{
		m_tPos.y += 200 * fDeltaTime;
	}
}

int Player::Update(float fDeltaTime)
{
	Creature::Update(fDeltaTime);

	// ��� ���� ����
	if (m_fDashTime >= 0.1f)
	{
		EndDash();
	}

	if (!m_bOnWall)
		m_pAnimation->ReturnClip();

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

	// �÷��̾� ���� ���
	wchar_t strStatus[32] = {};
	wsprintf(strStatus, L"Status: %d", (int)m_eStatus);

	POSITION tPos;
	tPos.x = m_tPos.x - m_tSize.x * m_tPivot.x - GET_SINGLE(Camera)->GetPos().x;
	tPos.y = m_tPos.y - m_tSize.y * m_tPivot.y - GET_SINGLE(Camera)->GetPos().y;

	TextOut(hDC, (int)tPos.x, (int)tPos.y, strStatus, lstrlen(strStatus));

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

}
void Player::DashLeft(float fDeltaTime)
{
	if (m_fDashTime == 0.f)
	{
		m_tSpeed.x = -2000.f;
	}

	m_fDashTime += fDeltaTime;
	m_tSpeed.y = 0.f;
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

void Player::EndDash()
{
	if (m_iDir == -1)	m_eStatus = PLAYER_STATUS::FALLING_LEFT;
	if (m_iDir == 1)	m_eStatus = PLAYER_STATUS::FALLING_RIGHT;
	m_tSpeed.x = 0.f;
	m_fDashTime = 0.f;
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

		if(m_iDir == -1)	m_eStatus = PLAYER_STATUS::IDLE_LEFT;
		if(m_iDir == 1)		m_eStatus = PLAYER_STATUS::IDLE_RIGHT;

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

		if (iInterW > iInterH)	// (�÷��� ����) ���Ʒ����� �浹
		{
			m_tSpeed.y = 0.f;

			if (tRC.top == platformRect.top)	// ������ �浹
			{
				if (m_iDir == -1)	m_eStatus = PLAYER_STATUS::IDLE_LEFT;
				if (m_iDir == 1)		m_eStatus = PLAYER_STATUS::IDLE_RIGHT;

				m_bJumpEnable = true;
				m_bDashEnable = true;

				m_tPos.y -= iInterH;
			}
			else if (tRC.bottom == platformRect.bottom)	// �Ʒ����� �浹
			{
				m_tPos.y += iInterH;
			}
		}

		if (iInterW < iInterH)	// (�÷��� ����) �¿쿡�� �浹
		{
			m_tSpeed.x = 0.f;
			
			if (tRC.left == platformRect.left)	// ���ʿ��� �浹
			{
				m_eStatus = PLAYER_STATUS::ON_LEFTWALL;
				m_tPos.x -= iInterW;
				++m_tPos.x;
			}
			else if (tRC.right == platformRect.right)	// �����ʿ��� �浹
			{
				m_eStatus = PLAYER_STATUS::ON_RIGHTWALL;
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

		if (m_iDir == -1)		m_eStatus = PLAYER_STATUS::FALLING_LEFT;
		if (m_iDir == 1)		m_eStatus = PLAYER_STATUS::FALLING_RIGHT;

		m_bOnWall = false;
		m_tAccel.y = 2000.f;
	}
}

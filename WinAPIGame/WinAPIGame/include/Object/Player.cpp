#include "Player.h"
#include "../Core/CInput.h"
#include "../Resources/Texture.h"
#include "../Animation/Animation.h"
#include "../Collider/ColliderRect.h"

Player::Player()	:	// TODO: ������ ��� �ʱ�ȭ�ߴ��� Ȯ��!
	m_iDir(1),
	fDashTime(0.f),
	bJumpEnable(true),
	bDashEnable(true)
{
}

Player::Player(const Player& player)	:	// TODO: ������ ��� ����or�ʱ�ȭ �ƴ��� Ȯ��!
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

	// �ִϸ��̼� �߰� (������ Ÿ��)
	vector<wstring> vecFileName;

	for (int i = 0; i < 12; i++)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"PlayerWalk/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClipFrame("WalkRight", ANI_OPTION::LOOP, 1.f, 12, 0.f, _SIZE(32.f, 32.f), "PlayerWalkRight", vecFileName);
	SetAnimationClipColorKey("WalkRight", 255, 255, 255);


	// �浹ü �߰� (Rect Ÿ��)
	ColliderRect* pRC = AddCollider<ColliderRect>("PlayerBody");

	pRC->SetRect(-16, -16, 16, 16);
	// TODO: �浹�� �Ͼ�� ���� �Լ� �߰� �� AddCollisionFunction ȣ��
	pRC->AddCollisionFunction(COL_STATE::ENTER, this, &Player::StandOnGround);
	pRC->AddCollisionFunction(COL_STATE::STAY, this, &Player::StandOnGround);

	SAFE_RELEASE(pRC);

	return true;
}

void Player::Input(float fDeltaTime)
{
	Creature::Input(fDeltaTime);

	// TODO: ������ �ϵ��ڵ� �� �� �Լ� ���� ���� ȣ��, ���� �ϵ��ڵ� ���� ������ ����
	if (KEYPRESS("MoveLeft"))		// ���� ����Ű
	{
		m_tPos.x -= 200 * fDeltaTime;
		//m_tSpeed.x = -200;
		m_iDir = -1;
	}

	if (KEYUP("MoveLeft"))
	{
		//m_tSpeed.x += 200;
	}

	if (KEYPRESS("MoveRight"))		// ������ ����Ű
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

	if (KEYPRESS("DashRight") && bDashEnable)		// �� + X
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

	if (KEYPRESS("DashLeft") && bDashEnable)		// �� + X
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

	if (KEYPRESS("DashUp") && bDashEnable)		// �� + X
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

	if (KEYPRESS("DashDown") && bDashEnable)		// �� + X
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
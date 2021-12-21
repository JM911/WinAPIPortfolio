#include "PlayerLifeUI.h"
#include "Player.h"
#include "LifeIcon.h"

PlayerLifeUI::PlayerLifeUI()	:
	m_iPrevLife(0)
{
}

PlayerLifeUI::PlayerLifeUI(const PlayerLifeUI& ui)	:
	UIObj(ui)
{
	m_iPrevLife = ui.m_iPrevLife;
}

PlayerLifeUI::~PlayerLifeUI()
{
	Safe_Delete_VecList(m_vecLifeIcon);
}

bool PlayerLifeUI::Init()
{
	m_iPrevLife = Player::GetLife();
	SetPos(50, 50);
	SetSize(76, 30);
	SetTexture("LifeText", L"UI/LifeText.bmp");

	for (int i = 0; i < m_iPrevLife; i++)
	{
		LifeIcon* pLifeIcon = new LifeIcon;
		pLifeIcon->Init();
		pLifeIcon->SetPos(130 + 40 * i, 50);
		m_vecLifeIcon.push_back(pLifeIcon);
	}

	return true;
}

void PlayerLifeUI::Input(float fDeltaTime)
{
	UIObj::Input(fDeltaTime);
}

int PlayerLifeUI::Update(float fDeltaTime)
{
	UIObj::Update(fDeltaTime);

	if (m_iPrevLife != 0 && m_iPrevLife != Player::GetLife())
	{
		m_iPrevLife--;
		m_vecLifeIcon[m_iPrevLife]->SetEnable(false);

	}

	return 0;
}

int PlayerLifeUI::LateUpdate(float fDeltaTime)
{
	UIObj::LateUpdate(fDeltaTime);
	return 0;
}

void PlayerLifeUI::Collision(float fDeltaTime)
{
	UIObj::Collision(fDeltaTime);
}

void PlayerLifeUI::Render(HDC hDC, float fDeltaTime)
{
	UIObj::Render(hDC, fDeltaTime);

	vector<LifeIcon*>::iterator iter;
	vector<LifeIcon*>::iterator iterEnd = m_vecLifeIcon.end();

	for (iter = m_vecLifeIcon.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC, fDeltaTime);
	}
}

PlayerLifeUI* PlayerLifeUI::Clone()
{
	return new PlayerLifeUI(*this);
}

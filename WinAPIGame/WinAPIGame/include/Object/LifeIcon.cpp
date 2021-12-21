#include "LifeIcon.h"

LifeIcon::LifeIcon()	:
	m_bEnable(true)
{
}

LifeIcon::LifeIcon(const LifeIcon& ui)	:
	UIObj(ui)
{
	m_bEnable = ui.m_bEnable;
}

LifeIcon::~LifeIcon()
{
}

void LifeIcon::SetTextureByEnable()
{
	if (m_bEnable)
	{
		SetTexture("PlayerLifeIcon", L"UI/LifeIcon.bmp");
		SetColorKey(255, 255, 255);
	}
	else
	{
		SetTexture("BlankTex", L"UI/blank.bmp");
		SetColorKey(255, 255, 255);
	}
}

bool LifeIcon::Init()
{
	SetSize(30, 30);
	SetTexture("PlayerLifeIcon", L"UI/LifeIcon.bmp");
	SetColorKey(255, 255, 255);

	return true;
}

void LifeIcon::Input(float fDeltaTime)
{
	UIObj::Input(fDeltaTime);
}

int LifeIcon::Update(float fDeltaTime)
{
	UIObj::Update(fDeltaTime);
	return 0;
}

int LifeIcon::LateUpdate(float fDeltaTime)
{
	UIObj::LateUpdate(fDeltaTime);
	return 0;
}

void LifeIcon::Collision(float fDeltaTime)
{
	UIObj::Collision(fDeltaTime);
}

void LifeIcon::Render(HDC hDC, float fDeltaTime)
{
	UIObj::Render(hDC, fDeltaTime);
}

LifeIcon* LifeIcon::Clone()
{
	return new LifeIcon(*this);
}

#include "NumberUI.h"

NumberUI::NumberUI()	:
	m_iNum(0)
{
}

NumberUI::NumberUI(const NumberUI& ui)	:
	UIObj(ui)
{
	m_iNum = ui.m_iNum;
}

NumberUI::~NumberUI()
{
}

void NumberUI::SetTextureByNum()
{
	// TODO: wsprintf 등 이용해서 더 짧게 만들어 볼까..
	switch (m_iNum)
	{
	case 0:
		SetTexture("Num0", L"UI/Number/0.bmp");
		SetColorKey(255, 255, 255);
		break;
	case 1:
		SetTexture("Num1", L"UI/Number/1.bmp");
		SetColorKey(255, 255, 255);
		break;
	case 2:
		SetTexture("Num2", L"UI/Number/2.bmp");
		SetColorKey(255, 255, 255);
		break;
	case 3:
		SetTexture("Num3", L"UI/Number/3.bmp");
		SetColorKey(255, 255, 255);
		break;
	case 4:
		SetTexture("Num4", L"UI/Number/4.bmp");
		SetColorKey(255, 255, 255);
		break;
	case 5:
		SetTexture("Num5", L"UI/Number/5.bmp");
		SetColorKey(255, 255, 255);
		break;
	case 6:
		SetTexture("Num6", L"UI/Number/6.bmp");
		SetColorKey(255, 255, 255);
		break;
	case 7:
		SetTexture("Num7", L"UI/Number/7.bmp");
		SetColorKey(255, 255, 255);
		break;
	case 8:
		SetTexture("Num8", L"UI/Number/8.bmp");
		SetColorKey(255, 255, 255);
		break;
	case 9:
		SetTexture("Num9", L"UI/Number/9.bmp");
		SetColorKey(255, 255, 255);
		break;
	}
}

bool NumberUI::Init()
{
	SetSize(24, 30);
	SetTexture("Num0", L"UI/Number/0.bmp");
	SetColorKey(255, 255, 255);
	return true;
}

void NumberUI::Input(float fDeltaTime)
{
	UIObj::Input(fDeltaTime);
}

int NumberUI::Update(float fDeltaTime)
{
	UIObj::Update(fDeltaTime);
	return 0;
}

int NumberUI::LateUpdate(float fDeltaTime)
{
	UIObj::LateUpdate(fDeltaTime);
	return 0;
}

void NumberUI::Collision(float fDeltaTime)
{
	UIObj::Collision(fDeltaTime);
}

void NumberUI::Render(HDC hDC, float fDeltaTime)
{
	UIObj::Render(hDC, fDeltaTime);
}

NumberUI* NumberUI::Clone()
{
	return new NumberUI(*this);
}

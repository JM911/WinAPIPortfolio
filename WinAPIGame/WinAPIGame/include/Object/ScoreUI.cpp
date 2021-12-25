#include "ScoreUI.h"
#include "NumberUI.h"

int ScoreUI::m_iScore = 0;
int ScoreUI::m_iPrevScore = 0;

ScoreUI::ScoreUI()
{
}

ScoreUI::ScoreUI(const ScoreUI& ui)	:
	UIObj(ui)
{
}

ScoreUI::~ScoreUI()
{
	SAFE_RELEASE(m_pNum1);
	SAFE_RELEASE(m_pNum2);
}

bool ScoreUI::Init()
{
	SetPos(1000, 50);
	SetSize(113, 30);
	SetTexture("ScoreTex", L"UI/score.bmp");
	//SetColorKey(255, 255, 255);

	m_pNum1 = new NumberUI;
	m_pNum2 = new NumberUI;
	m_pNum1->Init();
	m_pNum2->Init();

	m_pNum1->SetPos(GetPos().x + 130, GetPos().y);
	m_pNum2->SetPos(GetPos().x + 160, GetPos().y);

	return true;
}

void ScoreUI::Input(float fDeltaTime)
{
	UIObj::Input(fDeltaTime);
}

int ScoreUI::Update(float fDeltaTime)
{
	UIObj::Update(fDeltaTime);

	m_pNum1->SetNum(m_iScore / 10);
	m_pNum2->SetNum(m_iScore % 10);

	m_pNum1->SetPos(GetPos().x + 130, GetPos().y);
	m_pNum2->SetPos(GetPos().x + 160, GetPos().y);

	return 0;
}

int ScoreUI::LateUpdate(float fDeltaTime)
{
	UIObj::LateUpdate(fDeltaTime);
	return 0;
}

void ScoreUI::Collision(float fDeltaTime)
{
	UIObj::Collision(fDeltaTime);
}

void ScoreUI::Render(HDC hDC, float fDeltaTime)
{
	UIObj::Render(hDC, fDeltaTime);
	m_pNum1->Render(hDC, fDeltaTime);
	m_pNum2->Render(hDC, fDeltaTime);
}

ScoreUI* ScoreUI::Clone()
{
	return new ScoreUI(*this);
}

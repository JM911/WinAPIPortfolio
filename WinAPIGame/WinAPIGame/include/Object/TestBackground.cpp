#include "TestBackground.h"
#include "../Core/Camera.h"
#include "../Core.h"
#include "../Resources/Texture.h"

TestBackground::TestBackground()
{
}

TestBackground::TestBackground(const TestBackground& test)	:
	StaticObj(test)
{
}

TestBackground::~TestBackground()
{
	SAFE_RELEASE(m_pTexture);
}

bool TestBackground::Init(POSITION tPos, _SIZE tSize, POSITION tPivot, const string& strBGName, const wchar_t* pBGFileName)
{
	SetPos(tPos);
	SetSize(tSize);
	SetPivot(tPivot);

	SetTexture(strBGName, pBGFileName, BACKGROUND_PATH);

	return true;
}

bool TestBackground::Init()
{
	return false;
}

void TestBackground::Input(float fDeltaTime)
{
	StaticObj::Input(fDeltaTime);
}

int TestBackground::Update(float fDeltaTime)
{
	StaticObj::Update(fDeltaTime);
	return 0;
}

int TestBackground::LateUpdate(float fDeltaTime)
{
	StaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void TestBackground::Collision(float fDeltaTime)
{
	StaticObj::Collision(fDeltaTime);
}

void TestBackground::Render(HDC hDC, float fDeltaTime)
{
	StaticObj::Render(hDC, fDeltaTime);		// FW에는 주석처리 되어있음. 일단 여기선 그냥 쓰자
	
	// TODO: 카메라 클래스 설계 후 작업
	if (m_pTexture)
	{
		POSITION tPos;
		tPos.x = m_tPos.x - m_tSize.x * m_tPivot.x;
		tPos.y = m_tPos.y - m_tSize.y * m_tPivot.y;

		POSITION tCamPos = GET_SINGLE(Camera)->GetPos();

		BitBlt(hDC, (int)tPos.x, (int)tPos.y, GETRESOLUTION.iW, GETRESOLUTION.iH, m_pTexture->GetDC(), (int)tCamPos.x, (int)tCamPos.y, SRCCOPY);
	}

}

TestBackground* TestBackground::Clone()
{
	return new TestBackground(*this);
}

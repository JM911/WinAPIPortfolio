#include "Obj.h"
#include "../Resources/Texture.h"
#include "../Resources/ResourcesManager.h"
#include "../Core/Camera.h"

Obj::Obj()
{
}

Obj::Obj(const Obj& obj)
{
	*this = obj;

	// TODO: 애니메이션 복사, 충돌체 복사
}

Obj::~Obj()
{
}

void Obj::SetTexture(Texture* pTexture)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTexture;

	if (pTexture)
		pTexture->AddRef();
}

void Obj::SetTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(ResourcesManager)->LoadTexture(strKey, pFileName, strPathKey);
}

void Obj::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_pTexture->SetColorKey(r, g, b);
}

void Obj::Input(float fDeltaTime)
{
}

int Obj::Update(float fDeltaTime)
{
	// TODO: 충돌체와 애니메이션 업데이트
	return 0;
}

int Obj::LateUpdate(float fDeltaTime)
{
	// TODO: 충돌체와 애니메이션 업데이트
	return 0;
}

void Obj::Collision(float fDeltaTime)
{
}

void Obj::Render(HDC hDC, float fDeltaTime)
{
	POSITION tPos;
	tPos.x = m_tPos.x - m_tSize.x * m_tPivot.x - GET_SINGLE(Camera)->GetPos().x;
	tPos.y = m_tPos.y - m_tSize.y * m_tPivot.y - GET_SINGLE(Camera)->GetPos().y;
	
	// TODO: 화면 밖으로 나가면 렌더하지 않도록 하는 설정 추가
	RESOLUTION tClientRS = GET_SINGLE(Camera)->GetClientRS();

	bool bInClient = true;

	if (tPos.x + m_tSize.x < 0)
		bInClient = false;
	else if (tPos.x > tClientRS.iW)
		bInClient = false;
	else if (tPos.y + m_tSize.y < 0)
		bInClient = false;
	else if (tPos.y > tClientRS.iH)
		bInClient = false;

	// TODO: 나중에 텍스쳐 설정하면 텍스쳐와 애니메이션을 그리도록 수정
	if (m_pTexture && bInClient)
	{
		POSITION tImagePos;

		tImagePos.x += m_tImageOffset.x;
		tImagePos.y += m_tImageOffset.y;

		if (m_pTexture->GetColorKeyEnable())		// 컬러키가 활성화되어 있다면
		{
			TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y, m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y, SRCCOPY);
		}
	}

}

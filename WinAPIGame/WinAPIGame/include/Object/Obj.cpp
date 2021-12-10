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

	// TODO: �ִϸ��̼� ����, �浹ü ����
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
	// TODO: �浹ü�� �ִϸ��̼� ������Ʈ
	return 0;
}

int Obj::LateUpdate(float fDeltaTime)
{
	// TODO: �浹ü�� �ִϸ��̼� ������Ʈ
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
	
	// TODO: ȭ�� ������ ������ �������� �ʵ��� �ϴ� ���� �߰�
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

	// TODO: ���߿� �ؽ��� �����ϸ� �ؽ��Ŀ� �ִϸ��̼��� �׸����� ����
	if (m_pTexture && bInClient)
	{
		POSITION tImagePos;

		tImagePos.x += m_tImageOffset.x;
		tImagePos.y += m_tImageOffset.y;

		if (m_pTexture->GetColorKeyEnable())		// �÷�Ű�� Ȱ��ȭ�Ǿ� �ִٸ�
		{
			TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y, m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(), tImagePos.x, tImagePos.y, SRCCOPY);
		}
	}

}

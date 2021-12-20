#include "Obj.h"
#include "../Resources/Texture.h"
#include "../Resources/ResourcesManager.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"

list<Obj*> Obj::m_ObjList;

Obj::Obj()	:
	m_pTexture(NULL),
	m_pAnimation(NULL)
{
}

Obj::Obj(const Obj& obj)
{
	*this = obj;

	if (obj.m_pAnimation)
		m_pAnimation = obj.m_pAnimation->Clone();

	if (m_pTexture)
		m_pTexture->AddRef();
	
	// TODO: 충돌체 복사
}

Obj::~Obj()
{
	SAFE_RELEASE(m_pTexture);
	Safe_Release_VecList(m_ColliderList);
	SAFE_RELEASE(m_pAnimation);
}

void Obj::AddObj(Obj* pObj)
{
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

Obj* Obj::FindObject(const string& strTag)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();			// 여기서 해야 하나?
			return *iter;
		}
	}

	return NULL;
}

void Obj::EraseObj(Obj* pObj)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if (*iter == pObj)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void Obj::EraseObj(const string& strTag)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void Obj::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
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

Animation* Obj::CreateAnimation(const string& strTag)
{
	SAFE_RELEASE(m_pAnimation);

	m_pAnimation = new Animation;

	m_pAnimation->SetTag(strTag);
	m_pAnimation->SetObj(this);

	if (!m_pAnimation->Init())
	{
		SAFE_RELEASE(m_pAnimation);
		return NULL;
	}

	//m_pAnimation->AddRef();

	return m_pAnimation;
}

bool Obj::AddAnimationClipAtlas(const string& strName, ANI_OPTION eOption, float fAnimationLimitTime, 
	int iMaxFrameX, int iTotalFrame, float fOptionLimitTime, _SIZE tFrameSize, 
	const string& strTexKey, const wchar_t* pFileName, const string& strPathKey)
{
	if (!m_pAnimation)
		return false;

	m_pAnimation->AddClipAtlas(strName, eOption, fAnimationLimitTime, iMaxFrameX, iTotalFrame, fOptionLimitTime, tFrameSize,
		strTexKey, pFileName, strPathKey);

	return true;
}

bool Obj::AddAnimationClipFrame(const string& strName, ANI_OPTION eOption, float fAnimationLimitTime, 
	int iMaxFrame, float fOptionLimitTime, _SIZE tFrameSize, 
	const string& strTexKey, const vector<wstring>& vecFileName, const string& strPathKey)
{
	if (!m_pAnimation)
		return false;

	m_pAnimation->AddClipFrame(strName, eOption, fAnimationLimitTime, iMaxFrame, fOptionLimitTime, tFrameSize,
		strTexKey, vecFileName, strPathKey);

	return true;
}

void Obj::SetAnimationClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b)
{
	if (m_pAnimation)
		m_pAnimation->SetClipColorKey(strClip, r, g, b);
}

Collider* Obj::GetCollider(const string& strTag)
{
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			// (*iter)->AddRef();
			return (*iter);
		}
	}

	return NULL;
}

void Obj::EraseCollider(const string& strTag)
{
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			SAFE_DELETE((*iter));
			m_ColliderList.erase(iter);
			return;
		}
	}
}

void Obj::Input(float fDeltaTime)
{
}

int Obj::Update(float fDeltaTime)
{
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object에 Enable 변수 추가하면 반영

		(*iter)->Update(fDeltaTime);

		// TODO: Object에 Life 변수 추가하면 반영
	}

	if (m_pAnimation)
		m_pAnimation->Update(fDeltaTime);

	return 0;
}

int Obj::LateUpdate(float fDeltaTime)
{
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object에 Enable 변수 추가하면 반영

		(*iter)->LateUpdate(fDeltaTime);

		// TODO: Object에 Life 변수 추가하면 반영
	}

	return 0;
}

void Obj::Collision(float fDeltaTime)
{
}

void Obj::Render(HDC hDC, float fDeltaTime)
{
	if (m_pLayer && m_pLayer->GetTag() == "UI")
		return;

	POSITION tPos;
	tPos.x = m_tPos.x - m_tSize.x * m_tPivot.x - GET_SINGLE(Camera)->GetPos().x;
	tPos.y = m_tPos.y - m_tSize.y * m_tPivot.y - GET_SINGLE(Camera)->GetPos().y;
	
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

	// 텍스쳐 및 애니메이션 출력
	if (m_pTexture && bInClient)
	{
		POSITION tImagePos;

		if (m_pAnimation)
		{
			PANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();

			if (pClip->eType == ANI_TYPE::ATLAS)
			{
				tImagePos.x = pClip->iCurFrameX * pClip->tFrameSize.x + (pClip->iCurFrameX - 1) * pClip->tFrameInterval.x;
				tImagePos.y = pClip->iCurFrameY * pClip->tFrameSize.y + (pClip->iCurFrameY - 1) * pClip->tFrameInterval.y;
			}
		}

		tImagePos.x += m_tImageOffset.x;
		tImagePos.y += m_tImageOffset.y;

		if (m_pTexture->GetColorKeyEnable())		// 컬러키가 활성화되어 있다면
		{
			TransparentBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_tSize.x, (int)m_tSize.y, m_pTexture->GetDC(),
				(int)tImagePos.x, (int)tImagePos.y, (int)m_tSize.x, (int)m_tSize.y, m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_tSize.x, (int)m_tSize.y, m_pTexture->GetDC(), (int)tImagePos.x, (int)tImagePos.y, SRCCOPY);
		}
	}

	// 충돌체 출력
	if (bInClient)
	{
		list<Collider*>::iterator iter;
		list<Collider*>::iterator iterEnd = m_ColliderList.end();

		for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
		{
			// TODO: Object에 Enable 변수 추가하면 반영
			
			(*iter)->Render(hDC, fDeltaTime);

			// TODO: Object에 Life 변수 추가하면 반영
		}
	}

}

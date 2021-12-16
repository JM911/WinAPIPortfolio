#include "Animation.h"
#include "../Resources/Texture.h"
#include "../Object/Obj.h"
#include "../Resources/ResourcesManager.h"

Animation::Animation()	:
	m_pCurClip(NULL),
	m_bMotionEnd(false)
{
}

Animation::Animation(const Animation& anim)
{
	*this = anim;

	m_bMotionEnd = false;
	m_mapClip.clear();

	unordered_map<string, PANIMATIONCLIP>::const_iterator iter;
	unordered_map<string, PANIMATIONCLIP>::const_iterator iterEnd = m_mapClip.end();

	for (iter = m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		PANIMATIONCLIP pClip = new ANIMATIONCLIP;

		*pClip = *iter->second;

		for (size_t i = 0; i < pClip->vecTexture.size(); ++i)
		{
			pClip->vecTexture[i]->AddRef();
		}
	}

	m_pCurClip = NULL;

	m_strCurClip = "";
	SetCurrentClip(anim.m_strCurClip);
}

Animation::~Animation()
{
	unordered_map<string, PANIMATIONCLIP>::iterator iter;
	unordered_map<string, PANIMATIONCLIP>::iterator iterEnd = m_mapClip.end();

	for (iter = m_mapClip.begin(); iter != iterEnd; ++iter)
	{
		for (size_t i = 0; i < iter->second->vecTexture.size(); ++i)
		{
			SAFE_RELEASE(iter->second->vecTexture[i]);
		}

		SAFE_DELETE(iter->second);
	}

	m_mapClip.clear();
}

void Animation::SetClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b)
{
	PANIMATIONCLIP pClip = FindClip(strClip);

	if (!pClip)
		return;

	for (size_t i = 0; i < pClip->vecTexture.size(); ++i)
	{
		pClip->vecTexture[i]->SetColorKey(r, g, b);
	}
}

void Animation::SetCurrentClip(const string& strCurClip)
{
	ChangeClip(strCurClip);		// 이렇게 할거면 굳이 이 함수 존재 이유가 있을까?
}

void Animation::SetDefaultClip(const string& strDefaultClip)
{
	m_strDefaultClip = strDefaultClip;
}

void Animation::ChangeClip(const string& strClip)
{
	if (m_strCurClip == strClip)
		return;

	m_strCurClip = strClip;

	if (m_pCurClip)
	{
		m_pCurClip->iCurFrameX = 0;
		m_pCurClip->iCurFrameY = 0;
		m_pCurClip->fAnimationTime = 0.f;
		m_pCurClip->fOptionTime = 0.f;
	}

	m_pCurClip = FindClip(strClip);

	if (m_pCurClip->eType == ANI_TYPE::ATLAS)
		m_pObj->SetTexture(m_pCurClip->vecTexture[0]);		// 만약 타입별로 ANIMATIONCLIP 구조체를 따로 정의한다면 수정

	else if (m_pCurClip->eType == ANI_TYPE::FRAME)
		m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iCurFrameX + m_pCurClip->iMaxFrameX * m_pCurClip->iCurFrameY]);
}

void Animation::ReturnClip()
{
	ChangeClip(m_strDefaultClip);
}

PANIMATIONCLIP Animation::FindClip(const string& strName)
{
	unordered_map<string, PANIMATIONCLIP>::iterator iter = m_mapClip.find(strName);

	if (iter == m_mapClip.end())
		return NULL;

	return iter->second;
}

bool Animation::AddClipAtlas(const string& strName, ANI_OPTION eOption, 
	float fAnimationLimitTime, int iMaxFrameX, int iTotalFrame, float fOptionLimitTime, _SIZE tFrameSize,
	const string& strTexKey, const wchar_t* pFileName, const string& strPathKey)
{
	PANIMATIONCLIP pClip = new ANIMATIONCLIP;

	pClip->eType = ANI_TYPE::ATLAS;
	pClip->eOption = eOption;
	pClip->fAnimationLimitTime = fAnimationLimitTime;
	pClip->iMaxFrameX = iMaxFrameX;
	pClip->iMaxFrameY = (iTotalFrame - 1) / iMaxFrameX + 1;
	pClip->iTotalFrame = iTotalFrame;
	pClip->fOptionLimitTime = fOptionLimitTime;
	pClip->fAnimationFrameTime = fAnimationLimitTime / iTotalFrame;
	pClip->tFrameSize = tFrameSize;

	Texture* pTex = GET_SINGLE(ResourcesManager)->LoadTexture(strTexKey, pFileName, strPathKey);

	pClip->tFrameInterval = _SIZE(0.f, 0.f);

	if(pClip->iMaxFrameX > 1)
		pClip->tFrameInterval.x = (pTex->GetWidth() - (pClip->tFrameSize.x * (float)pClip->iMaxFrameX)) / (float)(pClip->iMaxFrameX - 1);
	if(pClip->iMaxFrameY > 1)
		pClip->tFrameInterval.y = (pTex->GetHeight() - (pClip->tFrameSize.y * (float)pClip->iMaxFrameY)) / (float)(pClip->iMaxFrameY - 1);

	pClip->vecTexture.push_back(pTex);

	pClip->fAnimationTime = 0.f;
	pClip->iCurFrameX = 0;
	pClip->iCurFrameY = 0;
	pClip->fOptionTime = 0.f;

	m_mapClip.insert(make_pair(strName, pClip));

	if (m_strCurClip.empty())
		SetCurrentClip(strName);

	if (m_strDefaultClip.empty())
		SetDefaultClip(strName);

	return true;
}

bool Animation::AddClipFrame(const string& strName, ANI_OPTION eOption, 
	float fAnimationLimitTime, int iMaxFrame, float fOptionLimitTime, _SIZE tFrameSize,
	const string& strTexKey, const vector<wstring>& vecFileName, const string& strPathKey)
{
	PANIMATIONCLIP pClip = new ANIMATIONCLIP;
	
	pClip->eType = ANI_TYPE::FRAME;
	pClip->eOption = eOption;
	pClip->fAnimationLimitTime = fAnimationLimitTime;
	pClip->iMaxFrameX = iMaxFrame;
	pClip->iMaxFrameY = 1;
	pClip->fOptionLimitTime = fOptionLimitTime;
	pClip->fAnimationFrameTime = fAnimationLimitTime / iMaxFrame;
	pClip->tFrameSize = tFrameSize;

	for (size_t i = 0; i < vecFileName.size(); ++i)
	{
		char strKey[256] = {};
		sprintf_s(strKey, "%s%d", strTexKey.c_str(), i);
		Texture* pTex = GET_SINGLE(ResourcesManager)->LoadTexture(strKey, vecFileName[i].c_str(), strPathKey);

		pClip->vecTexture.push_back(pTex);
	}

	pClip->fAnimationTime = 0.f;
	pClip->iCurFrameX = 0;
	pClip->iCurFrameY = 0;
	pClip->fOptionTime = 0.f;

	m_mapClip.insert(make_pair(strName, pClip));

	if (m_strCurClip.empty())
		SetCurrentClip(strName);

	if (m_strDefaultClip.empty())
		SetDefaultClip(strName);

	return true;
}

bool Animation::Init()
{
	return true;
}

void Animation::Update(float fDeltaTime)
{
	m_bMotionEnd = false;

	m_pCurClip->fAnimationTime += fDeltaTime;

	// 혹시라도 렉이 생기는 등의 이유로 DeltaTime이 클 경우 애니메이션 프레임을 건너뛸 수 있도록 설계
	while (m_pCurClip->fAnimationTime >= m_pCurClip->fAnimationFrameTime)
	{
		m_pCurClip->fAnimationTime -= m_pCurClip->fAnimationFrameTime;

		// 프레임 형식이면 매번 텍스쳐를 교체해줘야 한다.
		if (m_pCurClip->eType == ANI_TYPE::FRAME && m_pCurClip->iCurFrameX != m_pCurClip->iMaxFrameX)
			m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iCurFrameX]);

		++m_pCurClip->iCurFrameX;

		if (m_pCurClip->iCurFrameX == m_pCurClip->iMaxFrameX)
		{
			m_pCurClip->iCurFrameX = 0;
			++m_pCurClip->iCurFrameY;
		}

		if (m_pCurClip->iCurFrameX + m_pCurClip->iMaxFrameX * m_pCurClip->iCurFrameY == m_pCurClip->iTotalFrame)	// 애니메이션이 한바퀴 다 돌았다는 것 => 옵션 체크
		{
			m_pCurClip->iCurFrameY = 0;
			m_bMotionEnd = true;

			switch (m_pCurClip->eOption)
			{
			case ANI_OPTION::ONCE_RETURN:
				ReturnClip();	// 기본 모션으로 돌아가야 함.
				break;
			case ANI_OPTION::ONCE_DESTROY:
				// TODO: 오브젝트 삭제(Die) 함수 추가 후 작업.
				break;
			case ANI_OPTION::TIME_RETURN:
				break;
			case ANI_OPTION::TIME_DESTROY:
				break;
			}
		}
		else
		{
			if (m_pCurClip->eType == ANI_TYPE::FRAME)
				m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iCurFrameX]);
		}
	}
}

Animation* Animation::Clone()
{
	return new Animation(*this);
}

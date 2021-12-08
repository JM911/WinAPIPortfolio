#include "ResourcesManager.h"
#include "Texture.h"

DEFINITION_SINGLE(ResourcesManager)

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
	SAFE_RELEASE(m_pBackBuffer);
	Safe_Release_Map(m_mapTexture);
}

Texture* ResourcesManager::GetBackBuffer() const
{
	m_pBackBuffer->AddRef();
	return m_pBackBuffer;
}

bool ResourcesManager::Init(HINSTANCE hInst, HDC hDC)
{
	m_hInst = hInst;
	m_hDC = hDC;

	// 백버퍼를 불러온다.
	m_pBackBuffer = LoadTexture("BackBuffer", L"BackBuffer.bmp");

	return true;
}

Texture* ResourcesManager::LoadTexture(const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	Texture* pTexture = FindTexture(strKey);

	if (pTexture)
		return pTexture;

	pTexture = new Texture;

	if (!pTexture->LoadTexture(m_hInst, m_hDC, strKey, pFileName, strPathKey))		// 경로에 텍스쳐가 없으면 예외처리
	{
		SAFE_RELEASE(pTexture);
		return NULL;
	}

	pTexture->AddRef();
	m_mapTexture.insert(make_pair(strKey, pTexture));

	return pTexture;
}

Texture* ResourcesManager::FindTexture(const string& strKey)
{
	unordered_map<string, Texture*>::iterator iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
		return NULL;

	iter->second->AddRef();		// 텍스쳐 공유를 위해

	return iter->second;
}

#include "SoundManager.h"
#include "../Core/PathManager.h"

DEFINITION_SINGLE(SoundManager)

SoundManager::SoundManager()	:
	m_pSystem(NULL)
{
}

SoundManager::~SoundManager()
{
	unordered_map<string, PSOUNDINFO>::iterator iter;
	unordered_map<string, PSOUNDINFO>::iterator iterEnd = m_mapSound.end();

	for (iter = m_mapSound.begin(); iter != iterEnd; ++iter)
	{
		iter->second->pSound->release();
		SAFE_DELETE(iter->second);
	}

	m_pSystem->close();
	m_pSystem->release();
}

bool SoundManager::Init()
{
	System_Create(&m_pSystem);

	m_pSystem->init(10, FMOD_INIT_NORMAL, NULL);

	return true;
}

bool SoundManager::LoadSound(const string& strKey, bool bLoop, const char* pFileName, const string& strPathKey)
{
	if (FindSound(strKey))
		return true;

	const char* pPath = GET_SINGLE(PathManager)->FindPathByMultiByte(strPathKey);
	string strFullPath;

	if (pPath)
		strFullPath = pPath;

	strFullPath += pFileName;

	FMOD_MODE eMode = FMOD_LOOP_NORMAL;

	if (!bLoop)
		eMode = FMOD_DEFAULT;

	PSOUNDINFO pSoundInfo = new SOUNDINFO;

	pSoundInfo->bLoop = bLoop;
	m_pSystem->createSound(strFullPath.c_str(), eMode, NULL, &pSoundInfo->pSound);

	m_mapSound.insert(make_pair(strKey, pSoundInfo));

	return true;
}

bool SoundManager::Play(const string& strKey)
{
	PSOUNDINFO pSound = FindSound(strKey);

	if (!pSound)
		return false;

	m_pSystem->update();

	SOUND_TYPE eType = SOUND_TYPE::BGM;

	if (!pSound->bLoop)
		eType = SOUND_TYPE::EFFECT;

	m_pSystem->playSound(pSound->pSound, NULL, false, &m_pChannel[(unsigned int)eType]);

	return true;
}

void SoundManager::Stop(SOUND_TYPE eType)
{
	m_pChannel[(unsigned int)eType]->stop();
}

void SoundManager::Volume(SOUND_TYPE eType, float fVolume)
{
	m_pChannel[(unsigned int)eType]->setVolume(fVolume);
}

PSOUNDINFO SoundManager::FindSound(const string& strKey)
{
	unordered_map<string, PSOUNDINFO>::iterator iter = m_mapSound.find(strKey);

	if (iter == m_mapSound.end())
		return NULL;

	return iter->second;
}
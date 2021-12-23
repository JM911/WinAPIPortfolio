#pragma once

#include "../Game.h"
#include "fmod.hpp"

using namespace FMOD;

#pragma comment(lib, "fmod_vc")

typedef struct _tagSoundInfo
{
	Sound*	pSound;
	bool	bLoop;
}SOUNDINFO, *PSOUNDINFO;

class SoundManager
{
private:
	SoundManager();
	~SoundManager();

private:
	System* m_pSystem;
	Channel* m_pChannel[(unsigned int)SOUND_TYPE::END];
	unordered_map<string, PSOUNDINFO>	m_mapSound;
	
public:
	bool Init();
	bool LoadSound(const string& strKey, bool bLoop, const char* pFileName, const string& strPathKey = SOUND_PATH);
	bool Play(const string& strKey);
	void Stop(SOUND_TYPE eType);
	void Volume(SOUND_TYPE eType, float fVolume);

	PSOUNDINFO FindSound(const string& strKey);

	void ClearMap();		// 게임 재시작 기능 만들 때 호출
	
	DECLARE_SINGLE(SoundManager);
};


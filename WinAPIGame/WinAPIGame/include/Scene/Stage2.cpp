#include "Stage2.h"
#include "../Sound/SoundManager.h"
#include "../Object/Player.h"
#include "../Object/Ground.h"
#include "../Object/TestBackground.h"
#include "../Core/Camera.h"
#include "../Object/Needle.h"
#include "../Object/ScoreUI.h"
#include "../Object/PlayerLifeUI.h"

Stage2::Stage2()
{
}

Stage2::~Stage2()
{
}

bool Stage2::Init()
{
	if (!Scene::Init())		// 부모 Scene 클래스의 초기화 함수 호출
		return false;

	SetSceneTag("Stage2");

	// 사운드
	if (!GET_SINGLE(SoundManager)->FindSound("Stage2BGM"))
	{
		GET_SINGLE(SoundManager)->Stop(SOUND_TYPE::BGM);
		GET_SINGLE(SoundManager)->LoadSound("Stage2BGM", true, "Stage2.ogg");
		GET_SINGLE(SoundManager)->Play("Stage2BGM");
		GET_SINGLE(SoundManager)->Volume(SOUND_TYPE::BGM, 0.3f);
	}

	// 플레이어
	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);


	// 땅
	Ground* pGround = Obj::CreateObj<Ground>("Ground1", pLayer);
	pGround->SetGroundInfo(-100.f, 4000.f, 90);
	SAFE_RELEASE(pGround);



	// 바닥 사망 판정
	Needle* pNeedle = Obj::CreateObj<Needle>("BottomNeedle", pLayer);
	pNeedle->Init(POSITION(0.f, 800.f), 150, 1);
	SAFE_RELEASE(pNeedle);

	// 배경
	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("Stage2BG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(3840, 720), POSITION(0.f, 0.f), "Stage2BG", L"Stage2.bmp");
	SAFE_RELEASE(pBackground);

	// 점수 UI
	pLayer = FindLayer("UI");
	ScoreUI* pScore = Obj::CreateObj<ScoreUI>("ScoreUI", pLayer);
	SAFE_RELEASE(pScore);

	// 목숨 UI
	PlayerLifeUI* pLifeUI = Obj::CreateObj<PlayerLifeUI>("LifeUI", pLayer);
	SAFE_RELEASE(pLifeUI);

	return true;
}

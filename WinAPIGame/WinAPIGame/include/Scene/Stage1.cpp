#include "Stage1.h"
#include "Layer.h"
#include "../Object/Player.h"
#include "../Core/Camera.h"
#include "../Object/TestBackground.h"
#include "../Object/Ground.h"
#include "../Object/TilePlatform.h"
#include "../Sound/SoundManager.h"
#include "../Object/ScoreUI.h"
#include "../Object/PlayerLifeUI.h"
#include "../Object/Needle.h"
#include "../Object/StageClearObj.h"
#include "../Object/Strawberry.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

bool Stage1::Init()
{
	if (!Scene::Init())		// 부모 Scene 클래스의 초기화 함수 호출
		return false;

	SetSceneTag("Stage1");

	// 사운드
	if (!GET_SINGLE(SoundManager)->FindSound("Stage1BGM"))
	{
		GET_SINGLE(SoundManager)->Stop(SOUND_TYPE::BGM);
		GET_SINGLE(SoundManager)->LoadSound("Stage1BGM", true, "Stage1.ogg");
		GET_SINGLE(SoundManager)->Play("Stage1BGM");
		GET_SINGLE(SoundManager)->Volume(SOUND_TYPE::BGM, 0.3f);
	}

	// 플레이어
	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);


	// 땅
	Ground* pGround = Obj::CreateObj<Ground>("Ground1", pLayer);
	pGround->SetGroundInfo(-100.f, 1000.f, 90);
	SAFE_RELEASE(pGround);

	pGround = Obj::CreateObj<Ground>("Ground2", pLayer);
	pGround->SetGroundInfo(1100.f, 1600.f, 90);
	SAFE_RELEASE(pGround);

	pGround = Obj::CreateObj<Ground>("Ground3", pLayer);
	pGround->SetGroundInfo(2300.f, 2700.f, 90);
	SAFE_RELEASE(pGround);

	pGround = Obj::CreateObj<Ground>("Ground4", pLayer);
	pGround->SetGroundInfo(3000.f, 4000.f, 90);
	SAFE_RELEASE(pGround);

	// 딸기
	Strawberry* pStrawberry = Obj::CreateObj<Strawberry>("Strawberry1", pLayer);
	pStrawberry->SetPos(3300.f, 600.f);
	SAFE_RELEASE(pStrawberry);

	pStrawberry = Obj::CreateObj<Strawberry>("Strawberry2", pLayer);
	pStrawberry->SetPos(3400.f, 600.f);
	SAFE_RELEASE(pStrawberry);

	pStrawberry = Obj::CreateObj<Strawberry>("Strawberry3", pLayer);
	pStrawberry->SetPos(3500.f, 600.f);
	SAFE_RELEASE(pStrawberry);


	// 스테이지 클리어
	StageClearObj* pStageClear = Obj::CreateObj<StageClearObj>("StageClear", pLayer);
	SAFE_RELEASE(pStageClear);

	/*** 플랫폼 ***/
	// 점프 튜토리얼1
	TilePlatform* pTilePlatform = Obj::CreateObj<TilePlatform>("Platform1", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(600.f, 600.f), 2, 1);
	SAFE_RELEASE(pTilePlatform);

	// 점프 튜토리얼2
	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform2", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(1550.f, 550.f), 5, 1);
	SAFE_RELEASE(pTilePlatform);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform3", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(1750.f, 450.f), 5, 1);
	SAFE_RELEASE(pTilePlatform);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform4", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(1950.f, 350.f), 5, 1);
	SAFE_RELEASE(pTilePlatform);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform5", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(2150.f, 250.f), 5, 1);
	SAFE_RELEASE(pTilePlatform);





	// 바닥 사망 판정
	Needle* pNeedle = Obj::CreateObj<Needle>("BottomNeedle", pLayer);
	pNeedle->Init(POSITION(0.f, 800.f), 150, 1);
	SAFE_RELEASE(pNeedle);

	// 배경
	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("Stage1BG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(3840, 720), POSITION(0.f, 0.f), "Stage1BG", L"Stage1_2.bmp");
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

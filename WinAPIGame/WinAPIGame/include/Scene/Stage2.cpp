#include "Stage2.h"
#include "../Sound/SoundManager.h"
#include "../Object/Player.h"
#include "../Object/Ground.h"
#include "../Object/TestBackground.h"
#include "../Core/Camera.h"
#include "../Object/Needle.h"
#include "../Object/ScoreUI.h"
#include "../Object/PlayerLifeUI.h"
#include "../Object/StageClearObj.h"
#include "../Object/Strawberry.h"

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
		GET_SINGLE(SoundManager)->Volume(SOUND_TYPE::BGM, 0.15f);
	}

	// 플레이어
	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);


	// 땅
	Ground* pGround = Obj::CreateObj<Ground>("Ground1", pLayer);
	pGround->SetGroundInfo(-100, 1900, 90);
	SAFE_RELEASE(pGround);

	pGround = Obj::CreateObj<Ground>("Ground2", pLayer);
	pGround->SetGroundInfo(2700, 4000, 90);
	SAFE_RELEASE(pGround);



	/*** 플랫폼 ***/
	// 벽타기 튜토리얼
	TilePlatform* pTilePlatform = Obj::CreateObj<TilePlatform>("Platform1", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(300, 120), 3, 16);
	SAFE_RELEASE(pTilePlatform);


	// 벽점프 튜토리얼
	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform2", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(600, 0), 3, 16);
	SAFE_RELEASE(pTilePlatform);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform3", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(800, 120), 3, 16);
	SAFE_RELEASE(pTilePlatform);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform4", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(1000, 0), 3, 16);
	SAFE_RELEASE(pTilePlatform);


	// 가시 튜토리얼
	Needle* pNeedle = Obj::CreateObj<Needle>("Needle1", pLayer);
	pNeedle->SetTileTexture("SpikeUp", L"Platform/Tiles/Spike_Up.bmp");
	pNeedle->Init(POSITION(1200, 600), 2, 1);
	SAFE_RELEASE(pNeedle);

	pNeedle = Obj::CreateObj<Needle>("Needle2", pLayer);
	pNeedle->SetTileTexture("SpikeUp", L"Platform/Tiles/Spike_Up.bmp");
	pNeedle->Init(POSITION(1400, 600), 5, 1);
	SAFE_RELEASE(pNeedle);


	// for fun1
	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform5", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(1800, 530), 5, 1);
	SAFE_RELEASE(pTilePlatform);

	pNeedle = Obj::CreateObj<Needle>("Needle3_1", pLayer);
	pNeedle->SetTileTexture("SpikeUp", L"Platform/Tiles/Spike_Up.bmp");
	pNeedle->Init(POSITION(1860, 500), 1, 1);
	SAFE_RELEASE(pNeedle);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform6", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(2000, 430), 5, 1);
	SAFE_RELEASE(pTilePlatform);

	pNeedle = Obj::CreateObj<Needle>("Needle3_2", pLayer);
	pNeedle->SetTileTexture("SpikeUp", L"Platform/Tiles/Spike_Up.bmp");
	pNeedle->Init(POSITION(2060, 400), 1, 1);
	SAFE_RELEASE(pNeedle);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform7", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(2200, 330), 5, 1);
	SAFE_RELEASE(pTilePlatform);

	pNeedle = Obj::CreateObj<Needle>("Needle3_3", pLayer);
	pNeedle->SetTileTexture("SpikeUp", L"Platform/Tiles/Spike_Up.bmp");
	pNeedle->Init(POSITION(2260, 300), 1, 1);
	SAFE_RELEASE(pNeedle);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform8", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(2400, 430), 5, 1);
	SAFE_RELEASE(pTilePlatform);

	pNeedle = Obj::CreateObj<Needle>("Needle3_4", pLayer);
	pNeedle->SetTileTexture("SpikeUp", L"Platform/Tiles/Spike_Up.bmp");
	pNeedle->Init(POSITION(2460, 400), 1, 1);
	SAFE_RELEASE(pNeedle);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform9", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(2600, 530), 5, 1);
	SAFE_RELEASE(pTilePlatform);

	pNeedle = Obj::CreateObj<Needle>("Needle3_5", pLayer);
	pNeedle->SetTileTexture("SpikeUp", L"Platform/Tiles/Spike_Up.bmp");
	pNeedle->Init(POSITION(2660, 500), 1, 1);
	SAFE_RELEASE(pNeedle);


	// for fun2
	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform10", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(2900, 0), 2, 16);
	SAFE_RELEASE(pTilePlatform);

	pNeedle = Obj::CreateObj<Needle>("Needle4_1", pLayer);
	pNeedle->SetTileTexture("SpikeRight", L"Platform/Tiles/Spike_Right.bmp");
	pNeedle->Init(POSITION(2960, 240), 1, 8);
	SAFE_RELEASE(pNeedle);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform11", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(3150, 120), 2, 16);
	SAFE_RELEASE(pTilePlatform);

	pNeedle = Obj::CreateObj<Needle>("Needle4_2", pLayer);
	pNeedle->SetTileTexture("SpikeUp", L"Platform/Tiles/Spike_Up.bmp");
	pNeedle->Init(POSITION(3150, 90), 2, 1);
	SAFE_RELEASE(pNeedle);

	pNeedle = Obj::CreateObj<Needle>("Needle4_3", pLayer);
	pNeedle->SetTileTexture("SpikeRight", L"Platform/Tiles/Spike_Right.bmp");
	pNeedle->Init(POSITION(3210, 120), 1, 16);
	SAFE_RELEASE(pNeedle);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform12", pLayer);
	pTilePlatform->SetTileTexture("Tile1", L"Platform/Tiles/1.bmp");
	pTilePlatform->SetPlatform(POSITION(3450, 0), 2, 16);
	SAFE_RELEASE(pTilePlatform);

	pNeedle = Obj::CreateObj<Needle>("Needle4_4", pLayer);
	pNeedle->SetTileTexture("SpikeLeft", L"Platform/Tiles/Spike_Left.bmp");
	pNeedle->Init(POSITION(3420, 0), 1, 16);
	SAFE_RELEASE(pNeedle);

	/*** 딸기 ***/
	{
		// 벽타기 튜토리얼
		Strawberry* pStrawberry = Obj::CreateObj<Strawberry>("Strawberry1", pLayer);
		pStrawberry->SetPos(345, 100);
		SAFE_RELEASE(pStrawberry);

		// 벽점프 튜토리얼
		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry2-1", pLayer);
		pStrawberry->SetPos(645, 540);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry2_2", pLayer);
		pStrawberry->SetPos(750, 500);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry2_3", pLayer);
		pStrawberry->SetPos(750, 400);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry2_4", pLayer);
		pStrawberry->SetPos(750, 300);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry2_5", pLayer);
		pStrawberry->SetPos(750, 200);
		SAFE_RELEASE(pStrawberry);

		// 가시 튜토리얼
		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry3_1", pLayer);
		pStrawberry->SetPos(1230, 500);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry3_2", pLayer);
		pStrawberry->SetPos(1430, 500);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry3_3", pLayer);
		pStrawberry->SetPos(1470, 500);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry3_4", pLayer);
		pStrawberry->SetPos(1510, 500);
		SAFE_RELEASE(pStrawberry);

		// for fun1
		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry4_1", pLayer);
		pStrawberry->SetPos(1875, 400);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry4_1", pLayer);
		pStrawberry->SetPos(2075, 300);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry4_1", pLayer);
		pStrawberry->SetPos(2275, 200);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry4_1", pLayer);
		pStrawberry->SetPos(2475, 300);
		SAFE_RELEASE(pStrawberry);

		pStrawberry = Obj::CreateObj<Strawberry>("Strawberry4_1", pLayer);
		pStrawberry->SetPos(2675, 400);
		SAFE_RELEASE(pStrawberry);
	}




	// 스테이지 클리어
	StageClearObj* pStageClear = Obj::CreateObj<StageClearObj>("StageClear", pLayer);
	SAFE_RELEASE(pStageClear);

	// 바닥 사망 판정
	pNeedle = Obj::CreateObj<Needle>("BottomNeedle", pLayer);
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

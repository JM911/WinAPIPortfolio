#include "Stage3.h"
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
#include "../Object/Dashball.h"

Stage3::Stage3()
{
}

Stage3::~Stage3()
{
}

bool Stage3::Init()
{
	if (!Scene::Init())		// 부모 Scene 클래스의 초기화 함수 호출
		return false;

	SetSceneTag("Stage3");

	// 사운드
	if (!GET_SINGLE(SoundManager)->FindSound("Stage3BGM"))
	{
		GET_SINGLE(SoundManager)->Stop(SOUND_TYPE::BGM);
		GET_SINGLE(SoundManager)->LoadSound("Stage3BGM", true, "Stage3.ogg");
		GET_SINGLE(SoundManager)->Play("Stage3BGM");
		GET_SINGLE(SoundManager)->Volume(SOUND_TYPE::BGM, 0.15f);
	}

	// 플레이어
	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);

	// 땅
	Ground* pGround = Obj::CreateObj<Ground>("Ground1", pLayer);
	pGround->SetGroundInfo(-100, 2590, 90);
	SAFE_RELEASE(pGround);

	pGround = Obj::CreateObj<Ground>("Ground2", pLayer);
	pGround->SetGroundInfo(3600, 4000, 90);
	SAFE_RELEASE(pGround);



	/*** 플랫폼, 가시 ***/

	// 대시볼 튜토리얼
	Needle* pNeedle = Obj::CreateObj<Needle>("Needle1", pLayer);
	pNeedle->SetTileTexture("SpikeUp", L"Platform/Tiles/Spike_Up.bmp");
	pNeedle->Init(POSITION(350, 600), 12, 1);
	SAFE_RELEASE(pNeedle);

	// for fun 1
	TilePlatform* pTilePlatform = Obj::CreateObj<TilePlatform>("Platform1_1", pLayer);
	pTilePlatform->SetTileTexture("Tile2", L"Platform/Tiles/2.bmp");
	pTilePlatform->SetPlatform(POSITION(1300, 530), 4, 1);
	SAFE_RELEASE(pTilePlatform);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform1_2", pLayer);
	pTilePlatform->SetTileTexture("Tile2", L"Platform/Tiles/2.bmp");
	pTilePlatform->SetPlatform(POSITION(1450, 430), 4, 1);
	SAFE_RELEASE(pTilePlatform);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform1_3", pLayer);
	pTilePlatform->SetTileTexture("Tile2", L"Platform/Tiles/2.bmp");
	pTilePlatform->SetPlatform(POSITION(1600, 330), 4, 1);
	SAFE_RELEASE(pTilePlatform);

	// for fun 2
	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform2_1", pLayer);
	pTilePlatform->SetTileTexture("Tile2", L"Platform/Tiles/2.bmp");
	pTilePlatform->SetPlatform(POSITION(2500, 240), 3, 12);
	SAFE_RELEASE(pTilePlatform);

	pTilePlatform = Obj::CreateObj<TilePlatform>("Platform2_2", pLayer);
	pTilePlatform->SetTileTexture("Tile2", L"Platform/Tiles/2.bmp");
	pTilePlatform->SetPlatform(POSITION(3600, 240), 3, 12);
	SAFE_RELEASE(pTilePlatform);




	/*** 대시볼 ***/
	
	// 대시볼 튜토리얼
	Dashball* pDashball = Obj::CreateObj<Dashball>("Dashball1", pLayer);
	pDashball->SetPos(530, 500);
	SAFE_RELEASE(pDashball);

	// 대시볼+딸기
	pDashball = Obj::CreateObj<Dashball>("Dashball2", pLayer);
	pDashball->SetPos(1000, 350);
	SAFE_RELEASE(pDashball);

	// for fun 1
	pDashball = Obj::CreateObj<Dashball>("Dashball3", pLayer);
	pDashball->SetPos(1950, 200);
	SAFE_RELEASE(pDashball);

	// for fun 2
	pDashball = Obj::CreateObj<Dashball>("Dashball4_1", pLayer);
	pDashball->SetPos(2900, 150);
	SAFE_RELEASE(pDashball);
	pDashball = Obj::CreateObj<Dashball>("Dashball4_2", pLayer);
	pDashball->SetPos(3100, 150);
	SAFE_RELEASE(pDashball);
	pDashball = Obj::CreateObj<Dashball>("Dashball4_3", pLayer);
	pDashball->SetPos(3300, 150);
	SAFE_RELEASE(pDashball);




	/*** 딸기 ***/

	// 대시볼 튜토리얼
	Strawberry* pStrawberry = Obj::CreateObj<Strawberry>("Strawberry1_1", pLayer);
	pStrawberry->SetPos(380, 500);
	SAFE_RELEASE(pStrawberry);

	pStrawberry = Obj::CreateObj<Strawberry>("Strawberry1_2", pLayer);
	pStrawberry->SetPos(680, 520);
	SAFE_RELEASE(pStrawberry);

	// 대시볼+딸기
	pStrawberry = Obj::CreateObj<Strawberry>("Strawberry2", pLayer);
	pStrawberry->SetPos(1000, 170);
	SAFE_RELEASE(pStrawberry);

	// for fun 1
	pStrawberry = Obj::CreateObj<Strawberry>("Strawberry3", pLayer);
	pStrawberry->SetPos(2150, 200);
	SAFE_RELEASE(pStrawberry);




	// 스테이지 클리어
	StageClearObj* pStageClear = Obj::CreateObj<StageClearObj>("StageClear", pLayer);
	SAFE_RELEASE(pStageClear);

	// 바닥 사망 판정
	pNeedle = Obj::CreateObj<Needle>("BottomNeedle", pLayer);
	pNeedle->Init(POSITION(0.f, 800.f), 150, 1);
	SAFE_RELEASE(pNeedle);

	// 배경
	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("Stage3BG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(3840, 720), POSITION(0.f, 0.f), "Stage3BG", L"Stage3.bmp");
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

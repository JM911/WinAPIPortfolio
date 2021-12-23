#include "TestScene.h"
#include "Layer.h"
#include "../Object/Player.h"
#include "../Object/TestBackground.h"
#include "../Core/Camera.h"
#include "../Object/Ground.h"
#include "../Object/TestPlatform.h"
#include "../Object/TilePlatform.h"
#include "../Object/Needle.h"
#include "../Object/Dashball.h"
#include "../Object/ScoreUI.h"
#include "../Object/StageClearObj.h"
#include "../Object/Strawberry.h"
#include "../Object/PlayerLifeUI.h"
#include "../Sound/SoundManager.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

bool TestScene::Init()
{
	if (!Scene::Init())		// 부모 Scene 클래스의 초기화 함수 호출
		return false;

	//SetSceneTag("Stage1");

	// TODO: 앞으로 씬을 만들면 여기다가 레이어, 오브젝트 객체 모두 불러와서 사용

	// 플레이어
	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);	
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);

	// 땅
	Ground* pGround = Obj::CreateObj<Ground>("Ground1", pLayer);
	pGround->SetGroundInfo(-100.f, 700.f, 90);
	SAFE_RELEASE(pGround);

	//pGround = Obj::CreateObj<Ground>("Ground2", pLayer);
	//pGround->SetGroundInfo(600.f, 1200.f, 200);
	//SAFE_RELEASE(pGround);

	// 플랫폼
	TestPlatform* pPlatform = Obj::CreateObj<TestPlatform>("Platform", pLayer);
	pPlatform->Init(POSITION(700.f, 140.f), _SIZE(100.f, 280.f));
	SAFE_RELEASE(pPlatform);

	pPlatform = Obj::CreateObj<TestPlatform>("Platform", pLayer);
	pPlatform->Init(POSITION(1500.f, 140.f), _SIZE(100.f, 280.f));
	SAFE_RELEASE(pPlatform);

	// 타일 플랫폼
	TilePlatform* pTilePlatform = Obj::CreateObj<TilePlatform>("Platform2", pLayer);
	pTilePlatform->SetTileTexture("tempTile", L"Platform/Tiles/2.bmp");
	pTilePlatform->SetPlatform(POSITION(900.f, 140.f), 4, 6);
	SAFE_RELEASE(pTilePlatform);

	// 가시 (타일 플랫폼 형태)
	Needle* pNeedle = Obj::CreateObj<Needle>("Needle1", pLayer);
	pNeedle->Init(POSITION(0.f, 800.f), 250, 1);
	SAFE_RELEASE(pNeedle);

	// 대시볼
	Dashball* pDashball = Obj::CreateObj<Dashball>("Dashball", pLayer);
	pDashball->SetPos(100.f, 500.f);
	SAFE_RELEASE(pDashball);

	// 스테이지 클리어
	StageClearObj* pStageClear = Obj::CreateObj<StageClearObj>("StageClear", pLayer);
	SAFE_RELEASE(pStageClear);

	// 딸기
	Strawberry* pStrawberry = Obj::CreateObj<Strawberry>("Strawberry1", pLayer);
	pStrawberry->SetPos(500.f, 500.f);
	SAFE_RELEASE(pStrawberry);

	// 배경
	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("TestBG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(3840, 720), POSITION(0.f, 0.f), "TestBG", L"Stage1_2.bmp");
	SAFE_RELEASE(pBackground);

	// 점수 (테스트중)
	pLayer = FindLayer("UI");
	ScoreUI* pScore = Obj::CreateObj<ScoreUI>("TestScore", pLayer);
	SAFE_RELEASE(pScore);

	// 목숨 (테스트중)
	PlayerLifeUI* pLifeUI = Obj::CreateObj<PlayerLifeUI>("TestLife", pLayer);
	SAFE_RELEASE(pLifeUI);

	return true;
}

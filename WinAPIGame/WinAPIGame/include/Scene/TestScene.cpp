#include "TestScene.h"
#include "Layer.h"
#include "../Object/Player.h"
#include "../Object/TestBackground.h"
#include "../Core/Camera.h"
#include "../Object/Ground.h"
#include "../Object/TestPlatform.h"
#include "../Object/TilePlatform.h"
#include "../Object/Needle.h"

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

	// TODO: 앞으로 씬을 만들면 여기다가 레이어, 오브젝트 객체 모두 불러와서 사용

	// 플레이어
	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);	
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);

	// 땅
	Ground* pGround = Obj::CreateObj<Ground>("Ground1", pLayer);
	pGround->SetGroundInfo(-100.f, 500, 200);
	SAFE_RELEASE(pGround);

	pGround = Obj::CreateObj<Ground>("Ground2", pLayer);
	pGround->SetGroundInfo(600.f, 500, 200);
	SAFE_RELEASE(pGround);

	// 플랫폼
	TestPlatform* pPlatform = Obj::CreateObj<TestPlatform>("Platform1", pLayer);
	pPlatform->Init(POSITION(700.f, 500.f), _SIZE(100.f, 280.f));
	SAFE_RELEASE(pPlatform);

	pPlatform = Obj::CreateObj<TestPlatform>("Platform2", pLayer);
	pPlatform->Init(POSITION(1500.f, 500.f), _SIZE(100.f, 280.f));
	SAFE_RELEASE(pPlatform);

	// 타일 플랫폼
	TilePlatform* pTilePlatform = Obj::CreateObj<TilePlatform>("Platform2", pLayer);
	pTilePlatform->Init(POSITION(900.f, 500.f), 4, 6);
	SAFE_RELEASE(pTilePlatform);

	// 가시 (타일 플랫폼 형태)
	Needle* pNeedle = Obj::CreateObj<Needle>("Needle1", pLayer);
	pNeedle->Init(POSITION(0.f, 1000.f), 100, 1);
	SAFE_RELEASE(pNeedle);

	// 배경
	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("TestBG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(1920.f, 1080.f), POSITION(0.f, 0.f), "TestBG", L"bluemoon.bmp");
	SAFE_RELEASE(pBackground);



	// TODO: 배경 Init 처럼 초기화 정보를 따로 줘야 하는 상황에서는 어떻게 하지?
	// FW에서는 Init() 함수에 다 하드코딩했지만 여기서는 배경클래스 하나로 여러 객체를 만들어서 쓰고 싶다. 그냥 지금처럼 둘까?

	return true;
}

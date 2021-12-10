#include "TestScene.h"
#include "Layer.h"
#include "../Object/Player.h"
#include "../Object/TestBackground.h"
#include "../Core/Camera.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

bool TestScene::Init()
{
	if (!Scene::Init())
		return false;

	// TODO: 앞으로 씬을 만들면 여기다가 레이어, 오브젝트 객체 모두 불러와서 사용
	// TODO: 여기서 쓴 new 객체 선언, Init, AddObject 등은 모두 Obj의 CreateObj 함수를 만들 때 옮겨넣고 여기서는 CreateObj 함수를 호출해야함.

	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = new Player;
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	pPlayer->Init();
	pLayer->AddObject(pPlayer);
	SAFE_RELEASE(pPlayer);

	pLayer = FindLayer("Background");
	TestBackground* pBackground = new TestBackground;
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(1920.f, 1080.f), POSITION(0.f, 0.f), "TestBG", L"bg0.bmp");
	pLayer->AddObject(pBackground);
	SAFE_RELEASE(pBackground);

	return true;
}

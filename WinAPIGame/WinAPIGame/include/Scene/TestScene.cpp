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
	if (!Scene::Init())		// 부모 Scene 클래스의 초기화 함수 호출
		return false;

	// TODO: 앞으로 씬을 만들면 여기다가 레이어, 오브젝트 객체 모두 불러와서 사용

	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);	
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);

	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("TestBG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(1920.f, 1080.f), POSITION(0.f, 0.f), "TestBG", L"bg0.bmp");
	SAFE_RELEASE(pBackground);

	// TODO: 배경 Init 처럼 초기화 정보를 따로 줘야 하는 상황에서는 어떻게 하지?
	// FW에서는 Init() 함수에 다 하드코딩했지만 여기서는 배경클래스 하나로 여러 객체를 만들어서 쓰고 싶다. 그냥 지금처럼 둘까?

	return true;
}

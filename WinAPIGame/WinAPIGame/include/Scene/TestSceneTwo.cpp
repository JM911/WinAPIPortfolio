#include "TestSceneTwo.h"
#include "Layer.h"
#include "../Object/TestBackground.h"

TestSceneTwo::TestSceneTwo()
{
}

TestSceneTwo::~TestSceneTwo()
{
}

bool TestSceneTwo::Init()
{
	if (!Scene::Init())		// 부모 Scene 클래스의 초기화 함수 호출
		return false;

	SetSceneTag("Stage2");

	// 배경
	Layer* pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("TestBG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(3840, 720), POSITION(0.f, 0.f), "TestBG", L"Stage1_2.bmp");
	SAFE_RELEASE(pBackground);

	return true;
}

#include "TestScene.h"
#include "Layer.h"
#include "../Object/Player.h"

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

	// TODO: 앞으로 씬을 만들면 여기다가 레이어, 오브젝트 객체 모두 불러와서 
	// TODO: 카메라 함수도 필요하면 여기서 호출

	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = new Player;
	pPlayer->Init();
	pLayer->AddObject(pPlayer);
	SAFE_RELEASE(pPlayer);

	return true;
}

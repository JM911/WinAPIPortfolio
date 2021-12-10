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

	// TODO: ������ ���� ����� ����ٰ� ���̾�, ������Ʈ ��ü ��� �ҷ��ͼ� ���
	// TODO: ���⼭ �� new ��ü ����, Init, AddObject ���� ��� Obj�� CreateObj �Լ��� ���� �� �Űְܳ� ���⼭�� CreateObj �Լ��� ȣ���ؾ���.

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

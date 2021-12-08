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

	// TODO: ������ ���� ����� ����ٰ� ���̾�, ������Ʈ ��ü ��� �ҷ��ͼ� 
	// TODO: ī�޶� �Լ��� �ʿ��ϸ� ���⼭ ȣ��

	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = new Player;
	pPlayer->Init();
	pLayer->AddObject(pPlayer);
	SAFE_RELEASE(pPlayer);

	return true;
}

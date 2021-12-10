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
	if (!Scene::Init())		// �θ� Scene Ŭ������ �ʱ�ȭ �Լ� ȣ��
		return false;

	// TODO: ������ ���� ����� ����ٰ� ���̾�, ������Ʈ ��ü ��� �ҷ��ͼ� ���

	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);	
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);

	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("TestBG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(1920.f, 1080.f), POSITION(0.f, 0.f), "TestBG", L"bg0.bmp");
	SAFE_RELEASE(pBackground);

	// TODO: ��� Init ó�� �ʱ�ȭ ������ ���� ��� �ϴ� ��Ȳ������ ��� ����?
	// FW������ Init() �Լ��� �� �ϵ��ڵ������� ���⼭�� ���Ŭ���� �ϳ��� ���� ��ü�� ���� ���� �ʹ�. �׳� ����ó�� �ѱ�?

	return true;
}

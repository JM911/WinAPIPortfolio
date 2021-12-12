#include "TestScene.h"
#include "Layer.h"
#include "../Object/Player.h"
#include "../Object/TestBackground.h"
#include "../Core/Camera.h"
#include "../Object/Ground.h"

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

	// �÷��̾�
	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);	
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);

	// ��
	Ground* pGround = Obj::CreateObj<Ground>("Ground", pLayer);
	pGround->Init(300);
	SAFE_RELEASE(pGround);

	// ���
	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("TestBG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(1920.f, 1080.f), POSITION(0.f, 0.f), "TestBG", L"bluemoon.bmp");
	SAFE_RELEASE(pBackground);


	// TODO: ��� Init ó�� �ʱ�ȭ ������ ���� ��� �ϴ� ��Ȳ������ ��� ����?
	// FW������ Init() �Լ��� �� �ϵ��ڵ������� ���⼭�� ���Ŭ���� �ϳ��� ���� ��ü�� ���� ���� �ʹ�. �׳� ����ó�� �ѱ�?

	return true;
}

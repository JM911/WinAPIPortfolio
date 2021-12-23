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
	if (!Scene::Init())		// �θ� Scene Ŭ������ �ʱ�ȭ �Լ� ȣ��
		return false;

	//SetSceneTag("Stage1");

	// TODO: ������ ���� ����� ����ٰ� ���̾�, ������Ʈ ��ü ��� �ҷ��ͼ� ���

	// �÷��̾�
	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);	
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);

	// ��
	Ground* pGround = Obj::CreateObj<Ground>("Ground1", pLayer);
	pGround->SetGroundInfo(-100.f, 700.f, 90);
	SAFE_RELEASE(pGround);

	//pGround = Obj::CreateObj<Ground>("Ground2", pLayer);
	//pGround->SetGroundInfo(600.f, 1200.f, 200);
	//SAFE_RELEASE(pGround);

	// �÷���
	TestPlatform* pPlatform = Obj::CreateObj<TestPlatform>("Platform", pLayer);
	pPlatform->Init(POSITION(700.f, 140.f), _SIZE(100.f, 280.f));
	SAFE_RELEASE(pPlatform);

	pPlatform = Obj::CreateObj<TestPlatform>("Platform", pLayer);
	pPlatform->Init(POSITION(1500.f, 140.f), _SIZE(100.f, 280.f));
	SAFE_RELEASE(pPlatform);

	// Ÿ�� �÷���
	TilePlatform* pTilePlatform = Obj::CreateObj<TilePlatform>("Platform2", pLayer);
	pTilePlatform->SetTileTexture("tempTile", L"Platform/Tiles/2.bmp");
	pTilePlatform->SetPlatform(POSITION(900.f, 140.f), 4, 6);
	SAFE_RELEASE(pTilePlatform);

	// ���� (Ÿ�� �÷��� ����)
	Needle* pNeedle = Obj::CreateObj<Needle>("Needle1", pLayer);
	pNeedle->Init(POSITION(0.f, 800.f), 250, 1);
	SAFE_RELEASE(pNeedle);

	// ��ú�
	Dashball* pDashball = Obj::CreateObj<Dashball>("Dashball", pLayer);
	pDashball->SetPos(100.f, 500.f);
	SAFE_RELEASE(pDashball);

	// �������� Ŭ����
	StageClearObj* pStageClear = Obj::CreateObj<StageClearObj>("StageClear", pLayer);
	SAFE_RELEASE(pStageClear);

	// ����
	Strawberry* pStrawberry = Obj::CreateObj<Strawberry>("Strawberry1", pLayer);
	pStrawberry->SetPos(500.f, 500.f);
	SAFE_RELEASE(pStrawberry);

	// ���
	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("TestBG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(3840, 720), POSITION(0.f, 0.f), "TestBG", L"Stage1_2.bmp");
	SAFE_RELEASE(pBackground);

	// ���� (�׽�Ʈ��)
	pLayer = FindLayer("UI");
	ScoreUI* pScore = Obj::CreateObj<ScoreUI>("TestScore", pLayer);
	SAFE_RELEASE(pScore);

	// ��� (�׽�Ʈ��)
	PlayerLifeUI* pLifeUI = Obj::CreateObj<PlayerLifeUI>("TestLife", pLayer);
	SAFE_RELEASE(pLifeUI);

	return true;
}

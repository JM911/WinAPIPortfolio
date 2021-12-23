#include "Stage2.h"
#include "../Sound/SoundManager.h"
#include "../Object/Player.h"
#include "../Object/Ground.h"
#include "../Object/TestBackground.h"
#include "../Core/Camera.h"
#include "../Object/Needle.h"
#include "../Object/ScoreUI.h"
#include "../Object/PlayerLifeUI.h"

Stage2::Stage2()
{
}

Stage2::~Stage2()
{
}

bool Stage2::Init()
{
	if (!Scene::Init())		// �θ� Scene Ŭ������ �ʱ�ȭ �Լ� ȣ��
		return false;

	SetSceneTag("Stage2");

	// ����
	if (!GET_SINGLE(SoundManager)->FindSound("Stage2BGM"))
	{
		GET_SINGLE(SoundManager)->Stop(SOUND_TYPE::BGM);
		GET_SINGLE(SoundManager)->LoadSound("Stage2BGM", true, "Stage2.ogg");
		GET_SINGLE(SoundManager)->Play("Stage2BGM");
		GET_SINGLE(SoundManager)->Volume(SOUND_TYPE::BGM, 0.3f);
	}

	// �÷��̾�
	Layer* pLayer = FindLayer("Default");
	Player* pPlayer = Obj::CreateObj<Player>("Player", pLayer);
	GET_SINGLE(Camera)->SetTarget(pPlayer);
	SAFE_RELEASE(pPlayer);


	// ��
	Ground* pGround = Obj::CreateObj<Ground>("Ground1", pLayer);
	pGround->SetGroundInfo(-100.f, 4000.f, 90);
	SAFE_RELEASE(pGround);



	// �ٴ� ��� ����
	Needle* pNeedle = Obj::CreateObj<Needle>("BottomNeedle", pLayer);
	pNeedle->Init(POSITION(0.f, 800.f), 150, 1);
	SAFE_RELEASE(pNeedle);

	// ���
	pLayer = FindLayer("Background");
	TestBackground* pBackground = Obj::CreateObj<TestBackground>("Stage2BG", pLayer);
	pBackground->Init(POSITION(0.f, 0.f), _SIZE(3840, 720), POSITION(0.f, 0.f), "Stage2BG", L"Stage2.bmp");
	SAFE_RELEASE(pBackground);

	// ���� UI
	pLayer = FindLayer("UI");
	ScoreUI* pScore = Obj::CreateObj<ScoreUI>("ScoreUI", pLayer);
	SAFE_RELEASE(pScore);

	// ��� UI
	PlayerLifeUI* pLifeUI = Obj::CreateObj<PlayerLifeUI>("LifeUI", pLayer);
	SAFE_RELEASE(pLifeUI);

	return true;
}

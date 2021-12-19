#include "StartScene.h"
#include "TestScene.h"
#include "Layer.h"
#include "SceneManager.h"
#include "../Core.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "../Collider/ColliderRect.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::Init()
{
	if (!Scene::Init())
		return false;

	Layer* pLayer = FindLayer("Background");

	// ���г�(���ȭ��)
	UIPanel* pBackPanel = Obj::CreateObj<UIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(1280, 720);
	pBackPanel->SetTexture("StartBG", L"Backgrounds/startBG.bmp");

	SAFE_RELEASE(pBackPanel);
	
	// TODO: UI ������Ʈ��(�г�, ��ư, ���콺) �ϼ� �� �۾�

	// Play ��ư
	pLayer = FindLayer("UI");

	UIButton* pPlayBtn = Obj::CreateObj<UIButton>("PlayButton", pLayer);

	pPlayBtn->SetPos((float)(GETRESOLUTION.iW / 2), (float)(GETRESOLUTION.iH / 2));
	pPlayBtn->SetPivot(0.5f, 0.5f);
	pPlayBtn->SetSize(310, 130);
	pPlayBtn->SetTexture("PlayButton", L"UI/PlayButton.bmp");

	ColliderRect* pRC = (ColliderRect*)pPlayBtn->GetCollider("ButtonBody");
	pRC->SetRect(-155, -65, 155, 65);
	
	SAFE_RELEASE(pRC);

	pPlayBtn->SetCallback(this, &StartScene::StartButtonCallback);

	SAFE_RELEASE(pPlayBtn);

	return true;
}

void StartScene::StartButtonCallback(float fDeltaTime)
{
	GET_SINGLE(SceneManager)->CreateScene<TestScene>(SCENE_TYPE::NEXT);
}

void StartScene::EndButtonCallback(float fDeltaTime)
{
	GET_SINGLE(Core)->DestroyGame();
}

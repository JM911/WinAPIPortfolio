#include "StartScene.h"
#include "TestScene.h"
#include "Layer.h"
#include "SceneManager.h"
#include "../Core.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "../Collider/ColliderRect.h"
#include "../Sound/SoundManager.h"
#include "Stage1.h"
#include "../Object/ScoreUI.h"

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

	// 백패널(배경화면)
	UIPanel* pBackPanel = Obj::CreateObj<UIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(1280, 720);
	pBackPanel->SetTexture("StartBG", L"Backgrounds/startBG.bmp");

	SAFE_RELEASE(pBackPanel);

	// Play 버튼
	pLayer = FindLayer("UI");

	UIButton* pPlayBtn = Obj::CreateObj<UIButton>("PlayButton", pLayer);

	pPlayBtn->SetPos((float)(GETRESOLUTION.iW / 2) - 400, (float)(GETRESOLUTION.iH / 2) + 200);
	pPlayBtn->SetPivot(0.5f, 0.5f);
	pPlayBtn->SetSize(310, 130);
	pPlayBtn->SetTexture("PlayButton", L"UI/PlayButton.bmp");

	ColliderRect* pRC = (ColliderRect*)pPlayBtn->GetCollider("ButtonBody");
	pRC->SetRect(-155, -65, 155, 65);
	
	SAFE_RELEASE(pRC);

	pPlayBtn->SetCallback(this, &StartScene::StartButtonCallback);

	SAFE_RELEASE(pPlayBtn);

	// Exit 버튼
	UIButton* pExitBtn = Obj::CreateObj<UIButton>("ExitButton", pLayer);

	pExitBtn->SetPos((float)(GETRESOLUTION.iW / 2) + 400, (float)(GETRESOLUTION.iH / 2) + 200);
	pExitBtn->SetPivot(0.5f, 0.5f);
	pExitBtn->SetSize(310, 130);
	pExitBtn->SetTexture("ExitButtonTex", L"UI/ExitButton.bmp");

	pRC = (ColliderRect*)pExitBtn->GetCollider("ButtonBody");
	pRC->SetRect(-155, -65, 155, 65);

	SAFE_RELEASE(pRC);

	pExitBtn->SetCallback(this, &StartScene::EndButtonCallback);

	SAFE_RELEASE(pExitBtn);

	// 점수 초기화
	ScoreUI::SetScore(0);

	// BGM
	GET_SINGLE(SoundManager)->ClearMap();
	GET_SINGLE(SoundManager)->LoadSound("IntroBGM", true, "Intro.ogg");
	GET_SINGLE(SoundManager)->Play("IntroBGM");

	// 효과음
	GET_SINGLE(SoundManager)->LoadSound("StartSound", false, "GameStart.ogg");

	return true;
}

void StartScene::StartButtonCallback(float fDeltaTime)
{
	GET_SINGLE(SoundManager)->Play("StartSound");
	GET_SINGLE(SceneManager)->CreateScene<Stage1>(SCENE_TYPE::NEXT);
}

void StartScene::EndButtonCallback(float fDeltaTime)
{
	GET_SINGLE(Core)->DestroyGame();
}

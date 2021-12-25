#include "GameOverScene.h"
#include "../Object/UIPanel.h"
#include "../Core/Camera.h"
#include "../Sound/SoundManager.h"
#include "../Object/UIButton.h"
#include "../Core.h"
#include "../Collider/ColliderRect.h"
#include "../Scene/StartScene.h"
#include "../Scene/SceneManager.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

bool GameOverScene::Init()
{
	if (!Scene::Init())
		return false;

	Layer* pLayer = FindLayer("Background");

	// 백패널(배경화면)
	UIPanel* pBackPanel = Obj::CreateObj<UIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(1280, 720);
	pBackPanel->SetTexture("GameOverBG", L"Backgrounds/GameOverBG.bmp");

	GET_SINGLE(Camera)->SetTarget(pBackPanel);

	SAFE_RELEASE(pBackPanel);


	// Retry 버튼
	pLayer = FindLayer("UI");

	UIButton* pPlayBtn = Obj::CreateObj<UIButton>("RetryButton", pLayer);

	pPlayBtn->SetPos((float)(GETRESOLUTION.iW / 2) - 400, (float)(GETRESOLUTION.iH / 2) + 200);
	pPlayBtn->SetPivot(0.5f, 0.5f);
	pPlayBtn->SetSize(310, 130);
	pPlayBtn->SetTexture("RetryButtonTex", L"UI/RetryButton.bmp");

	ColliderRect* pRC = (ColliderRect*)pPlayBtn->GetCollider("ButtonBody");
	pRC->SetRect(-155, -65, 155, 65);

	SAFE_RELEASE(pRC);

	pPlayBtn->SetCallback(this, &GameOverScene::RetryButtonCallback);

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

	pExitBtn->SetCallback(this, &GameOverScene::EndButtonCallback);

	SAFE_RELEASE(pExitBtn);

	// 사운드
	GET_SINGLE(SoundManager)->Stop(SOUND_TYPE::BGM);
	GET_SINGLE(SoundManager)->LoadSound("GameOverSound", false, "GameOver.mp3");
	GET_SINGLE(SoundManager)->Play("GameOverSound");
		
	return true;
}

void GameOverScene::RetryButtonCallback(float fDeltaTime)
{
	GET_SINGLE(SceneManager)->CreateScene<StartScene>(SCENE_TYPE::NEXT);
}

void GameOverScene::EndButtonCallback(float fDeltaTime)
{
	GET_SINGLE(Core)->DestroyGame();
}

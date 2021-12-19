#include "GameOverScene.h"
#include "../Object/UIPanel.h"
#include "../Core/Camera.h"

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
	pBackPanel->SetTexture("StartBG", L"Backgrounds/startBG.bmp");

	GET_SINGLE(Camera)->SetTarget(pBackPanel);

	SAFE_RELEASE(pBackPanel);
		
	return true;
}

#include "StartScene.h"
#include "Layer.h"
#include "SceneManager.h"
#include "../Object/UIPanel.h"
#include "../Core.h"

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
	
	// TODO: UI 오브젝트들(패널, 버튼, 마우스) 완성 후 작업
	

	return true;
}

void StartScene::StartButtonCallback(float fDeltaTime)
{
}

void StartScene::EndButtonCallback(float fDeltaTime)
{
}

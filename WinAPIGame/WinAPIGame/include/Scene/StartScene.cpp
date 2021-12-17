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

	// ���г�(���ȭ��)
	UIPanel* pBackPanel = Obj::CreateObj<UIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(1280, 720);
	pBackPanel->SetTexture("StartBG", L"Backgrounds/startBG.bmp");

	SAFE_RELEASE(pBackPanel);
	
	// TODO: UI ������Ʈ��(�г�, ��ư, ���콺) �ϼ� �� �۾�
	

	return true;
}

void StartScene::StartButtonCallback(float fDeltaTime)
{
}

void StartScene::EndButtonCallback(float fDeltaTime)
{
}

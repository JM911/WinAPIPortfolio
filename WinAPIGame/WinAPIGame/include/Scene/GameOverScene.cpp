#include "GameOverScene.h"
#include "../Object/UIPanel.h"
#include "../Core/Camera.h"
#include "../Sound/SoundManager.h"

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

	// ���г�(���ȭ��)
	UIPanel* pBackPanel = Obj::CreateObj<UIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(1280, 720);
	pBackPanel->SetTexture("GameOverBG", L"Backgrounds/GameOverBG.bmp");

	GET_SINGLE(Camera)->SetTarget(pBackPanel);

	// ����
	GET_SINGLE(SoundManager)->Stop(SOUND_TYPE::BGM);
	GET_SINGLE(SoundManager)->LoadSound("GameOverSound", false, "GameOver.mp3");
	GET_SINGLE(SoundManager)->Play("GameOverSound");

	SAFE_RELEASE(pBackPanel);
		
	return true;
}

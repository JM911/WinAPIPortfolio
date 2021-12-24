#include "GameClearScene.h"
#include "../Object/UIPanel.h"
#include "../Core/Camera.h"
#include "../Sound/SoundManager.h"

GameClearScene::GameClearScene()
{
}

GameClearScene::~GameClearScene()
{
}

bool GameClearScene::Init()
{
	if (!Scene::Init())
		return false;

	Layer* pLayer = FindLayer("Background");


	// 백패널(배경화면)
	UIPanel* pBackPanel = Obj::CreateObj<UIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(1280, 720);
	pBackPanel->SetTexture("GameClearBG", L"Backgrounds/GameClearBG.bmp");

	GET_SINGLE(Camera)->SetTarget(pBackPanel);

	SAFE_RELEASE(pBackPanel);

	// TODO: 점수 표시

	// 사운드
	//GET_SINGLE(SoundManager)->Stop(SOUND_TYPE::BGM);
	//GET_SINGLE(SoundManager)->LoadSound("GameOverSound", false, "GameOver.mp3");
	//GET_SINGLE(SoundManager)->Play("GameOverSound");

	return true;
}

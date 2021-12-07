#include "SceneManager.h"
#include "Scene.h"
#include "TestScene.h"

DEFINITION_SINGLE(SceneManager)

SceneManager::SceneManager()	:
	m_pScene(NULL)
{
}

SceneManager::~SceneManager()
{
	SAFE_DELETE(m_pScene);
}

bool SceneManager::Init()
{
	// TODO: StartScene 클래스 타입으로 CreateScene 템플릿 함수 호출
	CreateScene<TestScene>();

	return true;
}

void SceneManager::Input(float fDeltaTime)
{
	m_pScene->Input(fDeltaTime);
}

int SceneManager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);

	// TODO: SceneChange 만들면 반환값 수정
	return 0;
}

int SceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);

	// TODO: SceneChange 만들면 반환값 수정
	return 0;
}

void SceneManager::Collision(float fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);
}

void SceneManager::Render(HDC hDC, float fDeltaTime)
{
	m_pScene->Render(hDC, fDeltaTime);
}

#include "SceneManager.h"
#include "Scene.h"
#include "TestScene.h"
#include "StartScene.h"
#include "../Collider/CollisionManager.h"

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
	CreateScene<StartScene>();

	return true;
}

void SceneManager::Input(float fDeltaTime)
{
	m_pScene->Input(fDeltaTime);
}

SCENE_CHANGE SceneManager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);

	return ChangeScene();
}

SCENE_CHANGE SceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);

	return ChangeScene();
}

void SceneManager::Collision(float fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);
}

void SceneManager::Render(HDC hDC, float fDeltaTime)
{
	m_pScene->Render(hDC, fDeltaTime);
}

SCENE_CHANGE SceneManager::ChangeScene()
{
	if (m_pNextScene)
	{
		SAFE_DELETE(m_pScene);
		m_pScene = m_pNextScene;
		m_pNextScene = NULL;

		GET_SINGLE(CollisionManager)->Clear();

		m_pScene->SetSceneType(SCENE_TYPE::CURRENT);
		// Scene::ChangePrototype();

		return SCENE_CHANGE::CHANGE;
	}

	return SCENE_CHANGE::NONE;
}

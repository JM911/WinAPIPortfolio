#include "SceneManager.h"
#include "Scene.h"
#include "TestScene.h"
#include "StartScene.h"
#include "../Collider/CollisionManager.h"

// 임시
#include "../Scene/Stage1.h"
#include "../Scene/Stage2.h"
#include "../Scene/Stage3.h"
#include "../Scene/GameClearScene.h"
#include "../Scene/GameOverScene.h"

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
	// 게임 시작할 때 호출하고 싶은 화면 작성
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

#pragma once

#include "../Game.h"

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

private:
	class Scene*	m_pScene;		// 현재 씬
	class Scene*	m_pNextScene;	// 다음 씬

// Get 함수
public:
	class Scene* GetScene()		const
	{
		return m_pScene;
	}

public:
	// TODO: Update, LateUpdate의 반환값으로 SCENE_CHANGE형 타입을 만들어서 넣어줌(장면전환 필요할 때 수정)
	bool Init();
	void Input(float fDeltaTime);
	SCENE_CHANGE Update(float fDeltaTime);
	SCENE_CHANGE LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);

	// TODO: 장면전환 함수 추가
	SCENE_CHANGE ChangeScene();

public:
	template <typename T>
	T* CreateScene(SCENE_TYPE st = SCENE_TYPE::CURRENT)
	{
		T* pScene = new T;

		pScene->SetSceneType(st);

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}

		switch (st)
		{
		case SCENE_TYPE::CURRENT:
			SAFE_DELETE(m_pScene);
			m_pScene = pScene;
			break;
		case SCENE_TYPE::NEXT:
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = pScene;
			break;
		}

		return pScene;
	}

	DECLARE_SINGLE(SceneManager)
};


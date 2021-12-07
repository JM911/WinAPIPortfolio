#pragma once

#include "../Game.h"

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

private:
	class Scene*	m_pScene;		// 현재 씬
	class scene*	m_pNextScene;	// 다음 씬

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
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);

	// TODO: 장면전환 함수, CreateScene 템플릿 추가

public:
	template <typename T>
	T* CreateScene()
	{
		T* pScene = new T;

		// TODO: SceneType만들면 적절한 함수 호출

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}

		// TODO: SceneType에 따라 m_pScene에 넣을지 m_pNextScene에 넣을지 결정하는 코드 작성
		SAFE_DELETE(m_pScene);
		m_pScene = pScene;
		// 일단은 그냥 m_pScene에 대입함

		return pScene;
	}

	DECLARE_SINGLE(SceneManager)
};


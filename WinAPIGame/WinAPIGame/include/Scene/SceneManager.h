#pragma once

#include "../Game.h"

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

private:
	class Scene*	m_pScene;		// ���� ��
	class Scene*	m_pNextScene;	// ���� ��

// Get �Լ�
public:
	class Scene* GetScene()		const
	{
		return m_pScene;
	}

public:
	// TODO: Update, LateUpdate�� ��ȯ������ SCENE_CHANGE�� Ÿ���� ���� �־���(�����ȯ �ʿ��� �� ����)
	bool Init();
	void Input(float fDeltaTime);
	SCENE_CHANGE Update(float fDeltaTime);
	SCENE_CHANGE LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);

	// TODO: �����ȯ �Լ� �߰�
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


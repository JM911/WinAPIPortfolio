#pragma once

#include "../Game.h"

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

private:
	class Scene*	m_pScene;		// ���� ��
	class scene*	m_pNextScene;	// ���� ��

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
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);

	// TODO: �����ȯ �Լ�, CreateScene ���ø� �߰�

public:
	template <typename T>
	T* CreateScene()
	{
		T* pScene = new T;

		// TODO: SceneType����� ������ �Լ� ȣ��

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}

		// TODO: SceneType�� ���� m_pScene�� ������ m_pNextScene�� ������ �����ϴ� �ڵ� �ۼ�
		SAFE_DELETE(m_pScene);
		m_pScene = pScene;
		// �ϴ��� �׳� m_pScene�� ������

		return pScene;
	}

	DECLARE_SINGLE(SceneManager)
};


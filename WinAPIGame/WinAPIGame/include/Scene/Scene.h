#pragma once

#include "../Game.h"

class Scene
{
private:
	friend class SceneManager;

protected:
	Scene();
	virtual ~Scene();	// FW���� ���������Լ��� �Ǿ�����. �Ƹ��� ��Ÿ?

// mapPrototype �߰� �� ���� �Լ� �߰�

protected:
	list<class Layer*>	m_LayerList;
	SCENE_TYPE			m_eSceneType;
	string				m_strSceneTag;

	// Get �Լ�
public:
	SCENE_TYPE GetSceneType()	const
	{
		return m_eSceneType;
	}
	string GetSceneTag()	const
	{
		return m_strSceneTag;
	}

	// Set �Լ�
public:
	void SetSceneType(SCENE_TYPE eSceneType)
	{
		m_eSceneType = eSceneType;
	}
	void SetSceneTag(const string& strTag)
	{
		m_strSceneTag = strTag;
	}

public:
	class Layer* CreateLayer(const string& strTag, int iZOrder = 0);
	class Layer* FindLayer(const string& strTag);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

public:
	static bool LayerSort(class Layer* pL1, class Layer* pL2);		// zorder �������� ������
};


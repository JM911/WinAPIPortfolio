#pragma once

#include "../Game.h"

class Scene
{
private:
	friend class SceneManager;

protected:
	Scene();
	virtual ~Scene();	// FW에는 순수가상함수로 되어있음. 아마도 오타?

// mapPrototype 추가 및 관련 함수 추가

protected:
	list<class Layer*>	m_LayerList;
	SCENE_TYPE			m_eSceneType;
	string				m_strSceneTag;

	// Get 함수
public:
	SCENE_TYPE GetSceneType()	const
	{
		return m_eSceneType;
	}
	string GetSceneTag()	const
	{
		return m_strSceneTag;
	}

	// Set 함수
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
	static bool LayerSort(class Layer* pL1, class Layer* pL2);		// zorder 오름차순 정리용
};


#pragma once

#include "../Game.h"

class Layer
{
private:
	friend class Scene;

private:
	Layer();

public:
	~Layer();		// 왜 public인지? 이유 알아보기

private:
	class Scene*		m_pScene;	// 이 레이어를 가지고 있는 씬
	string				m_strTag;	// 레이어의 이름(탐색용)
	int					m_iZOrder;	// z축 순서. 누가 덮고 덮일지를 생각하는 기준
	list<class Obj*>	m_ObjList;	// 리스트가 가지고 있는 오브젝트 리스트. 중간 삽입, 삭제가 잦아서 벡터보다는 리스트를 활용

// Get 함수
public:
	Scene* GetScene()	const
	{
		return m_pScene;
	}
	string GetTag()		const
	{
		return m_strTag;
	}
	int GetZOrder()		const
	{
		return m_iZOrder;
	}

// Set 함수
public:
	void SetScene(class Scene* pScene)
	{
		m_pScene = pScene;
	}
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}
	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

public:
	void AddObject(class Obj* pObj);

public:
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
};


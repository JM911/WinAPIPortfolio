#pragma once

#include "../Game.h"

class Layer
{
private:
	friend class Scene;

private:
	Layer();

public:
	~Layer();		// �� public����? ���� �˾ƺ���

private:
	class Scene*		m_pScene;	// �� ���̾ ������ �ִ� ��
	string				m_strTag;	// ���̾��� �̸�(Ž����)
	int					m_iZOrder;	// z�� ����. ���� ���� �������� �����ϴ� ����
	list<class Obj*>	m_ObjList;	// ����Ʈ�� ������ �ִ� ������Ʈ ����Ʈ. �߰� ����, ������ ��Ƽ� ���ͺ��ٴ� ����Ʈ�� Ȱ��

// Get �Լ�
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

// Set �Լ�
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


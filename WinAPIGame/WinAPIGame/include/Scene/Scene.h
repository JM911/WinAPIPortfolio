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


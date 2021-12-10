#include "Layer.h"
#include "../Object/Obj.h"

Layer::Layer()	:
	m_pScene(NULL),
	m_strTag(""),
	m_iZOrder(0)
{
}

Layer::~Layer()
{
	list<Obj*>::iterator iter;
	
	for (iter = m_ObjList.begin(); iter != m_ObjList.end(); ++iter)
	{
		Obj::EraseObj(*iter);
		SAFE_RELEASE((*iter));
	}

	m_ObjList.clear();
}

void Layer::AddObject(Obj* pObj)
{
	pObj->SetScene(m_pScene);
	pObj->SetLayer(this);
	pObj->AddRef();

	m_ObjList.push_back(pObj);
}

void Layer::Input(float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object�� Enable ���� �߰��ϸ� �ݿ�
		(*iter)->Input(fDeltaTime);
		// TODO: Object�� Life ���� �߰��ϸ� �ݿ�
	}
}

int Layer::Update(float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object�� Enable ���� �߰��ϸ� �ݿ�
		(*iter)->Update(fDeltaTime);
		// TODO: Object�� Life ���� �߰��ϸ� �ݿ�
	}

	return 0;
}

int Layer::LateUpdate(float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object�� Enable ���� �߰��ϸ� �ݿ�
		(*iter)->LateUpdate(fDeltaTime);
		// TODO: Object�� Life ���� �߰��ϸ� �ݿ�
	}

	return 0;
}

void Layer::Collision(float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object�� Enable ���� �߰��ϸ� �ݿ�
		(*iter)->Collision(fDeltaTime);
		// TODO: Object�� Life ���� �߰��ϸ� �ݿ�
	}
}

void Layer::Render(HDC hDC, float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object�� Enable ���� �߰��ϸ� �ݿ�
		(*iter)->Render(hDC, fDeltaTime);
		// TODO: Object�� Life ���� �߰��ϸ� �ݿ�
	}
}

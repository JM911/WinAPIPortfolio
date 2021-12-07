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
		// TODO: Obj에 ObjList를 추가하게 되면 삭제하는 함수도 만들어서 추가
		SAFE_RELEASE((*iter));
	}

	m_ObjList.clear();
}

void Layer::AddObject(Obj* pObj)
{
	// TODO: pObj의 씬, 레이어 추가 함수
	
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

void Layer::Input(float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object에 Enable 변수 추가하면 반영
		(*iter)->Input(fDeltaTime);
		// TODO: Object에 Life 변수 추가하면 반영
	}
}

int Layer::Update(float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object에 Enable 변수 추가하면 반영
		(*iter)->Update(fDeltaTime);
		// TODO: Object에 Life 변수 추가하면 반영
	}

	return 0;
}

int Layer::LateUpdate(float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object에 Enable 변수 추가하면 반영
		(*iter)->LateUpdate(fDeltaTime);
		// TODO: Object에 Life 변수 추가하면 반영
	}

	return 0;
}

void Layer::Collision(float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object에 Enable 변수 추가하면 반영
		(*iter)->Collision(fDeltaTime);
		// TODO: Object에 Life 변수 추가하면 반영
	}
}

void Layer::Render(HDC hDC, float fDeltaTime)
{
	list<Obj*>::iterator iter;
	list<Obj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object에 Enable 변수 추가하면 반영
		(*iter)->Render(hDC, fDeltaTime);
		// TODO: Object에 Life 변수 추가하면 반영
	}
}

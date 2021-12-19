#include "Scene.h"
#include "Layer.h"

Scene::Scene()	:
	m_eSceneType(SCENE_TYPE::CURRENT),
	m_strSceneTag("")
{
	// TODO: 필요한 레이어들 여기에 만들기
	Layer* pLayer = CreateLayer("Default", 1);
	pLayer = CreateLayer("Background");
	pLayer = CreateLayer("UI", INT_MAX);
}

Scene::~Scene()
{
	// TODO: mapPrototype 추가하면 추가작업
	Safe_Delete_VecList(m_LayerList);
}

Layer* Scene::CreateLayer(const string& strTag, int iZOrder)
{
	Layer* pLayer = new Layer;

	pLayer->SetTag(strTag);
	pLayer->SetScene(this);
	pLayer->SetZOrder(iZOrder);

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 2)
		m_LayerList.sort(Scene::LayerSort);

	return pLayer;
}

Layer* Scene::FindLayer(const string& strTag)
{
	list<Layer*>::iterator iter;

	for (iter = m_LayerList.begin(); iter != m_LayerList.end(); ++iter)
	{
		if ((*iter)->GetTag() == strTag)
			return *iter;
	}

	return NULL;
}

bool Scene::Init()
{
	return true;
}

void Scene::Input(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Layer에 Enable 변수 추가하면 반영

		(*iter)->Input(fDeltaTime);

		// TODO: Layer에 Life 변수 추가하면 반영
	}
}

int Scene::Update(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Layer에 Enable 변수 추가하면 반영

		(*iter)->Update(fDeltaTime);

		// TODO: Layer에 Life 변수 추가하면 반영
	}

	return 0;
}

int Scene::LateUpdate(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Layer에 Enable 변수 추가하면 반영

		(*iter)->LateUpdate(fDeltaTime);

		// TODO: Layer에 Life 변수 추가하면 반영
	}

	return 0;
}

void Scene::Collision(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Layer에 Enable 변수 추가하면 반영

		(*iter)->Collision(fDeltaTime);

		// TODO: Layer에 Life 변수 추가하면 반영
	}
}

void Scene::Render(HDC hDC, float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Layer에 Enable 변수 추가하면 반영

		(*iter)->Render(hDC, fDeltaTime);

		// TODO: Layer에 Life 변수 추가하면 반영
	}
}

bool Scene::LayerSort(Layer* pL1, Layer* pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();		// 등호 붙이지 않도록 주의. 주로 여기서 충돌이 많이 일어남.
}

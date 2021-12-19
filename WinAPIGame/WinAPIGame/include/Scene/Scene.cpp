#include "Scene.h"
#include "Layer.h"

Scene::Scene()	:
	m_eSceneType(SCENE_TYPE::CURRENT),
	m_strSceneTag("")
{
	// TODO: �ʿ��� ���̾�� ���⿡ �����
	Layer* pLayer = CreateLayer("Default", 1);
	pLayer = CreateLayer("Background");
	pLayer = CreateLayer("UI", INT_MAX);
}

Scene::~Scene()
{
	// TODO: mapPrototype �߰��ϸ� �߰��۾�
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
		// TODO: Layer�� Enable ���� �߰��ϸ� �ݿ�

		(*iter)->Input(fDeltaTime);

		// TODO: Layer�� Life ���� �߰��ϸ� �ݿ�
	}
}

int Scene::Update(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Layer�� Enable ���� �߰��ϸ� �ݿ�

		(*iter)->Update(fDeltaTime);

		// TODO: Layer�� Life ���� �߰��ϸ� �ݿ�
	}

	return 0;
}

int Scene::LateUpdate(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Layer�� Enable ���� �߰��ϸ� �ݿ�

		(*iter)->LateUpdate(fDeltaTime);

		// TODO: Layer�� Life ���� �߰��ϸ� �ݿ�
	}

	return 0;
}

void Scene::Collision(float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Layer�� Enable ���� �߰��ϸ� �ݿ�

		(*iter)->Collision(fDeltaTime);

		// TODO: Layer�� Life ���� �߰��ϸ� �ݿ�
	}
}

void Scene::Render(HDC hDC, float fDeltaTime)
{
	list<Layer*>::iterator iter;
	list<Layer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Layer�� Enable ���� �߰��ϸ� �ݿ�

		(*iter)->Render(hDC, fDeltaTime);

		// TODO: Layer�� Life ���� �߰��ϸ� �ݿ�
	}
}

bool Scene::LayerSort(Layer* pL1, Layer* pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();		// ��ȣ ������ �ʵ��� ����. �ַ� ���⼭ �浹�� ���� �Ͼ.
}

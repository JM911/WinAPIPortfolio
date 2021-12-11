#include "ColliderRect.h"
#include "../Object/Obj.h"
#include "../Core/Camera.h"

ColliderRect::ColliderRect()
{
	m_eColType = COL_TYPE::RECT;
}

ColliderRect::ColliderRect(const ColliderRect& coll)	:
	Collider(coll)
{
	m_tInfo = coll.m_tInfo;
}

ColliderRect::~ColliderRect()
{
}

void ColliderRect::SetRect(int l, int t, int r, int b)
{
	m_tInfo.left = l;
	m_tInfo.top = t;
	m_tInfo.right = r;
	m_tInfo.bottom = b;
}

bool ColliderRect::Init()
{
	return true;
}

void ColliderRect::Input(float fDeltaTime)
{
	Collider::Input(fDeltaTime);
}

int ColliderRect::Update(float fDeltaTime)
{
	Collider::Update(fDeltaTime);
	return 0;
}

int ColliderRect::LateUpdate(float fDeltaTime)
{
	Collider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.left = (LONG)tPos.x + m_tInfo.left;
	m_tWorldInfo.top = (LONG)tPos.y + m_tInfo.top;
	m_tWorldInfo.right = (LONG)tPos.x + m_tInfo.right;
	m_tWorldInfo.bottom = (LONG)tPos.y + m_tInfo.bottom;

	return 0;
}

bool ColliderRect::Collision(Collider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case COL_TYPE::RECT:
		return CollisionRectToRect(m_tWorldInfo, ((ColliderRect*)pDest)->GetWorldInfo(), &m_tIntersectInfo);
		break;
	}

	return false;
}

void ColliderRect::Render(HDC hDC, float fDeltaTime)
{
#ifdef _DEBUG
	Collider::Render(hDC, fDeltaTime);

	POSITION tCamPos = GET_SINGLE(Camera)->GetPos();

	RECT tRC = m_tWorldInfo;
	tRC.left -= (LONG)tCamPos.x;
	tRC.top -= (LONG)tCamPos.y;
	tRC.right -= (LONG)tCamPos.x;
	tRC.bottom -= (LONG)tCamPos.y;
	

	MoveToEx(hDC, tRC.left, tRC.top, NULL);
	LineTo(hDC, tRC.right, tRC.top);
	LineTo(hDC, tRC.right, tRC.bottom);
	LineTo(hDC, tRC.left, tRC.bottom);
	LineTo(hDC, tRC.left, tRC.top);
#endif	// DEBUG
}

ColliderRect* ColliderRect::Clone()
{
	return new ColliderRect(*this);
}

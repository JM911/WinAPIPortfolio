#include "ColliderPoint.h"
#include "../Object/Obj.h"
#include "ColliderRect.h"

ColliderPoint::ColliderPoint()
{
	m_eColType = COL_TYPE::POINT;
}

ColliderPoint::ColliderPoint(const ColliderPoint& coll)	:
	Collider(coll)
{
}

ColliderPoint::~ColliderPoint()
{
}

bool ColliderPoint::Init()
{
	return true;
}

void ColliderPoint::Input(float fDeltaTime)
{
	Collider::Input(fDeltaTime);
}

int ColliderPoint::Update(float fDeltaTime)
{
	Collider::Update(fDeltaTime);
	return 0;
}

int ColliderPoint::LateUpdate(float fDeltaTime)
{
	Collider::LateUpdate(fDeltaTime);

	m_tPointPos = m_pObj->GetPos();

	return 0;
}

bool ColliderPoint::Collision(Collider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case COL_TYPE::RECT:
		return CollisionRectToPoint(((ColliderRect*)pDest)->GetWorldInfo(), m_tPointPos);
	}

	return false;
}

void ColliderPoint::Render(HDC hDC, float fDeltaTime)
{
	Collider::Render(hDC, fDeltaTime);
}

ColliderPoint* ColliderPoint::Clone()
{
	return new ColliderPoint(*this);
}

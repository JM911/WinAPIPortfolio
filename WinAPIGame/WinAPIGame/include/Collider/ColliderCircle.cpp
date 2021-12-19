#include "ColliderCircle.h"
#include "../Object/Obj.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Collider/ColliderPoint.h"

ColliderCircle::ColliderCircle()
{
	m_eColType = COL_TYPE::CIRCLE;
}

ColliderCircle::ColliderCircle(const ColliderCircle& coll)	:
	Collider(coll)
{
	m_tInfo = coll.m_tInfo;
}

ColliderCircle::~ColliderCircle()
{
}

bool ColliderCircle::Init()
{
	return true;
}

void ColliderCircle::Input(float fDeltaTime)
{
	Collider::Input(fDeltaTime);
}

int ColliderCircle::Update(float fDeltaTime)
{
	Collider::Update(fDeltaTime);
	return 0;
}

int ColliderCircle::LateUpdate(float fDeltaTime)
{
	Collider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.tCenter.x = tPos.x + m_tInfo.tCenter.x;
	m_tWorldInfo.tCenter.y = tPos.y + m_tInfo.tCenter.y;

	return 0;
}

bool ColliderCircle::Collision(Collider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case COL_TYPE::CIRCLE:
		return CollisionCircleToCircle(m_tWorldInfo, ((ColliderCircle*)pDest)->GetWorldInfo());
	case COL_TYPE::RECT:
		return CollisionRectToCircle(((ColliderRect*)pDest)->GetWorldInfo(), m_tWorldInfo);
	case COL_TYPE::POINT:
		return CollisionCircleToPoint(m_tWorldInfo, ((ColliderPoint*)pDest)->GetPointPos());
	}

	return false;
}

void ColliderCircle::Render(HDC hDC, float fDeltaTime)
{
#ifdef _DEBUG
	Collider::Render(hDC, fDeltaTime);

	RECT tRC;	// 외접사각형
	POSITION tCamPos = GET_SINGLE(Camera)->GetPos();

	tRC.left	= (int)(m_tWorldInfo.tCenter.x - m_tWorldInfo.fRadius - tCamPos.x);
	tRC.top		= (int)(m_tWorldInfo.tCenter.y - m_tWorldInfo.fRadius - tCamPos.y);
	tRC.right	= (int)(m_tWorldInfo.tCenter.x + m_tWorldInfo.fRadius - tCamPos.x);
	tRC.bottom	= (int)(m_tWorldInfo.tCenter.y + m_tWorldInfo.fRadius - tCamPos.y);

	Arc(hDC, tRC.left, tRC.top, tRC.right, tRC.bottom, tRC.right, tRC.bottom, tRC.left, tRC.top);
	Arc(hDC, tRC.left, tRC.top, tRC.right, tRC.bottom, tRC.left, tRC.top, tRC.right, tRC.bottom);
#endif	// DEBUG
}

ColliderCircle* ColliderCircle::Clone()
{
	return new ColliderCircle(*this);
}

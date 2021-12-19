#include "Collider.h"
#include "../Core/CMath.h"

Collider::Collider()
{
}

Collider::Collider(const Collider& coll)
{
	*this = coll;
}

Collider::~Collider()
{
	// 이렇게 하는거 맞나?? SAFE_RELEASE도 없고 clear호출보다 더 연산만 잡아먹는 것 같은데...

	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->EraseCollisionList(this);
	}
}

void Collider::Input(float fDeltaTime)
{
}

int Collider::Update(float fDeltaTime)
{
	return 0;
}

int Collider::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool Collider::Collision(Collider* pDest)
{
	return false;
}

void Collider::Render(HDC hDC, float fDeltaTime)
{
}

bool Collider::CollisionRectToRect(const RECT& src, const RECT& dest, LPRECT pIntersect)
{
	bool bVertical		= false;	// 수직 충돌 여부
	bool bHorizontal	= false;	// 수평 충돌 여부

	// 수평 충돌
	if (src.left < dest.right && src.right > dest.left)
	{
		bHorizontal = true;

		if (pIntersect)
		{
			pIntersect->left = max(src.left, dest.left);
			pIntersect->right = min(src.right, dest.right);
		}
	}

	// 수직 충돌
	if (src.top < dest.bottom && src.bottom > dest.top)
	{
		bVertical = true;

		if (pIntersect)
		{
			pIntersect->top = max(src.top, dest.top);
			pIntersect->bottom = min(src.bottom, dest.bottom);
		}
	}

	if (bHorizontal && bVertical)
	{
		return true;
	}

	if (pIntersect)
	{
		pIntersect->left = 0;
		pIntersect->right = 0;
		pIntersect->top = 0;
		pIntersect->bottom = 0;
	}
	
	return false;
}

bool Collider::CollisionRectToPoint(const RECT& src, const POSITION& dest)
{
	if (dest.x < src.left)
		return false;
	else if (dest.x > src.right)
		return false;
	else if (dest.y < src.top)
		return false;
	else if (dest.y > src.bottom)
		return false;

	return true;
}

bool Collider::CollisionRectToCircle(const RECT& src, const CIRCLE& dest)
{
	if ((src.left <= dest.tCenter.x && dest.tCenter.x <= src.right)
		|| (src.top <= dest.tCenter.y && dest.tCenter.y <= src.bottom))
	{
		RECT tRC = src;
		tRC.left	-= (int)dest.fRadius;
		tRC.top		-= (int)dest.fRadius;
		tRC.right	+= (int)dest.fRadius;
		tRC.bottom	+= (int)dest.fRadius;

		if (dest.tCenter.x < tRC.left)
			return false;
		else if (dest.tCenter.x > tRC.right)
			return false;
		else if (dest.tCenter.y < tRC.top)
			return false;
		else if (dest.tCenter.y > tRC.bottom)
			return false;

		return true;
	}

	POSITION tPos[4];
	tPos[0] = POSITION(src.left, src.top);
	tPos[1] = POSITION(src.right, src.top);
	tPos[2] = POSITION(src.right, src.bottom);
	tPos[3] = POSITION(src.left, src.bottom);

	for (int i = 0; i < 4; i++)
	{
		float fDist = CMath::Distance(tPos[i], dest.tCenter);

		if (fDist <= dest.fRadius)
			return true;
	}

	return false;
}

bool Collider::CollisionCircleToCircle(const CIRCLE& src, const CIRCLE& dest)
{
	return CMath::Distance(src.tCenter, dest.tCenter) <= src.fRadius + dest.fRadius;
}

bool Collider::CollisionCircleToPoint(const CIRCLE& src, const POSITION& dest)
{
	return CMath::Distance(src.tCenter, dest) <= src.fRadius;
}

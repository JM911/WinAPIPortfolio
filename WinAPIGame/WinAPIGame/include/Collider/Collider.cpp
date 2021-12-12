#include "Collider.h"

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

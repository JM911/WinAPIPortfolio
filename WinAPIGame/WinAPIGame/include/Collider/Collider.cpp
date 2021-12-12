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
	// �̷��� �ϴ°� �³�?? SAFE_RELEASE�� ���� clearȣ�⺸�� �� ���길 ��ƸԴ� �� ������...

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
	bool bVertical		= false;	// ���� �浹 ����
	bool bHorizontal	= false;	// ���� �浹 ����

	// ���� �浹
	if (src.left < dest.right && src.right > dest.left)
	{
		bHorizontal = true;

		if (pIntersect)
		{
			pIntersect->left = max(src.left, dest.left);
			pIntersect->right = min(src.right, dest.right);
		}
	}

	// ���� �浹
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

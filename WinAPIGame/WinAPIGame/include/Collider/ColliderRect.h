#pragma once
#include "Collider.h"

class ColliderRect	:
	public Collider
{
protected:
	friend class Obj;

protected:
	ColliderRect();
	ColliderRect(const ColliderRect& coll);
	virtual ~ColliderRect();

private:
	RECT	m_tInfo;
	RECT	m_tWorldInfo;
	RECT	m_tIntersectInfo;

	// Get 함수
public:
	RECT GetInfo()		const
	{
		return m_tInfo;
	}
	RECT GetWorldInfo()	const
	{
		return m_tWorldInfo;
	}
	RECT GetIntersectInfo()	const
	{
		return m_tIntersectInfo;
	}

	// Set 함수
public:
	void SetRect(int l, int t, int r, int b);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(Collider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);

	virtual ColliderRect* Clone();
};


#pragma once
#include "Collider.h"

class ColliderCircle :
    public Collider
{
protected:
	friend class Obj;

protected:
	ColliderCircle();
	ColliderCircle(const ColliderCircle& coll);
	~ColliderCircle();

private:
	CIRCLE	m_tInfo;
	CIRCLE	m_tWorldInfo;

	// Get �Լ�
public:
	CIRCLE GetInfo()	const
	{
		return m_tInfo;
	}
	CIRCLE GetWorldInfo()	const
	{
		return m_tWorldInfo;
	}

	// Set �Լ�
public:
	void SetCircle(const POSITION& tCenter, float fRadius)
	{
		m_tInfo.tCenter = tCenter;
		m_tInfo.fRadius = fRadius;
		m_tWorldInfo.fRadius = fRadius;
	}


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(Collider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);

	virtual ColliderCircle* Clone();
};


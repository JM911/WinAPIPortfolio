#pragma once
#include "Collider.h"

class ColliderPoint :
    public Collider
{
protected:
    friend class Obj;

protected:
    ColliderPoint();
    ColliderPoint(const ColliderPoint& coll);
    ~ColliderPoint();

protected:
    POSITION    m_tPointPos;

    // Get ÇÔ¼ö
public:
    POSITION GetPointPos() const
    {
        return m_tPointPos;
    }

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual bool Collision(Collider* pDest);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual ColliderPoint* Clone();
};


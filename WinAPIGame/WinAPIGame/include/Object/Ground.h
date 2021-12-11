#pragma once
#include "StaticObj.h"

class Ground :
    public StaticObj
{
private:
    friend class Scene;

protected:
    Ground();
    Ground(const Ground& ground);
    ~Ground();

private:
    int m_iHeight;      // ���� �عٴں����� ����

public:
    virtual bool Init();
    bool Init(int tHeight);
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Ground* Clone();
};


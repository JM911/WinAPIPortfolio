#pragma once
#include "StaticObj.h"

class Ground :
    public StaticObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    Ground();
    Ground(const Ground& ground);
    ~Ground();

protected:
    float m_fStartX;    // �� ������ġ x ��ǥ
    float m_fEndX;      // �� ����ġ x ��ǥ
    int m_iHeight;      // ���� �عٴں����� ����

    // Set �Լ�
public:
    void SetGroundInfo(float fStartX, float fEndX, int iHeight);

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Ground* Clone();
};


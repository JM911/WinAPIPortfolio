#pragma once
#include "StaticObj.h"
class Dashball :
    public StaticObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    Dashball();
    Dashball(const Dashball& ball);
    ~Dashball();

private:
    bool    m_bEnable;
    float   m_fReviveTime;
    float   m_fTime;

    // Get �Լ�
public:
    bool GetEnable()    const
    {
        return m_bEnable;
    }

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Dashball* Clone();

    // TODO: �浹�Լ� �߰� - �÷��̾�� �浹�ϸ� �������(�ؽ��ĸ� �� ȭ������ ���) Enable = false ����
    void CollisionWithPlayer(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
};


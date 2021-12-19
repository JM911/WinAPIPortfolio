#pragma once
#include "UIObj.h"

class UIButton :
    public UIObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    UIButton();
    UIButton(const UIButton& ui);
    ~UIButton();

private:
    function<void(float fTime)> m_BtnCallback;  // ��ư�� ������ �� ȣ��Ǵ� �ݹ��Լ��� ��� ������ ����
    bool    m_bCallbackEnable;
    BTN_STATE  m_eState;

    // Set �Լ�
public:
    template<typename T>
    void SetCallback(T* pObj, void (T::* pFunc)(float))  // pObj�� ����Լ��� ���
    {
        m_BtnCallback = bind(pFunc, pObj, placeholders::_1);
        m_bCallbackEnable = true;
    }

    void SetCallback(void(*pFunc)(float))   // �����Լ��� ���
    {
        m_BtnCallback = bind(pFunc, placeholders::_1);
        m_bCallbackEnable = true;
    }

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);
    virtual UIButton* Clone();

    // (���콺 �����Ϳ���) �浹�Լ�
public:
    void MouseOver(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
    void MouseOut(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
};


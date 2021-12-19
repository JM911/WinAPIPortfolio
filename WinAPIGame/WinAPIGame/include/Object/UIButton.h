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
    function<void(float fTime)> m_BtnCallback;  // 버튼을 눌렀을 때 호출되는 콜백함수를 멤버 변수로 저장
    bool    m_bCallbackEnable;
    BTN_STATE  m_eState;

    // Set 함수
public:
    template<typename T>
    void SetCallback(T* pObj, void (T::* pFunc)(float))  // pObj의 멤버함수를 등록
    {
        m_BtnCallback = bind(pFunc, pObj, placeholders::_1);
        m_bCallbackEnable = true;
    }

    void SetCallback(void(*pFunc)(float))   // 전역함수를 등록
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

    // (마우스 포인터와의) 충돌함수
public:
    void MouseOver(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
    void MouseOut(class Collider* pSrc, class Collider* pDest, float fDeltaTime);
};


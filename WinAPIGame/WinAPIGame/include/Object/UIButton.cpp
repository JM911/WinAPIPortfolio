#include "UIButton.h"
#include "../Collider/ColliderRect.h"
#include "../Core/CInput.h"

UIButton::UIButton()    :
    m_eState(BTN_STATE::NONE),
    m_bCallbackEnable(false)
{
}

UIButton::UIButton(const UIButton& ui)  :
    UIObj(ui)
{
    m_eState = BTN_STATE::NONE;
    m_bCallbackEnable = false;
}

UIButton::~UIButton()
{
}

bool UIButton::Init()
{
    ColliderRect* pColl = AddCollider<ColliderRect>("ButtonBody");

    pColl->AddCollisionFunction(COL_STATE::ENTER, this, &UIButton::MouseOver);
    pColl->AddCollisionFunction(COL_STATE::LEAVE, this, &UIButton::MouseOut);

    //SAFE_RELEASE(pColl);

    return true;
}

void UIButton::Input(float fDeltaTime)
{
    UIObj::Input(fDeltaTime);
}

int UIButton::Update(float fDeltaTime)
{
    UIObj::Update(fDeltaTime);
    return 0;
}

int UIButton::LateUpdate(float fDeltaTime)
{
    UIObj::LateUpdate(fDeltaTime);

    if (m_eState != BTN_STATE::NONE)
    {
        if (KEYPRESS("MouseLClick"))    // 버튼을 클릭하고 홀드할 때
        {
            m_eState = BTN_STATE::CLICK;
            // TODO: 버튼을 클릭하고 홀드하는 상황의 텍스처를 다르게 만들고 싶은 경우 여기에 작성
            // SetImageOffset(0.f, 0.f);
        }

        if (m_eState == BTN_STATE::CLICK && KEYUP("MouseLClick"))   // 버튼을 누르다가 클릭버튼을 뗐을 때(클릭 완료)
        {
            m_eState = BTN_STATE::MOUSE_OVER;
            if (m_bCallbackEnable)
                m_BtnCallback(fDeltaTime);
        }
    }

    return 0;
}

void UIButton::Collision(float fDeltaTime)
{
    UIObj::Collision(fDeltaTime);
}

void UIButton::Render(HDC hDC, float fDeltaTime)
{
    UIObj::Render(hDC, fDeltaTime);
}

UIButton* UIButton::Clone()
{
    return new UIButton(*this);
}

void UIButton::MouseOver(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
    if (pDest->GetTag() == "Mouse")
    {
        m_eState = BTN_STATE::MOUSE_OVER;
        SetImageOffset(0.f, m_tSize.y);     // 마우스가 버튼 범위에 들어오면 텍스처 이미지오프셋 변경
    }
}

void UIButton::MouseOut(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
    if (pDest->GetTag() == "Mouse")
    {
        m_eState = BTN_STATE::NONE;
        SetImageOffset(0.f, 0.f);       // 마우스가 버튼 범위에서 나가면 텍스처 이미지오프셋 원래대로 변경
    }
}

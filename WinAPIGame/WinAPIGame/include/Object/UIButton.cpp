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
        if (KEYPRESS("MouseLClick"))    // ��ư�� Ŭ���ϰ� Ȧ���� ��
        {
            m_eState = BTN_STATE::CLICK;
            // TODO: ��ư�� Ŭ���ϰ� Ȧ���ϴ� ��Ȳ�� �ؽ�ó�� �ٸ��� ����� ���� ��� ���⿡ �ۼ�
            // SetImageOffset(0.f, 0.f);
        }

        if (m_eState == BTN_STATE::CLICK && KEYUP("MouseLClick"))   // ��ư�� �����ٰ� Ŭ����ư�� ���� ��(Ŭ�� �Ϸ�)
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
        SetImageOffset(0.f, m_tSize.y);     // ���콺�� ��ư ������ ������ �ؽ�ó �̹��������� ����
    }
}

void UIButton::MouseOut(Collider* pSrc, Collider* pDest, float fDeltaTime)
{
    if (pDest->GetTag() == "Mouse")
    {
        m_eState = BTN_STATE::NONE;
        SetImageOffset(0.f, 0.f);       // ���콺�� ��ư �������� ������ �ؽ�ó �̹��������� ������� ����
    }
}

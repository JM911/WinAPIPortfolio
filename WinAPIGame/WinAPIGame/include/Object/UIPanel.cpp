#include "UIPanel.h"

UIPanel::UIPanel()
{
}

UIPanel::UIPanel(const UIPanel& ui) :
    UIObj(ui)
{
}

UIPanel::~UIPanel()
{
}

bool UIPanel::Init()
{
    return true;
}

void UIPanel::Input(float fDeltaTime)
{
    UIObj::Input(fDeltaTime);
}

int UIPanel::Update(float fDeltaTime)
{
    UIObj::Update(fDeltaTime);
    return 0;
}

int UIPanel::LateUpdate(float fDeltaTime)
{
    UIObj::LateUpdate(fDeltaTime);
    return 0;
}

void UIPanel::Collision(float fDeltaTime)
{
    UIObj::Collision(fDeltaTime);
}

void UIPanel::Render(HDC hDC, float fDeltaTime)
{
    UIObj::Render(hDC, fDeltaTime);
}

UIPanel* UIPanel::Clone()
{
    return new UIPanel(*this);
}

#include "UIObj.h"

UIObj::UIObj()
{
}

UIObj::UIObj(const UIObj& ui)	:
	Obj(ui)
{
}

UIObj::~UIObj()
{
}

void UIObj::Input(float fDeltaTime)
{
	Obj::Input(fDeltaTime);
}

int UIObj::Update(float fDeltaTime)
{
	Obj::Update(fDeltaTime);
	return 0;
}

int UIObj::LateUpdate(float fDeltaTime)
{
	Obj::LateUpdate(fDeltaTime);
	return 0;
}

void UIObj::Collision(float fDeltaTime)
{
	Obj::Collision(fDeltaTime);
}

void UIObj::Render(HDC hDC, float fDeltaTime)
{
	Obj::Render(hDC, fDeltaTime);
}

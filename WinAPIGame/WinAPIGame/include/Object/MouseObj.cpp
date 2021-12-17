#include "MouseObj.h"
#include "../Core.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderPoint.h"

MouseObj::MouseObj()
{
}

MouseObj::MouseObj(const MouseObj& mouse)	:
	UIObj(mouse)
{
}

MouseObj::~MouseObj()
{
}

bool MouseObj::Init()
{
	POINT pt;
	
	GetCursorPos(&pt);
	ScreenToClient(WINDOWHANDLE, &pt);

	ShowCursor(TRUE);

	m_tClientPos = pt;

	POSITION tCamPos = GET_SINGLE(Camera)->GetPos();
	SetPos(m_tClientPos.x + tCamPos.x, m_tClientPos.y + tCamPos.y);

	ColliderPoint* pColl = AddCollider<ColliderPoint>("Mouse");
	SAFE_RELEASE(pColl);

	return true;
}

void MouseObj::Input(float fDeltaTime)
{
	UIObj::Input(fDeltaTime);
}

int MouseObj::Update(float fDeltaTime)
{
	UIObj::Update(fDeltaTime);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(WINDOWHANDLE, &pt);

	m_tClientPos = pt;

	POSITION tCamPos = GET_SINGLE(Camera)->GetPos();
	SetPos(m_tClientPos.x + tCamPos.x, m_tClientPos.y + tCamPos.y);

	return 0;
}

int MouseObj::LateUpdate(float fDeltaTime)
{
	UIObj::LateUpdate(fDeltaTime);
	return 0;
}

void MouseObj::Collision(float fDeltaTime)
{
	UIObj::Collision(fDeltaTime);
}

void MouseObj::Render(HDC hDC, float fDeltaTime)
{
	UIObj::Render(hDC, fDeltaTime);
}

MouseObj* MouseObj::Clone()
{
	return new MouseObj(*this);
}
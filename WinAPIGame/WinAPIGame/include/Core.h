#pragma once
#include "Game.h"
#include "Object/Obj.h"	// юс╫ц

class Core
{
private:
	static bool		m_bLoop;

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	Core();
	~Core();

private:
	BOOL Create();
	ATOM MyRegisterClass();

private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	HDC			m_hDC;
	RESOLUTION	m_tRS;

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);

	DECLARE_SINGLE(Core)
};


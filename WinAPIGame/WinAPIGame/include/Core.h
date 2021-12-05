#pragma once
#include "Game.h"

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

	DECLARE_SINGLE(Core)
};


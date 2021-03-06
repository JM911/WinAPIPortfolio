#pragma once
#include "Game.h"
#include "Object/Obj.h"	// 임시

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
	RESOLUTION	m_tWorldRS;

	// Get 함수
public:
	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}
	HWND GetWindowHandle()		const
	{
		return m_hWnd;
	}
	RESOLUTION GetResolution()	const
	{
		return m_tRS;
	}
	RESOLUTION GetWorldResolution()	const
	{
		return m_tWorldRS;
	}

	void DestroyGame()	// 게임 종료용
	{
		DestroyWindow(m_hWnd);
	}

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float fDeltaTime);
	SCENE_CHANGE Update(float fDeltaTime);
	SCENE_CHANGE LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);

	DECLARE_SINGLE(Core)
};


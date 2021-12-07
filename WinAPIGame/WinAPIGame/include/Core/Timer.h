#pragma once

#include "../Game.h"

class Timer
{
private:
	Timer();
	~Timer();

private:
	HWND			m_hWnd;
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTime;
	float m_fDeltaTime;
	float m_fTimeScale;
	float m_fFPS;
	float m_fFPSTime;
	float m_iFrame;

// Get 함수
public:
	float GetDeltaTime()	const
	{
		return m_fDeltaTime * m_fTimeScale;
	}
	float GetTimeScale()	const
	{
		return m_fTimeScale;
	}
	float GetFPS()			const
	{
		return m_fFPS;
	}

// Set 함수
public:
	void SetTimeScale(float fTimeScale)
	{
		m_fTimeScale = fTimeScale;
	}

public:
	bool Init(HWND hWnd);
	void Update();

	DECLARE_SINGLE(Timer)
};


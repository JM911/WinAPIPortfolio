#include "Timer.h"

DEFINITION_SINGLE(Timer)

Timer::Timer()	:
	m_fTimeScale(1.f)
{
}

Timer::~Timer()
{
}

bool Timer::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTime);

	m_fDeltaTime = 0.f;
	m_fFPS = 0.f;
	m_fFPSTime = 0.f;
	m_iFrame = 0;

	return true;
}

void Timer::Update()
{
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime);

	m_fDeltaTime = (tTime.QuadPart - m_tTime.QuadPart) / (float)m_tSecond.QuadPart;

	m_tTime = tTime;

	m_fFPSTime += m_fDeltaTime;
	++m_iFrame;

	if (m_fFPSTime >= 1.f)
	{
		m_fFPS = m_iFrame / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iFrame = 0;

		// TODO: 디버그 모드에서 프레임 출력하도록 처리
	}
}

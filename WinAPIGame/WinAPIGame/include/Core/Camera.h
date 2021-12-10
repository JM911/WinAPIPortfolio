#pragma once

#include "../Game.h"

class Camera
{
private:
	Camera();
	~Camera();

private:
	POSITION	m_tPos;
	RESOLUTION	m_tClientRS;
	RESOLUTION	m_tWorldRS;
	POSITION	m_tPivot;
	class Obj*	m_pTarget;

	// Get 함수
public:
	POSITION GetPos()	const
	{
		return m_tPos;
	}
	RESOLUTION GetClientRS()	const
	{
		return m_tClientRS;
	}

	// Set 함수
public:
	void SetPos(const POSITION& tPos)
	{
		m_tPos = tPos;
	}
	void SetPos(float x, float y)
	{
		m_tPos = POSITION(x, y);
	}
	void SetPivot(const POSITION& tPivot)
	{
		m_tPivot = tPivot;
	}
	void SetPivot(float x, float y)
	{
		m_tPivot = POSITION(x, y);
	}
	void SetClientResolution(const RESOLUTION& tRS)
	{
		m_tClientRS = tRS;
	}
	void SetClientResolution(int x, int y)
	{
		m_tClientRS = RESOLUTION(x, y);
	}
	void SetWolrdResolution(const RESOLUTION& tRS)
	{
		m_tWorldRS = tRS;
	}
	void SetWolrdResolution(int x, int y)
	{
		m_tWorldRS = RESOLUTION(x, y);
	}
	void SetTarget(class Obj* pObj);

public:
	bool Init(const POSITION& tPos, const RESOLUTION& tRS, const RESOLUTION& tWorldRS);
	void Input(float fDeltaTime);
	void Update(float fDeltaTime);
	void Scroll(float x, float y);

	DECLARE_SINGLE(Camera)
};


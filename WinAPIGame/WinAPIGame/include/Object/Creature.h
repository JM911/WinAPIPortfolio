#pragma once

#include "MoveObj.h"

class Creature	:
	public MoveObj
{
protected:
    Creature();
    Creature(const Creature& creature);
    ~Creature();

// TODO: HP, Die 등 생명체 오브젝트 공통요소 또는 함수 추가
private:
    bool    m_bStarted;

public:
    virtual bool Init() = 0;
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual MoveObj* Clone() = 0;
};


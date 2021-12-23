#pragma once

#include "MoveObj.h"

class Creature	:
	public MoveObj
{
protected:
    Creature();
    Creature(const Creature& creature);
    ~Creature();

// TODO: HP, Die �� ����ü ������Ʈ ������ �Ǵ� �Լ� �߰�
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


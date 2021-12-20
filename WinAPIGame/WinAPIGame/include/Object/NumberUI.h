#pragma once
#include "UIObj.h"

class NumberUI :
    public UIObj
{
private:
    friend class ScoreUI;

protected:
    NumberUI();
    NumberUI(const NumberUI& ui);
    ~NumberUI();

private:
    int m_iNum;

    // Get �Լ�
public:
    int GetNum()    const
    {
        return m_iNum;
    }

    // Set �Լ�
public:
    void SetNum(int iNum)
    {
        m_iNum = iNum;
        SetTextureByNum();
    }

private:
    void SetTextureByNum();

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);
    virtual NumberUI* Clone();
};


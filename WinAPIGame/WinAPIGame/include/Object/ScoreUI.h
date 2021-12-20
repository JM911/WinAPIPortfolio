#pragma once
#include "UIObj.h"

class ScoreUI :
    public UIObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    ScoreUI();
    ScoreUI(const ScoreUI& ui);
    ~ScoreUI();

private:
    static int m_iScore;
    class NumberUI* m_pNum1;
    class NumberUI* m_pNum2;

    // Get �Լ�
public:
    static int GetScore()
    {
        return m_iScore;
    }

    // Set �Լ�
public:
    static void SetScore(int iScore)
    {
        m_iScore = iScore;
    }
    
    // ��Ÿ �Լ�
public:
    static void AddScore(int iScore)
    {
        m_iScore += iScore;
    }

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);
    virtual ScoreUI* Clone();
};

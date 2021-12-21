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
    static int m_iPrevScore;
    class NumberUI* m_pNum1;
    class NumberUI* m_pNum2;

    // Get 함수
public:
    static int GetScore()
    {
        return m_iScore;
    }

    // Set 함수
public:
    static void SetScore(int iScore)
    {
        m_iScore = iScore;
    }
    static void SetPrevScore()
    {
        m_iPrevScore = m_iScore;
    }
    
    // 기타 함수
public:
    static void AddScore(int iScore)
    {
        m_iScore += iScore;
    }
    static void ReturnToPrevScore()
    {
        m_iScore = m_iPrevScore;
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


#pragma once
#include "StaticObj.h"

class Ground :
    public StaticObj
{
private:
    friend class Obj;
    friend class Scene;

protected:
    Ground();
    Ground(const Ground& ground);
    ~Ground();

protected:
    float m_fStartX;    // 땅 시작위치 x 좌표
    float m_fEndX;      // 땅 끝위치 x 좌표
    int m_iHeight;      // 월드 밑바닥부터의 높이

    // Set 함수
public:
    void SetGroundInfo(float fStartX, float fEndX, int iHeight);

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Ground* Clone();
};


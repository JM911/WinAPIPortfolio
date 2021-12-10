#pragma once
#include "StaticObj.h"

class TestBackground :
    public StaticObj
{
private:
    //friend class Obj;
    friend class Scene;

 public:    // TODO: 테스트 끝나면 protected로 수정
    TestBackground();
    TestBackground(const TestBackground& test);
    ~TestBackground();

public:
    virtual bool Init(POSITION tPos, _SIZE tSize, POSITION tPivot, const string& strBGName, const wchar_t* pBGFileName);
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual TestBackground* Clone();
};


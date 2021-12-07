#pragma once
#include "../Ref.h"

class Obj :
    public Ref
{
protected:
    friend class Core;  // 임시용이므로 나중에 삭제

protected:
    Obj();
    Obj(const Obj& obj);
    virtual ~Obj();

protected:
    POSITION    m_tPos;
    _SIZE       m_tSize;
    _SIZE       m_tImageOffset;
    POSITION    m_tPivot;

// Get 함수
public:
    POSITION GetPos()   const
    {
        return m_tPos;
    }

    _SIZE GetSize()     const
    {
        return m_tSize;
    }

    POSITION GetPivot() const
    {
        return m_tPivot;
    }

// Set 함수
public:
    void SetPos(const POSITION& tPos)
    {
        m_tPos = tPos;
    }
    void SetPos(const POINT& tPos)
    {
        m_tPos = tPos;
    }
    void SetPos(float x, float y)
    {
        m_tPos.x = x;
        m_tPos.y = y;
    }

    void SetSize(const _SIZE& tSize)
    {
        m_tSize = tSize;
    }
    void SetSize(float x, float y)
    {
        m_tSize.x = x;
        m_tSize.y = y;
    }

    void SetPivot(const POSITION& tPivot)
    {
        m_tPivot = tPivot;
    }
    void SetPivot(float x, float y)
    {
        m_tPivot.x = x;
        m_tPivot.y = y;
    }

    void SetImageOffset(const POSITION& tOffset)
    {
        m_tImageOffset = tOffset;
    }
    void SetImageOffset(float x, float y)
    {
        m_tImageOffset.x = x;
        m_tImageOffset.y = y;
    }

public:
    virtual bool Init() = 0;
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Obj* Clone() = 0;
};


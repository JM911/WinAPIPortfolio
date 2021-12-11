#pragma once
#include "../Ref.h"

class Collider :
    public Ref
{
protected:
    friend class Obj;

protected:
    Collider();
    Collider(const Collider& coll);
    virtual ~Collider() = 0;

protected:
    COL_TYPE        m_eColType;
    class Obj*      m_pObj;         // 이 충돌체를 들고 있는 오브젝트 객체 포인터
    list<Collider*> m_CollisionList;

    list<function<void(Collider*, Collider*, float)>> m_FuncList[static_cast<unsigned int>(COL_TYPE::END)];
    POSITION        m_tHitPoint;

    // Get 함수
public:
    COL_TYPE GetColliderType()  const
    {
        return m_eColType;
    }
    class Obj* GetObj()     const
    {
        return m_pObj;
    }
    POSITION GetHitPoint()  const
    {
        return m_tHitPoint;
    }

    // Set 함수
public:
    void SetObj(class Obj* pObj)
    {
        m_pObj = pObj;
    }
    void SetHitPoint(const POSITION& tPos)
    {
        m_tHitPoint = tPos;
    }

public:
    void AddCollisionFunction(COL_STATE eState, void (*pFunc)(Collider*, Collider*, float))
    {
        function<void(Collider*, Collider*, float)> func;

        func = bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3);

        m_FuncList[static_cast<unsigned int>(eState)].push_back(func);
    }

    template <typename T>
    void AddCollisionFunction(COL_STATE eState, T* pObj, void (T::* pFunc)(Collider*, Collider*, float))
    {
        function<void(Collider*, Collider*, float)> func;

        func = bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3);

        m_FuncList[static_cast<unsigned int>(eState)].push_back(func);
    }

    void CallFunction(COL_STATE eState, Collider* pDest, float fDeltaTime)
    {
        list<function<void(Collider*, Collider*, float)>>::iterator iter;
        list<function<void(Collider*, Collider*, float)>>::iterator iterEnd = m_FuncList[static_cast<unsigned int>(eState)].end();

        for (iter = m_FuncList[static_cast<unsigned int>(eState)].begin(); iter != iterEnd; ++iter)
        {
            (*iter)(this, pDest, fDeltaTime);
        }
    }

public:
    void AddCollider(Collider* pCollider)
    {
        m_CollisionList.push_back(pCollider);
    }

    bool CheckCollisionList(Collider* pCollider)
    {
        list<Collider*>::iterator iter;
        list<Collider*>::iterator iterEnd = m_CollisionList.end();

        for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
        {
            if (*iter == pCollider)
                return true;
        }

        return false;
    }

    void EraseCollisionList(Collider* pCollider)
    {
        list<Collider*>::iterator iter;
        list<Collider*>::iterator iterEnd = m_CollisionList.end();

        for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
        {
            if (*iter == pCollider)
            {
                m_CollisionList.erase(iter);
                break;
            }
        }
    }

public:
    virtual bool Init() = 0;
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual bool Collision(Collider* pDest);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Collider* Clone() = 0;

protected:
    bool CollisionRectToRect(const RECT& src, const RECT& dest, LPRECT pIntersect);
};


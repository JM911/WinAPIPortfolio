#pragma once
#include "../Ref.h"
#include "../Scene/Layer.h"

class Obj :
    public Ref
{
protected:
    friend class Core;  // 임시용이므로 나중에 삭제

protected:
    Obj();
    Obj(const Obj& obj);
    virtual ~Obj();

private:
    static list<Obj*>   m_ObjList;  // 실제 배치되는 놈들

public:
    static void AddObj(Obj* pObj);
    static Obj* FindObject(const string& strTag);
    static void EraseObj(Obj* pObj);
    static void EraseObj(const string& strTag);
    static void EraseObj();

protected:
    class Scene* m_pScene;      // 이 오브젝트 객체가 현재 들어가있는 씬
    class Layer* m_pLayer;      // 이 오브젝트 객체가 현재 들어가있는 레이어

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
    class Scene* GetScene() const
    {
        return m_pScene;
    }
    class Layer* GetLayer() const
    {
        return m_pLayer;
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

    void SetScene(class Scene* pScene)
    {
        m_pScene = pScene;
    }
    void SetLayer(class Layer* pLayer)
    {
        m_pLayer = pLayer;
    }

protected:
    class Texture* m_pTexture;
    class Animation* m_pAnimation;

public:
    void SetTexture(class Texture* pTexture);
    void SetTexture(const string& strKey, const wchar_t* pFileName = NULL, const string& strPathKey = TEXTURE_PATH);
    void SetColorKey(unsigned char r, unsigned char g, unsigned char b);

public:
    class Animation* CreateAnimation(const string& strTag);
    bool AddAnimationClipAtlas(const string& strName, ANI_OPTION eOption,
        float fAnimationLimitTime, int iMaxFrameX, int iTotalFrame, float fOptionLimitTime, _SIZE tFrameSize,
        const string& strTexKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
    bool AddAnimationClipFrame(const string& strName, ANI_OPTION eOption,
        float fAnimationLimitTime, int iMaxFrame, float fOptionLimitTime, _SIZE tFrameSize, const string& strTexKey,
        const vector<wstring>& vecFileName, const string& strPathKey = TEXTURE_PATH);
    void SetAnimationClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b);

public:
    virtual bool Init() = 0;
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual Obj* Clone() = 0;

public:
    template <typename T>
    static T* CreateObj(const string& strTag, class Layer* pLayer = NULL)
    {
        T* pObj = new T;

        pObj->SetTag(strTag);

        if (!pObj->Init())
        {
            SAFE_RELEASE(pObj);
            return NULL;
        }

        if (pLayer)
        {
            pLayer->AddObject(pObj);
        }

        AddObj(pObj);

        return pObj;
    }

    // static Obj* CreateCloneObj(const string& strPrototypeKey, const string& strTag, )
};


#pragma once
#include "../Ref.h"

class Animation :
    public Ref
{
private:
    friend class Obj;

private:
    Animation();
    Animation(const Animation& anim);
    ~Animation();

private:
    unordered_map<string, PANIMATIONCLIP>   m_mapClip;

private:
    PANIMATIONCLIP  m_pCurClip;         // ���� ���ư� Ŭ��
    string          m_strCurClip;           
    string          m_strDefaultClip;   // �⺻���� ���ư� Ŭ�� �̸�
    class Obj*      m_pObj;             // �ڽ��� ������ �ִ� ������Ʈ ��ü ������
    bool            m_bMotionEnd;       // �ִϸ��̼� �������� �������� üũ

    // Get �Լ�
public:
    bool GetMotionEnd() const
    {
        return m_bMotionEnd;
    }
    PANIMATIONCLIP GetCurrentClip() const
    {
        return m_pCurClip;
    }

    // Set �Լ�
public:
    void SetObj(class Obj* pObj)
    {
        m_pObj = pObj;
    }
    void SetClipColorKey(const string& strClip, unsigned char r, unsigned char g, unsigned char b);
    void SetCurrentClip(const string& strCurClip);
    void SetDefaultClip(const string& strDefaultClip);

public:
    void ChangeClip(const string& strClip);
    void ReturnClip();
    PANIMATIONCLIP FindClip(const string& strName);

private:
    // �� ��¥�� ��Ʋ�� Ÿ���� Ŭ�� �߰�
    bool AddClipAtlas(const string& strName, ANI_OPTION eOption,
        float fAnimationLimitTime, int iMaxFrameX, int iTotalFrame, float fOptionLimitTime, _SIZE tFrameSize,
        const string& strTexKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);

    // ���� ���� ���Ϸ� ������ ������ Ÿ���� Ŭ�� �߰�
    bool AddClipFrame(const string& strName, ANI_OPTION eOption,
        float fAnimationLimitTime, int iMaxFrame, float fOptionLimitTime, _SIZE tFrameSize, const string& strTexKey,
        const vector<wstring>& vecFileName, const string& strPathKey = TEXTURE_PATH);

public:
    bool Init();
    void Update(float fDeltaTime);
    Animation* Clone();
};


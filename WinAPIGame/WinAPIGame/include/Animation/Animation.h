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
    PANIMATIONCLIP  m_pCurClip;         // 현재 돌아갈 클립
    string          m_strCurClip;           
    string          m_strDefaultClip;   // 기본으로 돌아갈 클립 이름
    class Obj*      m_pObj;             // 자신을 가지고 있는 오브젝트 객체 포인터
    bool            m_bMotionEnd;       // 애니메이션 프레임이 끝났는지 체크

    // Get 함수
public:
    bool GetMotionEnd() const
    {
        return m_bMotionEnd;
    }
    PANIMATIONCLIP GetCurrentClip() const
    {
        return m_pCurClip;
    }

    // Set 함수
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
    // 한 장짜리 아틀라스 타입의 클립 추가
    bool AddClipAtlas(const string& strName, ANI_OPTION eOption,
        float fAnimationLimitTime, int iMaxFrameX, int iTotalFrame, float fOptionLimitTime, _SIZE tFrameSize,
        const string& strTexKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);

    // 여러 장의 파일로 구성된 프레임 타입의 클립 추가
    bool AddClipFrame(const string& strName, ANI_OPTION eOption,
        float fAnimationLimitTime, int iMaxFrame, float fOptionLimitTime, _SIZE tFrameSize, const string& strTexKey,
        const vector<wstring>& vecFileName, const string& strPathKey = TEXTURE_PATH);

public:
    bool Init();
    void Update(float fDeltaTime);
    Animation* Clone();
};


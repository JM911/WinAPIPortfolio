#pragma once
#include "../Ref.h"

class Texture :
    public Ref
{
private:
    friend class ResourcesManager;

private:
    Texture();
    ~Texture();

private:
    HDC         m_hMemDC;       
    HBITMAP     m_hBitmap;      // 비트맵을 컨트롤하기 위한 핸들
    HBITMAP     m_hOldBitmap;   // 이전 비트맵 핸들을 보관 (메모리 해제를 위해 필수)
    BITMAP      m_tInfo;        // 비트맵 정보
    
    COLORREF    m_ColorKey;     // TransparentBlt, 픽셀 충돌을 위한 컬러키
    bool        m_bColorKeyEnable;

    /* 아래 3개는 스테이지 저장용 변수인 것 같아서 일단 생략 */
    //wstring     m_strFileName;      // 비트맵 파일 이름
    //string      m_strKey;           // 코드 내에서 해당 텍스쳐에 붙여주는 key(이름)
    //string      m_strPathKey;       // 비트맵 파일 경로

    // Get 함수
public:
    COLORREF GetColorKey()  const
    {
        return m_ColorKey;
    }
    bool GetColorKeyEnable()    const
    {
        return m_bColorKeyEnable;
    }
    long GetWidth()     const
    {
        return m_tInfo.bmWidth;
    }
    long GetHeight()    const
    {
        return m_tInfo.bmHeight;
    }
    HDC GetDC()     const
    {
        return m_hMemDC;
    }

    // Set 함수
public:
    void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
    void SetColorKey(COLORREF colorKey);

public:
    bool LoadTexture(HINSTANCE hInst, HDC hDC, const string& strKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
};


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
    HBITMAP     m_hBitmap;      // ��Ʈ���� ��Ʈ���ϱ� ���� �ڵ�
    HBITMAP     m_hOldBitmap;   // ���� ��Ʈ�� �ڵ��� ���� (�޸� ������ ���� �ʼ�)
    BITMAP      m_tInfo;        // ��Ʈ�� ����
    
    COLORREF    m_ColorKey;     // TransparentBlt, �ȼ� �浹�� ���� �÷�Ű
    bool        m_bColorKeyEnable;

    /* �Ʒ� 3���� �������� ����� ������ �� ���Ƽ� �ϴ� ���� */
    //wstring     m_strFileName;      // ��Ʈ�� ���� �̸�
    //string      m_strKey;           // �ڵ� ������ �ش� �ؽ��Ŀ� �ٿ��ִ� key(�̸�)
    //string      m_strPathKey;       // ��Ʈ�� ���� ���

    // Get �Լ�
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

    // Set �Լ�
public:
    void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
    void SetColorKey(COLORREF colorKey);

public:
    bool LoadTexture(HINSTANCE hInst, HDC hDC, const string& strKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
};


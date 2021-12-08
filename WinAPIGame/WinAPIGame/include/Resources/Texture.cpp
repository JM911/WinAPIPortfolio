#include "Texture.h"
#include "../Core/PathManager.h"

Texture::Texture()	:
	m_hMemDC(NULL),
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255, 0, 255))	// �÷�Ű �⺻���� ����Ÿ �������� ����
{
}

Texture::~Texture()
{
	SelectObject(m_hMemDC, m_hOldBitmap);	// ������ �����Ǿ� �ִ� �ڵ�� ������
	DeleteObject(m_hBitmap);				// ������ ����� �ڵ� ����
	DeleteDC(m_hMemDC);						// DC ����
}

void Texture::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_ColorKey = RGB(r, g, b);
	m_bColorKeyEnable = true;
}

void Texture::SetColorKey(COLORREF colorKey)
{
	m_ColorKey = colorKey;
	m_bColorKeyEnable = true;
}

bool Texture::LoadTexture(HINSTANCE hInst, HDC hDC, const string& strKey, const wchar_t* pFileName, const string& strPathKey)
{
	// �޸� DC�� ������ش�
	m_hMemDC = CreateCompatibleDC(hDC);	// ���ڷ� ȭ�� DC�� �־��ָ� �ش� ȭ�� DC�� �޸� DC�� �����Ѵ�.

	// ��ü ��θ� ������ش�
	const wchar_t* pPath = GET_SINGLE(PathManager)->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);	// ��Ʈ���� ������ �� m_tInfo�� ������ ���´�.

	return true;
}

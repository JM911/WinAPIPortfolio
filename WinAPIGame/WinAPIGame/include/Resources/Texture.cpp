#include "Texture.h"
#include "../Core/PathManager.h"

Texture::Texture()	:
	m_hMemDC(NULL),
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255, 0, 255))	// 컬러키 기본값은 마젠타 색상으로 설정
{
}

Texture::~Texture()
{
	SelectObject(m_hMemDC, m_hOldBitmap);	// 기존에 지정되어 있던 핸들로 재지정
	DeleteObject(m_hBitmap);				// 지정이 사라진 핸들 삭제
	DeleteDC(m_hMemDC);						// DC 삭제
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
	// 메모리 DC를 만들어준다
	m_hMemDC = CreateCompatibleDC(hDC);	// 인자로 화면 DC를 넣어주면 해당 화면 DC용 메모리 DC를 생성한다.

	// 전체 경로를 만들어준다
	const wchar_t* pPath = GET_SINGLE(PathManager)->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);	// 비트맵의 정보를 얻어서 m_tInfo에 저장해 놓는다.

	return true;
}

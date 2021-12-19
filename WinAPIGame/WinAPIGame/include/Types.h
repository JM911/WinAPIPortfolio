#pragma once
#include "Flag.h"

typedef struct _tagResolution
{
	unsigned int iW;
	unsigned int iH;

	_tagResolution() :
		iW(0),
		iH(0)
	{

	}

	_tagResolution(int x, int y) :
		iW(x),
		iH(y)
	{

	}

}RESOLUTION, *PRESOLUTION;

typedef struct _tagPosition
{
	float x, y;

	// 생성자 오버로딩
	_tagPosition()	:
		x(0.f),
		y(0.f)
	{

	}

	_tagPosition(float _x, float _y) :
		x(_x),
		y(_y)
	{

	}

	// =연산자 오버로딩
	void operator= (const _tagPosition& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	void operator= (const POINT& pt)
	{
		x = (float)pt.x;
		y = (float)pt.y;
	}

	// TODO?: 사칙연산 오버로딩

}POSITION, *PPOSITION, _SIZE, *_PSIZE;

// TODO: 애니메이션 클립을 아틀라스/프레임 두 개로 아예 나눠버릴까?
typedef struct _tagAnimationClip		// 모션 하나를 저장하는 역할 (구조체 1개 = 모션 1개)
{
	ANI_TYPE		eType;
	ANI_OPTION		eOption;
	vector<class Texture*>	vecTexture;	// 프레임 애니메이션이라면 여러 장 push
	
	// 애니메이션의 속도 조절용
	float			fAnimationTime;
	float			fAnimationLimitTime;
	float			fAnimationFrameTime;
	
	// 아틀라스 타입인 경우 사용
	int				iCurFrameX;
	int				iCurFrameY;
	int				iMaxFrameX;
	int				iMaxFrameY;
	//int				iStartFrameX;
	//int				iStartFrameY;
	int				iTotalFrame;
	
	// 애니메이션 옵션에 따라 사용할 수도 있는 변수
	float			fOptionTime;
	float			fOptionLimitTime;

	// 출력에 쓰일 프레임 사이즈, 프레임 간격
	_SIZE			tFrameSize;			// 실제 출력할 그림 크기
	_SIZE			tFrameInterval;		// 그림 간의 간격
}ANIMATIONCLIP, *PANIMATIONCLIP;

//typedef struct _tagRectangle
//{
//	float l;
//	float t;
//	float r;
//	float b;
//
//	_tagRectangle() :
//		l(0.f),
//		t(0.f),
//		r(0.f),
//		b(0.f)
//	{ }
//}RECTANGLE, *PRECTANGLE;

typedef struct _tagCircle
{
	POSITION	tCenter;
	float		fRadius;

	_tagCircle()	:
		tCenter(0.f, 0.f),
		fRadius(0.f)
	{ }
}CIRCLE, *PCIRCLE;
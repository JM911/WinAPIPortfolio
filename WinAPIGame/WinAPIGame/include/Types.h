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

	// ������ �����ε�
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

	// =������ �����ε�
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

	// TODO?: ��Ģ���� �����ε�

}POSITION, *PPOSITION, _SIZE, *_PSIZE;

// TODO: �ִϸ��̼� Ŭ���� ��Ʋ��/������ �� ���� �ƿ� ����������?
typedef struct _tagAnimationClip		// ��� �ϳ��� �����ϴ� ���� (����ü 1�� = ��� 1��)
{
	ANI_TYPE		eType;
	ANI_OPTION		eOption;
	vector<class Texture*>	vecTexture;	// ������ �ִϸ��̼��̶�� ���� �� push
	
	// �ִϸ��̼��� �ӵ� ������
	float			fAnimationTime;
	float			fAnimationLimitTime;
	float			fAnimationFrameTime;
	
	// ��Ʋ�� Ÿ���� ��� ���
	int				iCurFrameX;
	int				iCurFrameY;
	int				iMaxFrameX;
	int				iMaxFrameY;
	//int				iStartFrameX;
	//int				iStartFrameY;
	int				iTotalFrame;
	
	// �ִϸ��̼� �ɼǿ� ���� ����� ���� �ִ� ����
	float			fOptionTime;
	float			fOptionLimitTime;

	// ��¿� ���� ������ ������, ������ ����
	_SIZE			tFrameSize;			// ���� ����� �׸� ũ��
	_SIZE			tFrameInterval;		// �׸� ���� ����
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
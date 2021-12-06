#pragma once

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
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
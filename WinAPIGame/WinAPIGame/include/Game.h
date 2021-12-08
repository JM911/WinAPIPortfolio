#pragma once

#include <Windows.h>
#include <crtdbg.h>			// 메모리 누수 체크
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <typeinfo>			// 타입.name() 함수 사용

using namespace std;

#include "Macro.h"
#include "resource.h"
#include "Types.h"

#pragma comment(lib, "msimg32")		// 정적 라이브러리를 포함시켜주는 코드

// Path Key
#define ROOT_PATH		"RootPath"
#define TEXTURE_PATH	"TexturePath"

template <typename T>
void Safe_Delete_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	p.clear();
}

template <typename T>
void Safe_Release_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE((*iter));
	}

	p.clear();
}

template <typename T>
void Safe_Delete_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	p.clear();
}

template <typename T>
void Safe_Release_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE(iter->second);
	}

	p.clear();
}
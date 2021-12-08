#pragma once

#include "../Game.h"

typedef struct _tagKeyInfo
{
	string			strName;
	vector<DWORD>	vecKey;		// 누르는 키 정보 저장(여러 개일 수 있으므로 벡터로 저장)
	bool			bDown;		// 키를 누른 직후
	bool			bPress;		// 키를 누르고 있는 도중
	bool			bUp;		// 키를 뗀 직후

	_tagKeyInfo() :
		bDown(false),
		bPress(false),
		bUp(false)
	{ }
}KEYINFO, *PKEYINFO;

class CInput
{
private:
	CInput();
	~CInput();

	// TODO: 마우스 관련 변수, 함수 추가
private:
	// HWND hWnd;		// FW에는 있지만 사용처가 없어서 뺌. 나중에 추가하면 Init 함수 인자로도 추가.
	unordered_map<string, PKEYINFO>	m_mapKey;
	PKEYINFO	m_pCreateKey;

public:
	bool Init();
	void Update(float fDeltaTime);

public:		// 맵핑된 키의 상태를 확인하는 함수
	bool KeyDown(const string& strKey)	const;
	bool KeyPress(const string& strKey)	const;
	bool KeyUp(const string& strKey)	const;

public:
	template <typename T>
	bool AddKey(const T& data)
	{
		const char* pTType = typeid(T).name();	// 자료형 이름을 문자열로 반환

		if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)	// char 또는 int형이면 키보드의 키값이 들어왔다는 것
		{
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}

		else	// char, int 형이 아닌 다른 자료형이면 map의 키값을 입력한 것으로 인식
		{
			m_pCreateKey->strName = data;
			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}

		return true;
	}

	template <typename T, typename ... Types>		// 가변인자 템플릿(C++11 문법)
	bool AddKey(const T& data, const Types& ...arg)
	{
		if (!m_pCreateKey)
			m_pCreateKey = new KEYINFO;

		const char* pTType = typeid(T).name();	// 자료형 이름을 문자열로 반환

		if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)	// char 또는 int형이면 키보드의 키값이 들어왔다는 것
		{
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}

		else	// char, int 형이 아닌 다른 자료형이면 map의 키값을 입력한 것으로 인식
		{
			m_pCreateKey->strName = data;
			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}

		AddKey(arg...);

		if (m_pCreateKey)
			m_pCreateKey = NULL;

		return true;
	}

private:
	PKEYINFO FindKey(const string& strKey)	const;

	DECLARE_SINGLE(CInput)
};


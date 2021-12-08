#pragma once

#include "../Game.h"

typedef struct _tagKeyInfo
{
	string			strName;
	vector<DWORD>	vecKey;		// ������ Ű ���� ����(���� ���� �� �����Ƿ� ���ͷ� ����)
	bool			bDown;		// Ű�� ���� ����
	bool			bPress;		// Ű�� ������ �ִ� ����
	bool			bUp;		// Ű�� �� ����

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

	// TODO: ���콺 ���� ����, �Լ� �߰�
private:
	// HWND hWnd;		// FW���� ������ ���ó�� ��� ��. ���߿� �߰��ϸ� Init �Լ� ���ڷε� �߰�.
	unordered_map<string, PKEYINFO>	m_mapKey;
	PKEYINFO	m_pCreateKey;

public:
	bool Init();
	void Update(float fDeltaTime);

public:		// ���ε� Ű�� ���¸� Ȯ���ϴ� �Լ�
	bool KeyDown(const string& strKey)	const;
	bool KeyPress(const string& strKey)	const;
	bool KeyUp(const string& strKey)	const;

public:
	template <typename T>
	bool AddKey(const T& data)
	{
		const char* pTType = typeid(T).name();	// �ڷ��� �̸��� ���ڿ��� ��ȯ

		if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)	// char �Ǵ� int���̸� Ű������ Ű���� ���Դٴ� ��
		{
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}

		else	// char, int ���� �ƴ� �ٸ� �ڷ����̸� map�� Ű���� �Է��� ������ �ν�
		{
			m_pCreateKey->strName = data;
			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}

		return true;
	}

	template <typename T, typename ... Types>		// �������� ���ø�(C++11 ����)
	bool AddKey(const T& data, const Types& ...arg)
	{
		if (!m_pCreateKey)
			m_pCreateKey = new KEYINFO;

		const char* pTType = typeid(T).name();	// �ڷ��� �̸��� ���ڿ��� ��ȯ

		if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)	// char �Ǵ� int���̸� Ű������ Ű���� ���Դٴ� ��
		{
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}

		else	// char, int ���� �ƴ� �ٸ� �ڷ����̸� map�� Ű���� �Է��� ������ �ν�
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


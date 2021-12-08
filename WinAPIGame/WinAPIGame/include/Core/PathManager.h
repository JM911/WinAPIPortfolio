#pragma once

#include "../Game.h"

class PathManager
{
private:
	PathManager();
	~PathManager();

private:
	unordered_map<string, wstring> m_mapPath;
	char m_strPath[MAX_PATH];

public:
	bool Init();
	bool CreatePath(const string& strKey, const wchar_t* pPath, const string& strBaseKey = ROOT_PATH);
	const wchar_t* FindPath(const string& strKey);			// �����ڵ�
	const char* FindPathByMultiByte(const string& strKey);	// ��Ƽ����Ʈ

	DECLARE_SINGLE(PathManager)
};


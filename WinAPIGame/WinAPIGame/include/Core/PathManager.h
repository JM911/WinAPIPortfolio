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
	const wchar_t* FindPath(const string& strKey);			// 유니코드
	const char* FindPathByMultiByte(const string& strKey);	// 멀티바이트

	DECLARE_SINGLE(PathManager)
};


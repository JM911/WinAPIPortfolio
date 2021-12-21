#include "PathManager.h"

DEFINITION_SINGLE(PathManager)

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

bool PathManager::Init()
{
    wchar_t strPath[MAX_PATH] = {};

    GetModuleFileName(NULL, strPath, MAX_PATH);

    for (int i = lstrlen(strPath) - 1; i >= 0; --i)
    {
        if (strPath[i] == '/' || strPath[i] == '\\')
        {
            memset(strPath + (i + 1), 0, sizeof(wchar_t) * (MAX_PATH - (i + 1)));       // 뭔지 이해 못했는데 일단 적음
            break;
        }
    }

    m_mapPath.insert(make_pair(ROOT_PATH, strPath));

    // 텍스쳐 경로 설정
    if (!CreatePath(TEXTURE_PATH, L"Texture/"))
        return false;

    // 배경 경로 설정
    if (!CreatePath(BACKGROUND_PATH, L"Texture/Backgrounds/"))
        return false;

    // 사운드 경로 설정
    if (!CreatePath(SOUND_PATH, L"Sound/"))
        return false;

    return true;
}

bool PathManager::CreatePath(const string& strKey, const wchar_t* pPath, const string& strBaseKey)
{
    const wchar_t* pBasePath = FindPath(strBaseKey);

    wstring strPath;

    if (pBasePath)
        strPath = pBasePath;

    strPath += pPath;

    m_mapPath.insert(make_pair(strKey, strPath));

    return true;
}

const wchar_t* PathManager::FindPath(const string& strKey)
{
    unordered_map<string, wstring>::iterator iter = m_mapPath.find(strKey);

    if (iter == m_mapPath.end())
        return NULL;

    return iter->second.c_str();
}

const char* PathManager::FindPathByMultiByte(const string& strKey)
{
    const wchar_t* pPath = FindPath(strKey);

    if (!pPath)
        return NULL;

    memset(m_strPath, 0, sizeof(char) * MAX_PATH);

    // 유니코드를 멀티바이트로 변환하는 함수
    WideCharToMultiByte(CP_ACP, 0, pPath, -1, m_strPath, lstrlen(pPath), 0, 0);

    return m_strPath;
}

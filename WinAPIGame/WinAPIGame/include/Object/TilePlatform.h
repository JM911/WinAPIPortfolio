#pragma once
#include "StaticObj.h"

class TilePlatform :
    public StaticObj
{
private:
    friend class Obj;

protected:
    TilePlatform();
    TilePlatform(const TilePlatform& tilePlatform);
    virtual ~TilePlatform();

private:
    vector<class Tile*> m_vecTile;
    string m_strTileKey;
    wstring m_wstrTileTexFileName;
    bool m_bTileSetting;

    // Set ÇÔ¼ö
public:
    void SetTileTexture(const string& strKey, const wchar_t* pFileName);
    void SetPlatform(POSITION tPos, int iTileNumX, int iTileNumY);

public:
    virtual bool Init();
    virtual void Input(float fDeltaTime);
    virtual int Update(float fDeltaTime);
    virtual int LateUpdate(float fDeltaTime);
    virtual void Collision(float fDeltaTime);
    virtual void Render(HDC hDC, float fDeltaTime);

    virtual TilePlatform* Clone();
};


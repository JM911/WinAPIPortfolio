#include "TilePlatform.h"
#include "Tile.h"
#include "../Collider/ColliderRect.h"

TilePlatform::TilePlatform()
{
}

TilePlatform::TilePlatform(const TilePlatform& tilePlatform)	:
	StaticObj(tilePlatform)
{
	m_vecTile.clear();

	for (size_t i = 0; i < tilePlatform.m_vecTile.size(); ++i)
	{
		m_vecTile.push_back(tilePlatform.m_vecTile[i]->Clone());
	}
}

TilePlatform::~TilePlatform()
{
	Safe_Release_VecList(m_vecTile);
}

bool TilePlatform::Init()
{
	return true;
}

bool TilePlatform::Init(POSITION tPos, int iTileNumX, int iTileNumY)
{
	SetPos(tPos);
	SetSize((float)(32 * iTileNumX), (float)(32 * iTileNumY));

	for (int i = 0; i < iTileNumX; ++i)
	{
		for (int j = 0; j < iTileNumY; ++j)
		{
			Tile* pTile = new Tile;
			pTile->Init();
			pTile->SetPos(tPos.x + 1 + i * 32, tPos.y + 1 + j * 32);
			m_vecTile.push_back(pTile);
		}
	}

	ColliderRect* pRC = AddCollider<ColliderRect>("PlatformBody");
	pRC->SetRect(0, 0, (int)m_tSize.x, (int)m_tSize.y);
	SAFE_RELEASE(pRC);

	return true;
}

void TilePlatform::Input(float fDeltaTime)
{
	StaticObj::Input(fDeltaTime);
}

int TilePlatform::Update(float fDeltaTime)
{
	StaticObj::Update(fDeltaTime);
	return 0;
}

int TilePlatform::LateUpdate(float fDeltaTime)
{
	StaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void TilePlatform::Collision(float fDeltaTime)
{
	StaticObj::Collision(fDeltaTime);
}

void TilePlatform::Render(HDC hDC, float fDeltaTime)
{
	StaticObj::Render(hDC, fDeltaTime);

	vector<Tile*>::iterator iter;
	vector<Tile*>::iterator iterEnd = m_vecTile.end();

	for (iter = m_vecTile.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render(hDC, fDeltaTime);
	}
}

TilePlatform* TilePlatform::Clone()
{
	return new TilePlatform(*this);
}

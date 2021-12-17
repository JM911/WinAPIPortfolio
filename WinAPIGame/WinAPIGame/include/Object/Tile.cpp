#include "Tile.h"
#include "../Core/Camera.h"

Tile::Tile()
{
}

Tile::Tile(const Tile& tile)    :
    StaticObj(tile)
{
}

Tile::~Tile()
{
}

bool Tile::Init()
{
    SetSize(32, 32);
    SetTexture("BaseTile", L"Platform/Tiles/1.bmp");

    return true;
}

void Tile::Input(float fDeltaTime)
{
    StaticObj::Input(fDeltaTime);
}

int Tile::Update(float fDeltaTime)
{
    StaticObj::Update(fDeltaTime);
    return 0;
}

int Tile::LateUpdate(float fDeltaTime)
{
    StaticObj::LateUpdate(fDeltaTime);
    return 0;
}

void Tile::Collision(float fDeltaTime)
{
    StaticObj::Collision(fDeltaTime);
}

void Tile::Render(HDC hDC, float fDeltaTime)
{
    StaticObj::Render(hDC, fDeltaTime);
}

Tile* Tile::Clone()
{
    return new Tile(*this);
}

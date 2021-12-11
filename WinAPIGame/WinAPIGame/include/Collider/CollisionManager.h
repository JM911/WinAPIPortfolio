#pragma once
#include "../Game.h"

class CollisionManager
{
private:
	CollisionManager();
	~CollisionManager();

private:
	list<class Obj*>	m_CollisionList;

public:
	void AddObj(class Obj* pObj);
	void Collision(float fDeltaTime);
	bool Collision(class Obj* pSrc, class Obj* pDest, float fDeltaTime);
	void Clear();

	DECLARE_SINGLE(CollisionManager)
};


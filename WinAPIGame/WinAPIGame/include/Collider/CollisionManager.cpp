#include "CollisionManager.h"
#include "../Object/Obj.h"

DEFINITION_SINGLE(CollisionManager)

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::AddObj(Obj* pObj)
{
    if (pObj->CheckCollider())
    {
        m_CollisionList.push_back(pObj);
    }
}

void CollisionManager::Collision(float fDeltaTime)
{
    if (m_CollisionList.size() < 2)
    {
        m_CollisionList.clear();
        return;
    }

    list<Obj*>::iterator iter_1;
    list<Obj*>::iterator iterEnd_1 = m_CollisionList.end();
    --iterEnd_1;

    for (iter_1 = m_CollisionList.begin(); iter_1 != iterEnd_1; ++iter_1)
    {
        list<Obj*>::iterator iter_2 = iter_1;
        ++iter_2;
        list<Obj*>::iterator iterEnd_2 = m_CollisionList.end();

        for (; iter_2 != iterEnd_2; ++iter_2)
        {
            Collision(*iter_1, *iter_2, fDeltaTime);
        }
    }

    m_CollisionList.clear();        // 클리어를 매번 하는 이유?
}

bool CollisionManager::Collision(Obj* pSrc, Obj* pDest, float fDeltaTime)
{
    const list<Collider*>* pSrcList     = pSrc->GetColliderList();
    const list<Collider*>* pDestList    = pDest->GetColliderList();

    list<Collider*>::const_iterator iterSrc;
    list<Collider*>::const_iterator iterSrcEnd = pSrcList->end();

    list<Collider*>::const_iterator iterDest;
    list<Collider*>::const_iterator iterDestEnd = pDestList->end();

    bool bCollision = false;

    for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc)
    {
        for (iterDest = pDestList->begin(); iterDest != iterDestEnd; ++iterDest)
        {
            if ((*iterSrc)->Collision(*iterDest))
            {
                bCollision = true;

                // Dest의 HitPoint도 만들어줌
                (*iterDest)->SetHitPoint((*iterSrc)->GetHitPoint());

                // 충돌 목록에서 이전에 충돌된 적이 없다면 처음 막 충돌했다는 뜻
                if (!(*iterSrc)->CheckCollisionList(*iterDest))
                {
                    // 서로 상대방을 충돌 목록으로 추가한다.
                    (*iterSrc)->AddCollider(*iterDest);
                    (*iterDest)->AddCollider(*iterSrc);

                    (*iterSrc)->CallFunction(COL_STATE::ENTER, *iterDest, fDeltaTime);
                    (*iterDest)->CallFunction(COL_STATE::ENTER, *iterSrc, fDeltaTime);
                }

                // 기존에 충돌된 적이 있다면 계속 충돌 상태인 것이다.
                else
                {
                    (*iterSrc)->CallFunction(COL_STATE::STAY, *iterDest, fDeltaTime);
                    (*iterDest)->CallFunction(COL_STATE::STAY, *iterSrc, fDeltaTime);
                }
            }

            // 현재는 충돌이 아니지만 이전까지 충돌이 되고 있었다면 이제 막 충돌 상태에서 벗어났다는 것이다.
            else if ((*iterSrc)->CheckCollisionList(*iterDest))
            {
                // 서로 충돌 목록에서 제거한다.
                (*iterSrc)->EraseCollisionList(*iterDest);
                (*iterDest)->EraseCollisionList(*iterSrc);

                (*iterSrc)->CallFunction(COL_STATE::LEAVE, *iterDest, fDeltaTime);
                (*iterDest)->CallFunction(COL_STATE::LEAVE, *iterSrc, fDeltaTime);
            }
        }
    }

    return bCollision;
}

void CollisionManager::Clear()
{
    m_CollisionList.clear();
}

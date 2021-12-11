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

    m_CollisionList.clear();        // Ŭ��� �Ź� �ϴ� ����?
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

                // Dest�� HitPoint�� �������
                (*iterDest)->SetHitPoint((*iterSrc)->GetHitPoint());

                // �浹 ��Ͽ��� ������ �浹�� ���� ���ٸ� ó�� �� �浹�ߴٴ� ��
                if (!(*iterSrc)->CheckCollisionList(*iterDest))
                {
                    // ���� ������ �浹 ������� �߰��Ѵ�.
                    (*iterSrc)->AddCollider(*iterDest);
                    (*iterDest)->AddCollider(*iterSrc);

                    (*iterSrc)->CallFunction(COL_STATE::ENTER, *iterDest, fDeltaTime);
                    (*iterDest)->CallFunction(COL_STATE::ENTER, *iterSrc, fDeltaTime);
                }

                // ������ �浹�� ���� �ִٸ� ��� �浹 ������ ���̴�.
                else
                {
                    (*iterSrc)->CallFunction(COL_STATE::STAY, *iterDest, fDeltaTime);
                    (*iterDest)->CallFunction(COL_STATE::STAY, *iterSrc, fDeltaTime);
                }
            }

            // ����� �浹�� �ƴ����� �������� �浹�� �ǰ� �־��ٸ� ���� �� �浹 ���¿��� ����ٴ� ���̴�.
            else if ((*iterSrc)->CheckCollisionList(*iterDest))
            {
                // ���� �浹 ��Ͽ��� �����Ѵ�.
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

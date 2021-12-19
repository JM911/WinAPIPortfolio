#include "CInput.h"
#include "../Object/Obj.h"
#include "../Object/MouseObj.h"
#include "../Collider/CollisionManager.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()    :
    m_pCreateKey(NULL)
{
}

CInput::~CInput()
{
    Obj::EraseObj(m_pMouse);
    SAFE_RELEASE(m_pMouse);
    Safe_Delete_Map(m_mapKey);
}

bool CInput::Init()
{
    // TODO: AddKey�� ���� ���ϴ� Ű ����
    // �⺻ ������
    AddKey("MoveLeft", VK_LEFT);
    AddKey("MoveRight", VK_RIGHT);
    AddKey("Jump", 'C');

    // 4���� ���
    AddKey("DashLeft", VK_LEFT, 'X');
    AddKey("DashRight", VK_RIGHT, 'X');
    AddKey("DashUp", VK_UP, 'X');
    AddKey("DashDown", VK_DOWN, 'X');

    // �����
    AddKey("WallCliff", 'Z');
    AddKey("WallCliffUp", VK_UP, 'Z');
    AddKey("WallCliffDown", VK_DOWN, 'Z');

    // ���콺 ��ư
    AddKey("MouseLClick", VK_LBUTTON);
    AddKey("MouseRClick", VK_RBUTTON);

    // ���콺 ����
    m_pMouse = Obj::CreateObj<MouseObj>("Mouse");

    // TODO: (���콺 Ŀ�� �̹��� �ٲٰ� ���� ���) ���콺 �ؽ�ó or �ִϸ��̼� ���� �۾�

    return true;
}

void CInput::Update(float fDeltaTime)
{
    unordered_map<string, PKEYINFO>::iterator iter;
    unordered_map<string, PKEYINFO>::iterator iterEnd = m_mapKey.end();

    for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
    {
        int iPushCount = 0;
        for (size_t i = 0; i < iter->second->vecKey.size(); ++i)
        {
            if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
                iPushCount++;
        }

        if (iPushCount == iter->second->vecKey.size())       // �ʿ� ¥���� Ű�� ��� ���ȴٰ� �Ǵܵ� ��
        {
            if (!iter->second->bDown && !iter->second->bPress)   // �� �� false��� ���� �ִٰ� ó�� �����ٴ� ��
            {
                iter->second->bDown = true;
                iter->second->bPress = true;
            }

            else if (iter->second->bDown)        // bDown�� true��� ���� ������ �̹� ������ �־��ٴ� ��
                iter->second->bDown = false;
        }

        else    // ���ε� Ű�� ������ �ʾ��� ��
        {  
            if (iter->second->bDown || iter->second->bPress)        // �������� �ʾҴµ� �� �� �ϳ��� true��� ���� ������ ������ �־��ٴ� ��
            {
                iter->second->bUp = true;
                iter->second->bDown = false;
                iter->second->bPress = false;
            }

            else if (iter->second->bUp)     // ���� ������ bUp�� ���� ������ �̹� �����ߴٸ�
            {
                iter->second->bUp = false;
            }
        }
    }

    m_pMouse->Update(fDeltaTime);
    m_pMouse->LateUpdate(fDeltaTime);

    GET_SINGLE(CollisionManager)->AddObj(m_pMouse);
}

bool CInput::KeyDown(const string& strKey) const
{
    PKEYINFO pInfo = FindKey(strKey);

    if (!pInfo)
        return false;

    return pInfo->bDown;
}

bool CInput::KeyPress(const string& strKey) const
{
    PKEYINFO pInfo = FindKey(strKey);

    if (!pInfo)
        return false;

    return pInfo->bPress;
}

bool CInput::KeyUp(const string& strKey) const
{
    PKEYINFO pInfo = FindKey(strKey);

    if (!pInfo)
        return false;

    return pInfo->bUp;
}

PKEYINFO CInput::FindKey(const string& strKey) const
{
    unordered_map<string, PKEYINFO>::const_iterator iter = m_mapKey.find(strKey);

    if (iter == m_mapKey.end())
        return NULL;
    
    return iter->second;
}

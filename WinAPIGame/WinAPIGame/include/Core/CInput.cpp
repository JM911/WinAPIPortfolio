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
    // TODO: AddKey를 통해 원하는 키 맵핑
    // 기본 움직임
    AddKey("MoveLeft", VK_LEFT);
    AddKey("MoveRight", VK_RIGHT);
    AddKey("Jump", 'C');

    // 4방향 대시
    AddKey("DashLeft", VK_LEFT, 'X');
    AddKey("DashRight", VK_RIGHT, 'X');
    AddKey("DashUp", VK_UP, 'X');
    AddKey("DashDown", VK_DOWN, 'X');

    // 벽잡기
    AddKey("WallCliff", 'Z');
    AddKey("WallCliffUp", VK_UP, 'Z');
    AddKey("WallCliffDown", VK_DOWN, 'Z');

    // 마우스 버튼
    AddKey("MouseLClick", VK_LBUTTON);
    AddKey("MouseRClick", VK_RBUTTON);

    // 마우스 생성
    m_pMouse = Obj::CreateObj<MouseObj>("Mouse");

    // TODO: (마우스 커서 이미지 바꾸고 싶은 경우) 마우스 텍스처 or 애니메이션 관련 작업

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

        if (iPushCount == iter->second->vecKey.size())       // 맵에 짜여진 키가 모두 눌렸다고 판단될 때
        {
            if (!iter->second->bDown && !iter->second->bPress)   // 둘 다 false라면 떼고 있다가 처음 눌렀다는 뜻
            {
                iter->second->bDown = true;
                iter->second->bPress = true;
            }

            else if (iter->second->bDown)        // bDown이 true라면 직전 순간에 이미 누르고 있었다는 뜻
                iter->second->bDown = false;
        }

        else    // 맵핑된 키가 눌리지 않았을 때
        {  
            if (iter->second->bDown || iter->second->bPress)        // 누르지도 않았는데 둘 중 하나라도 true라면 직전 순간에 누르고 있었다는 뜻
            {
                iter->second->bUp = true;
                iter->second->bDown = false;
                iter->second->bPress = false;
            }

            else if (iter->second->bUp)     // 직전 순간에 bUp에 대한 판정을 이미 실행했다면
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

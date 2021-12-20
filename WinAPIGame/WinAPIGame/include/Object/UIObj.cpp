#include "UIObj.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"
#include "../Resources/Texture.h"

UIObj::UIObj()
{
}

UIObj::UIObj(const UIObj& ui)	:
	Obj(ui)
{
}

UIObj::~UIObj()
{
}

void UIObj::Input(float fDeltaTime)
{
	Obj::Input(fDeltaTime);
}

int UIObj::Update(float fDeltaTime)
{
	Obj::Update(fDeltaTime);
	return 0;
}

int UIObj::LateUpdate(float fDeltaTime)
{
	Obj::LateUpdate(fDeltaTime);
	return 0;
}

void UIObj::Collision(float fDeltaTime)
{
	Obj::Collision(fDeltaTime);
}

void UIObj::Render(HDC hDC, float fDeltaTime)
{
	//Obj::Render(hDC, fDeltaTime);
	
	POSITION tPos;
	tPos.x = m_tPos.x - m_tSize.x * m_tPivot.x;
	tPos.y = m_tPos.y - m_tSize.y * m_tPivot.y;

	RESOLUTION tClientRS = GET_SINGLE(Camera)->GetClientRS();

	// �ؽ��� �� �ִϸ��̼� ���
	if (m_pTexture)
	{
		POSITION tImagePos;

		if (m_pAnimation)
		{
			PANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();

			if (pClip->eType == ANI_TYPE::ATLAS)
			{
				tImagePos.x = pClip->iCurFrameX * pClip->tFrameSize.x + (pClip->iCurFrameX - 1) * pClip->tFrameInterval.x;
				tImagePos.y = pClip->iCurFrameY * pClip->tFrameSize.y + (pClip->iCurFrameY - 1) * pClip->tFrameInterval.y;
			}
		}

		tImagePos.x += m_tImageOffset.x;
		tImagePos.y += m_tImageOffset.y;

		if (m_pTexture->GetColorKeyEnable())		// �÷�Ű�� Ȱ��ȭ�Ǿ� �ִٸ�
		{
			TransparentBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_tSize.x, (int)m_tSize.y, m_pTexture->GetDC(),
				(int)tImagePos.x, (int)tImagePos.y, (int)m_tSize.x, (int)m_tSize.y, m_pTexture->GetColorKey());
		}
		else
		{
			BitBlt(hDC, (int)tPos.x, (int)tPos.y, (int)m_tSize.x, (int)m_tSize.y, m_pTexture->GetDC(), (int)tImagePos.x, (int)tImagePos.y, SRCCOPY);
		}
	}

	// �浹ü ���
	list<Collider*>::iterator iter;
	list<Collider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
	{
		// TODO: Object�� Enable ���� �߰��ϸ� �ݿ�

		(*iter)->Render(hDC, fDeltaTime);

		// TODO: Object�� Life ���� �߰��ϸ� �ݿ�
	}
}

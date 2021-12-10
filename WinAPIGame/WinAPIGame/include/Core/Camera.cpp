#include "Camera.h"
#include "../Object/Obj.h"

DEFINITION_SINGLE(Camera)

Camera::Camera()	:
	m_pTarget(NULL)
{
}

Camera::~Camera()
{
	SAFE_RELEASE(m_pTarget);
}

void Camera::SetTarget(Obj* pObj)
{
	SAFE_RELEASE(m_pTarget);
	m_pTarget = pObj;

	if (m_pTarget)
		m_pTarget->AddRef();
}

bool Camera::Init(const POSITION& tPos, const RESOLUTION& tRS, const RESOLUTION& tWorldRS)
{
	m_tPos = tPos;
	m_tClientRS = tRS;
	m_tWorldRS = tWorldRS;
	m_tPivot = POSITION(0.5f, 0.5f);	// Pivot �����̴� ��ɵ� ����غ���

	return true;
}

void Camera::Input(float fDeltaTime)
{
	if (!m_pTarget)		// Ÿ���� ���� ��� �Է����� �����̴� ���� ī�޶�
	{
		// TODO: ���� ī�޶� ���� ���� (FW�� ����)
	}
}

void Camera::Update(float fDeltaTime)
{
	if (m_pTarget)
	{
		POSITION	tPos = m_pTarget->GetPos();
		POSITION	tPivot = m_pTarget->GetPivot();
		_SIZE		tSize = m_pTarget->GetSize();

		// Ÿ���� �����¿� ��ǥ
		float fL = tPos.x - tPivot.x * tSize.x;	// Left
		float fT = tPos.y - tPivot.y * tSize.y;	// Top
		float fR = fL + tSize.x;				// Right
		float fB = fT + tSize.y;				// Bottom

		// ī�޶��� Pivot���� �������� ��/��, ��/�Ϸ� �������� ũ��
		float fLeftArea		= m_tClientRS.iW * m_tPivot.x;
		float fRightArea	= m_tClientRS.iW - fLeftArea;
		float fTopArea		= m_tClientRS.iH * m_tPivot.y;
		float fBottomArea	= m_tClientRS.iH - fTopArea;

		// ī�޶� Ÿ���� ����ٴϱ� & ���� ������ ������ �ʵ��� ����
		if (tPos.x <= fLeftArea)						// Ÿ���� ������ ���� ���� ����� ��
			m_tPos.x = 0.f;
		else if (tPos.x >= m_tWorldRS.iW - fRightArea)	// Ÿ���� ������ ������ ���� ����� ��
			m_tPos.x = (float)m_tWorldRS.iW - (float)m_tClientRS.iW;
		else
			m_tPos.x = tPos.x - (float)m_tClientRS.iW * m_tPivot.x;

		if (tPos.y <= fTopArea)							// Ÿ���� ������ ���� ���� ����� ��
			m_tPos.y = 0.f;
		else if (tPos.y >= m_tWorldRS.iH - fBottomArea)	// Ÿ���� ������ �Ʒ��� ���� ����� ��
			m_tPos.y = (float)m_tWorldRS.iH - (float)m_tClientRS.iH;
		else
			m_tPos.y = tPos.y - (float)m_tClientRS.iH * m_tPivot.y;
	}
}

void Camera::Scroll(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;

	if (m_tPos.x < 0)
		m_tPos.x = 0;
	else if (m_tPos.x > m_tWorldRS.iW - m_tClientRS.iW)
		m_tPos.x = (float)m_tWorldRS.iW - (float)m_tClientRS.iW;

	if (m_tPos.y < 0)
		m_tPos.y = 0;
	else if (m_tPos.y > m_tWorldRS.iH - m_tClientRS.iH)
		m_tPos.y = (float)m_tWorldRS.iH - (float)m_tClientRS.iH;
}

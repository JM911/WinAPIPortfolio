#include "Obj.h"

Obj::Obj()
{
}

Obj::Obj(const Obj& obj)
{
	*this = obj;

	// TODO: �ִϸ��̼� ����, �浹ü ����
}

Obj::~Obj()
{
}

void Obj::Input(float fDeltaTime)
{
}

int Obj::Update(float fDeltaTime)
{
	// TODO: �浹ü�� �ִϸ��̼� ������Ʈ
	return 0;
}

int Obj::LateUpdate(float fDeltaTime)
{
	// TODO: �浹ü�� �ִϸ��̼� ������Ʈ
	return 0;
}

void Obj::Collision(float fDeltaTime)
{
}

void Obj::Render(HDC hDC, float fDeltaTime)
{
	POSITION tPos;
	tPos.x = m_tPos.x - m_tSize.x * m_tPivot.x;
	tPos.y = m_tPos.y - m_tSize.y * m_tPivot.y;

	// TODO: ȭ�� ������ ������ �������� �ʵ��� �ϴ� ���� �߰�

	// TODO: ���߿� �ؽ��� �����ϸ� �ؽ��Ŀ� �ִϸ��̼��� �׸����� ����
	Rectangle(hDC, (int)tPos.x, (int)tPos.y, (int)(tPos.x + m_tSize.x), (int)(tPos.y + m_tSize.y));
}

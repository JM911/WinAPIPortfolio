#include "Obj.h"

Obj::Obj()
{
}

Obj::Obj(const Obj& obj)
{
	*this = obj;

	// TODO: 애니메이션 복사, 충돌체 복사
}

Obj::~Obj()
{
}

void Obj::Input(float fDeltaTime)
{
}

int Obj::Update(float fDeltaTime)
{
	// TODO: 충돌체와 애니메이션 업데이트
	return 0;
}

int Obj::LateUpdate(float fDeltaTime)
{
	// TODO: 충돌체와 애니메이션 업데이트
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

	// TODO: 화면 밖으로 나가면 렌더하지 않도록 하는 설정 추가

	// TODO: 나중에 텍스쳐 설정하면 텍스쳐와 애니메이션을 그리도록 수정
	Rectangle(hDC, (int)tPos.x, (int)tPos.y, (int)(tPos.x + m_tSize.x), (int)(tPos.y + m_tSize.y));
}

#pragma once

// 애니메이션 타입
enum class ANI_TYPE
{
	ATLAS,
	FRAME,
	END
};

// 애니메이션 옵션
enum class ANI_OPTION
{
	LOOP,			// 계속 반복되는 동작 (주로 idle 모션)
	ONCE_RETURN,	// 한 번 돌고 디폴트 모션으로 돌아감
	ONCE_DESTROY,	// 한 번 돌고 오브젝트 삭제(이펙트 등)
	TIME_RETURN,	// 일정 시간 돌고 디폴트 모션으로 돌아감
	TIME_DESTROY	// 일정 시간 돌고 오브젝트 삭제(버프 이펙트, 일정 시간동안 발동하는 스킬 등)
};
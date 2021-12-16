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

// 충돌체 타입
enum class COL_TYPE
{
	RECT,
	SPHERE,
	LINE,
	POINT,
	PIXEL,
	END
};

// 충돌 상태
enum class COL_STATE
{
	ENTER,
	STAY,
	LEAVE,
	END
};

// 씬 타입
enum class SCENE_TYPE
{
	CURRENT,
	NEXT,
	END
};

// 씬 변경 여부
enum class SCENE_CHANGE
{
	NONE,
	CHANGE
};

// 플레이어 상태
enum class PLAYER_STATUS
{
	IDLE_LEFT,
	IDLE_RIGHT,
	WALK_LEFT,
	WALK_RIGHT,
	JUMP_LEFT,
	JUMP_RIGHT,
	FALLING_LEFT,
	FALLING_RIGHT,
	DASH_LEFT,
	DASH_RIGHT,
	DASH_UP,
	DASH_DOWN,
	DASH_UPLEFT,
	DASH_UPRIGHT,
	DASH_DOWNLEFT,
	DASH_DOWNRIGHT,
	ON_LEFTWALL,
	ON_RIGHTWALL,
	CLIMB_LEFTWALL,
	CLIMB_RIGHTWALL,
	JUMP_LEFTWALL,
	JUMP_RIGHTWALL
};
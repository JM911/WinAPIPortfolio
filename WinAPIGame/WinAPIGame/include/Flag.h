#pragma once

// �ִϸ��̼� Ÿ��
enum class ANI_TYPE
{
	ATLAS,
	FRAME,
	END
};

// �ִϸ��̼� �ɼ�
enum class ANI_OPTION
{
	LOOP,			// ��� �ݺ��Ǵ� ���� (�ַ� idle ���)
	ONCE_RETURN,	// �� �� ���� ����Ʈ ������� ���ư�
	ONCE_DESTROY,	// �� �� ���� ������Ʈ ����(����Ʈ ��)
	TIME_RETURN,	// ���� �ð� ���� ����Ʈ ������� ���ư�
	TIME_DESTROY	// ���� �ð� ���� ������Ʈ ����(���� ����Ʈ, ���� �ð����� �ߵ��ϴ� ��ų ��)
};

// �浹ü Ÿ��
enum class COL_TYPE
{
	RECT,
	SPHERE,
	LINE,
	POINT,
	PIXEL,
	END
};

// �浹 ����
enum class COL_STATE
{
	ENTER,
	STAY,
	LEAVE,
	END
};

// �� Ÿ��
enum class SCENE_TYPE
{
	CURRENT,
	NEXT,
	END
};

// �� ���� ����
enum class SCENE_CHANGE
{
	NONE,
	CHANGE
};

// �÷��̾� ����
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
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
	CIRCLE,
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

// �ִϸ��̼� ����� �÷��̾� ����
enum class PLAYER_ANI_STATUS
{
	IDLE_LEFT,
	IDLE_RIGHT,
	WALK_LEFT,
	WALK_RIGHT,
	JUMP_LEFT,
	JUMP_RIGHT,
	FALL_LEFT,
	FALL_RIGHT,
	CLIMB_LEFT,
	CLIMB_RIGHT
};

// UI ��ư ����
enum class BTN_STATE
{
	NONE,
	MOUSE_OVER,
	CLICK
};

// ���� Ÿ��
enum class SOUND_TYPE
{
	BGM,
	EFFECT,
	END
};
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
#include "stdafx.h"
#include "EnemyAIMove.h"
#include "EnemyBase.h"
#include "Player.h"
#include "EnemyAIConBase.h"

//�萔��
namespace{
	static const float ENEMY_SPEED = 200.0f;
}

//�X�^�[�g�֐�
void EnemyAIMove::EnemyAIStart()
{
	m_player = FindGO<Player>("player");
}

//�A�b�v�f�[�g�֐�
void EnemyAIMove::EnemyAIUpdate()
{
	//���̃G�l�~�[�̃|�W�V�������擾
	Vector3 enemyPos = GetEnemyPtr().GetPosition();
	//�v���C���[�̃|�W�V�������擾
	Vector3 playerPos = m_player->GetPosition();

	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�����v�Z
	Vector3 diff = playerPos - enemyPos;
	//�x�N�g����P�ʃx�N�g����
	diff.Normalize();
	//�X�s�[�h�����Z
	Vector3 moveSpeed = diff * ENEMY_SPEED;
	//�ŏI�I�Ȉړ��ʒu��ݒ�
	Vector3 finalPos = GetEnemyPtr().GetCController()
		->Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	//�ʒu��ݒ�
	GetEnemyPtr().SetPosition(finalPos);

	//��]�n�̌v�Z
	RotationCalc(moveSpeed);

	//���ʒl
	Vector3 newForward = Vector3::AxisZ;

	GetEnemyPtr().SetForward(newForward);
}

//��]�l�̌v�Z
void EnemyAIMove::RotationCalc(const Vector3& moveSpeed)
{
	if (fabsf(moveSpeed.x) < 0.001f
		&& fabsf(moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(moveSpeed.x, moveSpeed.z);
	Quaternion rotation;
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	rotation.SetRotationY(angle);
	//��]�l��ݒ�
	GetEnemyPtr().SetRotation(rotation);
}
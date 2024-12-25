#include "stdafx.h"
#include "EnemyAIConColPlayer.h"
#include "Player.h"
#include "EnemyBase.h"

//�X�^�[�g�֐�
void EnemyAIConColPlayer::InitData()
{
	m_player = FindGO<Player>("player");
}

//�������s�֐�
bool EnemyAIConColPlayer::Execution()
{
	if (m_enemy == nullptr)
	{
		return false;
	}

	//�G�l�~�[�̃R���W�������擾����
	const auto& enemyCollision = g_collisionObjectManager->FindCollisionObject("enemy_col");

	if (enemyCollision == nullptr)
	{
		return false;
	}

	//�����G�l�~�[�̃R���W������
	//�v���C���[�̃L�����R���ɏՓ˂�����
	if (enemyCollision->IsHit(m_player->GetCharacterController()))
	{
		return true;
	}

	return false;
}


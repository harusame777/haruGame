#include "stdafx.h"
#include "WarriorAIMetapPatrol.h"
#include "Player.h"

//�萔��
namespace {
	/// <summary>
	/// �E�H���A�[�̍ő吔
	/// </summary>
	static const int WARRIOR_NUM = 3;
	float LEAVE_OR_CLOSER_DIFF = 1500.0f;
}

//���^AI�̏�����
void WarriorAIMetapPatrol::MetaAIInit()
{
	//�v���C���[�̃C���X�^���X���擾����
	m_player = FindGO<Player>("player");
}

//���^AI�̎��s
void WarriorAIMetapPatrol::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	WarriorRangeCalc();
}

void WarriorAIMetapPatrol::WarriorRangeCalc()
{
	//�v���C���[�̍��W
	Vector3 playerPos = m_player->GetPosition();
	//�E�H���A�[�̈ʒu���擾����ϐ���錾
	Vector3 warriorPos = m_MainCallWarrior->GetEnemyPtr().GetPosition();
	//�E�H���A�[�ƃv���C���[�̋���
	float warriorToPlayerDis;

	//�������v�Z
	warriorToPlayerDis = (playerPos - warriorPos).Length();

	if (warriorToPlayerDis < LEAVE_OR_CLOSER_DIFF)
	{
		//�v���C���[���牓�����񃋁[�g��T��
		SearchRute(SearchMode::en_Far);
	}
	else
	{
		//�v���C���[����߂����񃋁[�g��T��
		SearchRute(SearchMode::en_Near);
	}

}

void WarriorAIMetapPatrol::SearchRute(const SearchMode mode)
{

	//�v���C���[�̍��W
	Vector3 playerPos = m_player->GetPosition();
	//�S�[���n�_����v���C���[�܂ł̋���
	float ruteToPlayerDiff;
	//�m�肵���p�g���[�����[�g�̃f�[�^
	PatrolRuteDataHolder::PatrolRuteData* confirmedRute = nullptr;
	//�m�肵������
	float confirmedDiff;

	//���[�g�̐��Ԃ��
	for (auto& ptr : m_sharedPatrolRuteDatas->m_patrolRuteList)
	{

		//���̃p�g���[�����[�g���g�p����������
		if (ptr->GetIsUse() == true)
		{
			//�������΂�
			continue;
		}

		//�S�[���n�_����v���C���[�܂ł̋������v�Z����
		ruteToPlayerDiff = (playerPos - ptr->GetPosition()).Length();

		//���[�h���ߋ������[�h��������
		if (mode == SearchMode::en_Near)
		{
			//�f�[�^�������͏�Ԃł���܂��́A
			//���ɓ��͂��ꂽ�������߂�������
			if (confirmedRute == nullptr
				|| ruteToPlayerDiff < confirmedDiff)
			{
				//���݂̃|�C���^�̃f�[�^����͂���
				confirmedRute = ptr;

				//������������
				confirmedDiff = ruteToPlayerDiff;
			}
		}
		//���[�h�����������[�h��������
		else if (mode == SearchMode::en_Far)
		{
			//�f�[�^�������͏�Ԃł���܂��́A
			//���ɓ��͂��ꂽ������艓��������
			if (confirmedRute == nullptr
				|| ruteToPlayerDiff > confirmedDiff)
			{
				//���݂̃|�C���^�̃f�[�^����͂���
				confirmedRute = ptr;

				//������������
				confirmedDiff = ruteToPlayerDiff;
			}
		}

	}

	//�����f�[�^�������͏�Ԃ���Ȃ�������
	if (confirmedRute != nullptr)
	{
		//���̃��[�g���g�p���ɂ���
		confirmedRute->SetIsUse(true);

		//�ǐՒn�_���G�l�~�[�ɑ���
		m_MainCallWarrior->GetEnemyPtr().SetMoveTargetPosition(confirmedRute->GetPosition());
	}
}

void WarriorAIMetapPatrol::ProcessEnd()
{

	for (auto& ptr : m_sharedPatrolRuteDatas->m_patrolRuteList)
	{

		if (m_MainCallWarrior == ptr->GetUseEnemyPtr())
		{
			ptr->SetIsUse(false);
			SetProcessEndFlag(true);
		}

	}

}
#include "stdafx.h"
#include "EnemyAIMovePatrol.h"
#include "Player.h"
#include "EnemyBase.h"

//�萔��
namespace {
	float LEAVE_OR_CLOSER_DIFF = 1500.0f;
}

//�X�^�[�g�֐�
void EnemyAIMovePatrol::EnemyAIStart()
{
	//���x�������_�[���g�p���ď���n�_���擾����
	m_levelRender.Init("Assets/mapLevel/testLevel3.tkl", [&](LevelObjectData_Render& objData)
		{
			if (objData.ForwardMatchName(L"patrolroute") == true)
			{
				MetaAIPatrolRuteData* newData = new MetaAIPatrolRuteData;

				//���x������ʒu���擾����
				newData->m_patrolPos = objData.m_position;

				//�z��Ɋi�[����
				m_patrolRuteList.push_back(newData);

				return true;
			}
			return true;
		});

	//�v���C���[�̃C���X�^���X���擾����
	m_player = FindGO<Player>("player");
}

//�A�b�v�f�[�g�֐�
void EnemyAIMovePatrol::EnemyAIUpdate()
{

}

void EnemyAIMovePatrol::WarriorRangeCalc()
{
	//�v���C���[�̍��W
	Vector3 playerPos = m_player->GetPosition();
	//�E�H���A�[�̈ʒu���擾����ϐ���錾
	Vector3 warriorPos;
	//�E�H���A�[�ƃv���C���[�̋���
	float warriorToPlayerDis;
	
	//�������v�Z
	warriorToPlayerDis = (playerPos - warriorPos).Length();

	if (warriorToPlayerDis < LEAVE_OR_CLOSER_DIFF)
	{

	}
	else
	{
		//�v���C���[����߂����񃋁[�g��T��
		SearchRute(SearchMode::en_Near);
	}

}

void EnemyAIMovePatrol::SearchRute(const SearchMode mode)
{

	//�v���C���[�̍��W
	Vector3 playerPos = m_player->GetPosition();
	//
	float ruteToPlayerDiff;
	//
	MetaAIPatrolRuteData* confirmedRute = nullptr;

	float confirmedDiff;

	for (auto& ptr : m_patrolRuteList)
	{
		
		if (ptr->m_isUse == true)
		{
			continue;
		}

		ruteToPlayerDiff = (playerPos - ptr->m_patrolPos).Length();

		if (mode == SearchMode::en_Near)
		{
			if (confirmedRute == nullptr
				|| ruteToPlayerDiff < confirmedDiff)
			{
				confirmedRute = ptr;

				confirmedDiff = ruteToPlayerDiff;
			}
		}
		else
		{
			if (confirmedRute == nullptr
				|| ruteToPlayerDiff > confirmedDiff)
			{
				confirmedRute = ptr;

				confirmedDiff = ruteToPlayerDiff;
			}
		}

	}

	if (confirmedRute != nullptr)
	{
		confirmedRute->m_isUse = true;

		GetEnemyPtr().SetMoveTargetPosition(confirmedRute->m_patrolPos);
	}
}
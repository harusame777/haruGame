#include "stdafx.h"
#include "WarriorAIMetaRetreat.h"
#include "EnemyBase.h"
#include "EnemyAIConBase.h"
#include "EnemyAIConWaitTime.h"

void WarriorAIMetaRetreat::MetaAIInit()
{

}

void WarriorAIMetaRetreat::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	SearchRute();
}

void WarriorAIMetaRetreat::SearchRute()
{

	//�S�[���n�_����v���C���[�܂ł̋���
	float ruteToMainWarriorDiff;
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

		//����
		ruteToMainWarriorDiff = (ptr->GetPosition() - m_MainCallWarrior->GetEnemyPtr().GetPosition()).Length();

		//�f�[�^�������͏�Ԃł���܂��́A
		//���ɓ��͂��ꂽ�������߂�������
		if (confirmedRute == nullptr
			|| ruteToMainWarriorDiff > confirmedDiff)
		{
			//���݂̃|�C���^�̃f�[�^����͂���
			confirmedRute = ptr;

			//������������
			confirmedDiff = ruteToMainWarriorDiff;
		}
	
	}

	//�����f�[�^�������͏�Ԃ���Ȃ�������
	if (confirmedRute != nullptr)
	{
		//���̃��[�g���g�p���ɂ���
		confirmedRute->SetIsUse(true);

		//���̃��[�g���g�p���Ă���G�l�~�[��o�^����
		confirmedRute->SetUseEnemyPtr(m_MainCallWarrior);

		//�ǐՒn�_���G�l�~�[�ɑ���
		m_MainCallWarrior->GetEnemyPtr().SetMoveTargetPosition(confirmedRute->GetPosition());
	}

}

const bool WarriorAIMetaRetreat::ProcessEnd(EnemySMBase* initEnemy)
{
	for (auto& ptr : m_sharedPatrolRuteDatas->m_patrolRuteList)
	{

		if (m_MainCallWarrior == ptr->GetUseEnemyPtr())
		{
			ptr->SetIsUse(false);
			ptr->SetUseEnemyPtr(nullptr);
			m_isOneTimeGetRute = false;

			return true;
		}


	}

	return false;
}
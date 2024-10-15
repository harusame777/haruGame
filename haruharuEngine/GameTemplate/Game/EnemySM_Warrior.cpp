#include "stdafx.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"
#include "EnemyAIConSearch.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyAIConWaitTime.h"

//�X�^�[�g�֐�
void EnemySM_Warrior::Start()
{
	//AI��List�����̃G�l�~�[�ɕK�v�ȕ��ŏ���������
	//�o�H�T��
	m_enemyAIList.push_back(new EnemyAIMoveAstar);

	//�R�Â��Ă���G�l�~�[�̃C���X�^���X��AIList�̃v���O�����ɓn��
	for (auto& listPtr : m_enemyAIList)
	{
		listPtr->BinedEnemy(m_enemy);
	}

	//AIList�̒��̃v���O�����̃X�^�[�g�֐����N������
	for (auto& listPtr : m_enemyAIList)
	{
		listPtr->Start();
	}

	//����̃v���O���������X�g�Ɋi�[���Ă���
	//���E�T��
	m_enemyConList.push_back(new EnemyAIConSearch);

	//10�b�^�C�}�[
	m_enemyConList.push_back(new EnemyAIConWaitTime(10.0f));

	//�R�Â��Ă���G�l�~�[�̃C���X�^���X��ConList�̃v���O�����ɓn��
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->BinedEnemy(m_enemy);
	}

	//ConList�̒��̃v���O�����̃X�^�[�g�֐����N������
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->Start();
	}
}

//�A�b�v�f�[�g�֐�
void EnemySM_Warrior::Update()
{
	switch (m_warriorState)
	{
		//�ҋ@�X�e�[�g
	case EnemySM_Warrior::en_warrior_idle:
		//�ʂ̃X�e�[�g�ɂ���
		ChangeState();
		break;
		//�ǐՃX�e�[�g
	case EnemySM_Warrior::en_warrior_tracking:
		//10�b�ҋ@
		//10�b�o���Ă�����
		if (m_enemyConList[1]->Execution())
		{
			//�ʂ̃X�e�[�g�ɂ���
			ChangeState();
		}
		//10�b�o���Ă��Ȃ�������
		else
		{
			//�ǐՏ������X�V
			m_enemyAIList[0]->Update();
		}
		break;
	default:
		break;
	}
}

//���ʃX�e�[�g�ύX�֐�
void EnemySM_Warrior::ChangeState()
{
	//�ҋ@�X�e�[�g�ɂ���
	m_warriorState = WarriorState::en_warrior_idle;

	//�����ǐՃX�e�[�g����Ȃ���
	if (m_warriorState != WarriorState::en_warrior_tracking)
	{
		//���E���Ƀv���C���[�����ď����v���C���[�Ƃ̊Ԃɕǂ�����������
		if (m_enemyConList[0]->Execution())
		{
			//�ǐՃX�e�[�g�ɂ���
			m_warriorState = WarriorState::en_warrior_tracking;
		}
	}
}
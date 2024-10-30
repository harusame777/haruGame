#include "stdafx.h"
#include "EnemySM_Warrior.h"
#include "EnemyAIConSearch.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyAIConWaitTime.h"
#include "EnemyAIConColPlayer.h"
#include "EnemyAIMetaWarrior.h"

//�X�^�[�g�֐�
void EnemySM_Warrior::EnemyAIStart()
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
		listPtr->EnemyAIStart();
	}

	//����̃v���O���������X�g�Ɋi�[���Ă���
	//���E�T��
	m_enemyConList.push_back(new EnemyAIConSearch);

	//10�b�^�C�}�[
	m_enemyConList.push_back(new EnemyAIConWaitTime(10.0f));

	//�v���C���[�Ƃ̏Փ˔���
	m_enemyConList.push_back(new EnemyAIConColPlayer);

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

	//���^AI�̃C���X�^���X���i�[
	m_warriorMetaAI = FindGO<EnemyAIMetaWarrior>("MetaAI");
	//���^AI�ɃG�l�~�[�̃C���X�^���X�𑗂�
	m_warriorMetaAI->ListInitEnemy(this);
}

//�A�b�v�f�[�g�֐�
void EnemySM_Warrior::EnemyAIUpdate()
{
	//���ԍX�V
	TimeUpdate();

	switch (m_warriorState)
	{
		//�ҋ@�X�e�[�g
	case EnemySM_Warrior::en_warrior_idle:
		//�ʂ̃X�e�[�g�ɂ���
		ChangeState();
		break;
		//�ǐՃX�e�[�g
	case EnemySM_Warrior::en_warrior_tracking:
		//�ǐՂ��邩���Ȃ���
		if (!m_isTrackingTimeOver)
		{
			//�ʂ̃X�e�[�g�ɂ���
			ChangeState();
		}
		//10�b�o���Ă��Ȃ�������
		else
		{
			//�ǐՏ������X�V
			m_enemyAIList[0]->EnemyAIUpdate();
		}
		break;
	case EnemySM_Warrior::en_warrior_trackingMetaAI:
		//�ǐՂ��J�n����
		StateTransition_Tracking();
		break;
	default:
		break;
	}

}

//���ʃX�e�[�g�ύX�֐�
void EnemySM_Warrior::ChangeState()
{
	//�v���C���[�Ƃ̐ڐG����
	if (m_enemyConList[2]->Execution())
	{

	}

	//�ҋ@�X�e�[�g�ɂ���
	SetState(WarriorState::en_warrior_idle);

	//�����ǐՃX�e�[�g����Ȃ���
	if (m_warriorState != WarriorState::en_warrior_tracking)
	{
		//���E���Ƀv���C���[�����ď����v���C���[�Ƃ̊Ԃɕǂ�����������
		if (m_enemyConList[0]->Execution())
		{
			StateTransition_Tracking();
		}
	}
}

void EnemySM_Warrior::StateTransition_Tracking()
{
	//[�e�X�g]���^AI����w�������炤
	m_warriorMetaAI->MetaAIExecution(this);
	//�ǐՃX�e�[�g�ɂ���
	SetState(WarriorState::en_warrior_tracking);
	//�ǐՂ���悤��
	m_isTracking = true;
	m_isTrackingTimeOver = true;
	//�ǐՎ��Ԃ�������
	m_enemyConList[1]->Start();
}

//���ԏ���
void EnemySM_Warrior::TimeUpdate()
{
	//���݂̃X�e�[�g���ǐՏ�Ԃ�������
	if (m_warriorState == WarriorState::en_warrior_tracking)
	{
		//�ǐՃ^�C�}�[���X�V����
		//�c��b����0.0��������
		if (m_enemyConList[1]->Execution())
		{
			//�ǐՂ���ʂ̃X�e�[�g�ɂ���悤�ɂ���
			m_isTracking = false;
			m_isTrackingTimeOver = false;
			//�ǐՎ��Ԃ�������
			m_enemyConList[1]->Start();
			//���^AI�̃v���Z�X���I������
			m_warriorMetaAI->ProcessEnd();
		}
	}
}



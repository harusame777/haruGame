#include "stdafx.h"
#include "EnemySM_Warrior.h"
#include "EnemyAIConSearch.h"
#include "EnemyAIConWallSearch.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyAIMove.h"
#include "EnemyAIConWaitTime.h"
#include "EnemyAIConColPlayer.h"
#include "EnemyAIMetaWarrior.h"
#include "Player.h"
#include "Game.h"

//�G�l�~�[�S�̂��Ǘ����郁�^AI���쐬���āA�ǐՂ��Ǘ�������
//
//1.�G�l�~�[���ǐՂ��J�n����ۂɁA���^AI�ɃG�l�~�[�S�̂����āA���ɒǐՂ�����
//�G�l�~�[��I������֐������s������
//
//2.���^AI�ɑI�������G�l�~�[����A���ʂɒǂ��G�l�~�[�ƁA��荞�݂�������G�l�~�[��
//���ʂ�����B
//
//3.�G�l�~�[���ǐՂ��J�n����
//
//�Ȃ����^AI�̏����͒ǐՊJ�n��1��݂̂̏����Ƃ���
//
//�����炭�ǐՑ��s�̏������悭�Ȃ��̂ŉ��ǂ̕K�v�A��

//�X�^�[�g�֐�
void EnemySM_Warrior::EnemyAIStart()
{
	//���^AI�̃C���X�^���X���i�[
	m_warriorMetaAI = FindGO<EnemyAIMetaWarrior>("MetaAI");
	//���^AI�ɃG�l�~�[�̃C���X�^���X�𑗂�
	m_warriorMetaAI->ListInitEnemy(this);

	//�Q�[���̃C���X�^���X
	m_game = FindGO<Game>("game");

	//���ʂ̃f�[�^�z���_�[��������
	m_warriorDataHolder = m_warriorMetaAI->GetEnemyDatas();

	//AI��List�����̃G�l�~�[�ɕK�v�ȕ��ŏ���������
	//�o�H�T��
	m_enemyAIList.push_back(new EnemyAIMoveAstar(m_warriorDataHolder));

	//�ʏ�ړ�
	m_enemyAIList.push_back(new EnemyAIMove);

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
	m_enemyConList.push_back(new EnemyAIConSearch(45.0f,500.0f));

	//10�b�^�C�}�[
	m_enemyConList.push_back(new EnemyAIConWaitTime(10.0f));

	//�v���C���[�Ƃ̏Փ˔���
	m_enemyConList.push_back(new EnemyAIConColPlayer);

	//�ǐՎ����E�T��
	m_enemyConList.push_back(new EnemyAIConSearch(75.0f, 700.0f));

	//5�b�^�C�}�[
	m_enemyConList.push_back(new EnemyAIConWaitTime(5.0f));

	//15�b�^�C�}�[
	m_enemyConList.push_back(new EnemyAIConWaitTime(15.0f));

	//�ǂ�T��
	m_enemyConList.push_back(new EnemyAIConWallSearch);

	//20�b�^�C�}�[
	m_enemyConList.push_back(new EnemyAIConWaitTime(25.0f));

	//�R�Â��Ă���G�l�~�[�̃C���X�^���X��ConList�̃v���O�����ɓn��
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->BinedEnemy(m_enemy);
	}

	//ConList�̒��̃v���O�����̃X�^�[�g�֐����N������
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->InitData();
	}

	m_player = FindGO<Player>("player");
}

//�A�b�v�f�[�g�֐�
void EnemySM_Warrior::EnemyAIUpdate()
{
	if (m_warriorDataHolder->m_warriorDatas.size() == 0)
	{
		return;
	}

	//���ԍX�V
	TimeUpdate();

	//�����𒲐�
	m_warriorMetaAI->MetaAIExecution(this, EnemyAIMetaWarrior::mode_footStep);


	switch (m_warriorState)
	{
		//�ҋ@�X�e�[�g
	case EnemySM_Warrior::en_warrior_idle:

		m_enemy->SetPlayAnimationState(EnemyBase::en_idle);

		//�ʂ̃X�e�[�g�ɂ���
		ChangeState();
		break;
		//�ǐՃX�e�[�g
	case EnemySM_Warrior::en_warrior_tracking:

		m_enemy->SetPlayAnimationState(EnemyBase::en_patrol);

		//�����ދp��Ԃ���Ȃ�������
		if (m_isRetreat == false)
		{
			Vector3 plaPos = m_player->GetPosition();

			GetEnemyPtr().SetMoveTargetPosition(plaPos);
		}
		else
		{
			//[�e�X�g]���^AI����w�������炤
			m_warriorMetaAI->MetaAIExecution(this, EnemyAIMetaWarrior::mode_retreat);
		}

		//�ǐՏ������X�V
		m_enemyAIList[en_enemyAIMoveAstar]->EnemyAIUpdate();

		ChangeState();
		break;
	case EnemySM_Warrior::en_warrior_patrol:

		m_enemy->SetPlayAnimationState(EnemyBase::en_patrol);

		//���񏈗����X�V����
		m_enemyAIList[en_enemyAIMoveAstar]->EnemyAIUpdate();
		//�ʂ̃X�e�[�g�ɂ���
		ChangeState();
		break;
	case EnemySM_Warrior::en_warrior_trackingMetaAI:
		//�ǐՂ��J�n����
		StateTransition_Tracking();

		m_enemy->SetPlayAnimationState(EnemyBase::en_patrol);

		break;
	case EnemySM_Warrior::en_stop:

		m_enemy->SetPlayAnimationState(EnemyBase::en_idle);

		break;
	case EnemySM_Warrior::en_attack:

		m_enemy->SetPlayAnimationState(EnemyBase::en_attack);

		if (GetEnemyPtr().IsAnimationClipEnd() == true)
		{
			GetEnemyPtr().SetAnimationEnd(true);
		}

		break;
	default:
		break;
	}

}

//���ʃX�e�[�g�ύX�֐�
void EnemySM_Warrior::ChangeState()
{

	//�v���C���[�Ƃ̐ڐG����
	if (m_enemyConList[en_enemyAIConColPlayer]->Execution())
	{
		if (GetEnemyPtr().GetAttackFlag())
		{
			return;
		}

		GetEnemyPtr().SetAttackFlag(true);

		m_warriorMetaAI->MetaAIExecution(this,EnemyAIMetaWarrior::mode_stop);

		SetState(WarriorState::en_attack);

		m_game->PlayerGameOver();

		return;
	}

	if (m_warriorState == WarriorState::en_warrior_tracking ||
		m_warriorState == WarriorState::en_warrior_trackingMetaAI &&
		m_isTrackingTimeOver == true)
	{
		return;
	}

	if (m_warriorState != WarriorState::en_warrior_idle)
	{

		float diff = (GetEnemyPtr().GetPosition() - GetEnemyPtr().GetMoveTargetPosition()).Length();

		if (diff < 200.0f)
		{
			//�ҋ@�X�e�[�g�ɂ���
			SetState(WarriorState::en_warrior_idle);

			m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_patrolRouteSet,this);

			m_isWaitIdle = false;
		}
	}
	
	//��������X�e�[�g����Ȃ���
	if (m_warriorState != WarriorState::en_warrior_patrol)
	{
		//�ҋ@��Ԃ���5�b�����Ă�����
		if (m_isWaitIdle == true)
		{
			//[�e�X�g]���^AI����w�������炤
			m_warriorMetaAI->MetaAIExecution(this, EnemyAIMetaWarrior::mode_patrolRouteSet);
			//����X�e�[�g�ɂ���
			SetState(WarriorState::en_warrior_patrol);

			m_enemyConList[7]->InitData();

			m_isWaitIdle = false;
		}
	}


	//�����ǐՃX�e�[�g����Ȃ���
	if (m_warriorState != WarriorState::en_warrior_tracking)
	{
		//���E���Ƀv���C���[�����ď����v���C���[�Ƃ̊Ԃɕǂ�����������
		if (m_enemyConList[en_enemyAIConSearch]->Execution())
		{
			m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_patrolRouteSet, this);

			StateTransition_Tracking();
		}
	}
}

void EnemySM_Warrior::StateTransition_Tracking()
{
	//���̏�Ԃ��ƁA��x�ҋ@��ԂɂȂ�����ɂ�����x�ǐՏ�ԂɂȂ�ƁA�������������ĂȂ��̂ŁA�΍����������B
	//[�e�X�g]���^AI����w�������炤
	m_warriorMetaAI->MetaAIExecution(this,EnemyAIMetaWarrior::mode_trackingStateChange);
	//�ǐՃX�e�[�g�ɂ���
	SetState(WarriorState::en_warrior_tracking);
	//�ǐՂ���悤��
	m_isTrackingTimeOver = true;
	//�ǐՎ��Ԃ�������
	m_enemyConList[en_enemyAIConWaitTime10f]->InitData();
}

//���ԏ���
void EnemySM_Warrior::TimeUpdate()
{

	if (m_isRetreat == true)
	{
		if (m_enemyConList[5]->Execution())
		{
			//[�e�X�g]���^AI����w�������炤
			m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_retreat, this);

			StateTransition_Tracking();

			m_isRetreat = false;
		}
	}
	else
	{
		//�ǐՎ��Ԃ�������
		m_enemyConList[5]->InitData();
	}

	if (m_warriorState == WarriorState::en_warrior_patrol)
	{
		//�ҋ@�^�C�}�[���X�V����
		//�c��b����0.0��������
		if (m_enemyConList[7]->Execution())
		{
			//�ҋ@�X�e�[�g�ɂ���
			SetState(WarriorState::en_warrior_idle);

			m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_patrolRouteSet, this);

			m_isWaitIdle = false;
		}
	}

	//���݂̃X�e�[�g���ҋ@��Ԃ�������
	if (m_warriorState == WarriorState::en_warrior_idle)
	{
		//�ҋ@�^�C�}�[���X�V����
		//�c��b����0.0��������
		if (m_enemyConList[4]->Execution())
		{
			//����ɂ���
			m_isWaitIdle = true;
		}
	}
	else
	{
		//�ǐՎ��Ԃ�������
		m_enemyConList[4]->InitData();
	}

	//���݂̃X�e�[�g���ǐՏ�Ԃ�������
	if (m_warriorState == WarriorState::en_warrior_tracking)
	{
		//�v���C���[�����p�O�ɂ���
		if (!m_enemyConList[3]->Execution())
		{
			//�ǐՃ^�C�}�[���X�V����
			//�c��b����0.0��������
			if (m_enemyConList[en_enemyAIConWaitTime10f]->Execution())
			{
				//�ǐՂ���ʂ̃X�e�[�g�ɂ���悤�ɂ���
				m_isTrackingTimeOver = false;
				//�ǐՎ��Ԃ�������
				m_enemyConList[en_enemyAIConWaitTime10f]->InitData();

				SetState(WarriorState::en_warrior_idle);

				//���^AI�̃v���Z�X���I������
				m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_trackingStateChange,this);
			}
		}
		else
		{
			//�ǐՎ��Ԃ�������
			m_enemyConList[en_enemyAIConWaitTime10f]->InitData();
		}
	}
}



#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "WarriorAIMetaTracking.h"
#include "EnemySM_Warrior.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"
#include "Player.h"

//������
//
//1.�v���C���[��������
//
//2.�����̎���̃G�l�~�[�ɌĂт�����
//
//3.�Ăт����ɋC�Â��Ă��ꂽ�����ȊO�̃G�l�~�[�̌��݂̃X�e�[�g���擾����
//
//4.�����̃X�e�[�g�擾���A�����ȊO�̃G�l�~�[�̃X�e�[�g�ƌ���ׂ�
//
//5.���ʂɂ���ăX�e�[�g�̔ԍ���Ԃ�
//
//�ǂ̃^�C�~���O�ŒǐՃX�e�[�g��ύX���邩�H
//�G�l�~�[���v���C���[�ɋC�Â��Ď��͂ɌĂт������s�����^�C�~���O�Ŏ��s������
//�ǐՒ��ɂق��̃G�l�~�[���C�Â����肵����A�����I�Ɍ���ǂ��悤�ɂ���B

//�X�^�[�g�֐�
bool EnemyAIMetaWarrior::Start()
{

	//���ʂ̃f�[�^�z���_�[��������
	m_warriorDataHolder = std::make_shared<WarriorDataHolder>();

	//���^AI�̏����v���O������������
	m_AIMetaList.push_back(new WarriorAIMetaTracking(m_warriorDataHolder));

	for (auto& metaAIs : m_AIMetaList)
	{
		//������
		metaAIs->MetaAIInit();
	}

	return true;
}

//�E�H���A�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
void EnemyAIMetaWarrior::MetaAIExecution(EnemySM_Warrior* enemyPtr, const MetaAIMode setMode)
{

	//���݉�������̏�������������
	if (m_isCurrentlyProcessed == true)
	{
		return;
	}
	else
	{
		//�������ɂ���
		m_isCurrentlyProcessed = true;
	}

	//���̊֐����Ăяo�����G�l�~�[�̃|�C���^���i�[����
	m_MainCallWarrior = enemyPtr;

	//���������s����
	m_AIMetaList[setMode]->MetaAIExecution(enemyPtr);
}

//���X�g�ɃE�H���A�[����
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//���X�g�ɃE�H���A�[��������
	m_warriorDataHolder->m_warriorDatas.push_back(enemyPtr);
}

void EnemyAIMetaWarrior::ProcessEnd()
{
	//�����t���O���I���ɂ���
	m_isCurrentlyProcessed = false;

	//�S���̒ǐՃX�e�[�g���ǐՏ�Ԃɂ���
	for (auto& ptr : m_warriorDataHolder->m_warriorDatas)
	{
		ptr->SetTrackingState(WarriorTrackingState::en_nonTracking);
	}
}
#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "PatrolRuteDataHolder.h"
#include "WarriorAIMetaTracking.h"
#include "WarriorAIMetapPatrol.h"
#include "EnemySM_Warrior.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"
#include "Player.h"
#include "DebugEnemyTrackingState.h"
#include "WarriorAIMetaRetreat.h"

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
	
	m_debugWarriorTrackingState = NewGO<DebugEnemyTrackingState>(0, "debug");

	m_debugWarriorTrackingState->InitWarriorListData(m_warriorDataHolder);

	//���ʂ̃f�[�^�z���_�[��������
	m_patrolRuteDataHolder = std::make_shared<PatrolRuteDataHolder>();

	//���x�������_�[���g�p���ď���n�_���擾����
	m_patrolRuteLevelRender.Init("Assets/mapLevel/testLevel3.tkl", [&](LevelObjectData_Render& objData)
		{
			if (objData.ForwardMatchName(L"patrolroute") == true)
			{
				PatrolRuteDataHolder::PatrolRuteData* newData = new PatrolRuteDataHolder::PatrolRuteData;

				//���x������ʒu���擾����
				newData->SetPosition(objData.m_position);

				//�z��Ɋi�[����
				m_patrolRuteDataHolder->m_patrolRuteList.push_back(newData);

				return true;
			}
			return true;
		});

	//���^AI�̏����v���O������������
	ListInitAIMeta(new WarriorAIMetaTracking(m_warriorDataHolder), true);

	//���^AI�̏����v���O������������
	ListInitAIMeta(new WarriorAIMetapPatrol(m_warriorDataHolder, m_patrolRuteDataHolder), false);

	//���^AI�̏����v���O������������
	ListInitAIMeta(new WarriorAIMetaRetreat(m_patrolRuteDataHolder), true);

	for (auto& metaAIs : m_AIMetaList)
	{
		//������
		//metaAIs->MetaAIInit();
		metaAIs->GetAIMetaProgram()->MetaAIInit();
	}

	return true;
}

//�E�H���A�[�S�̂̒ǐՃX�e�[�g��ύX����֐�
void EnemyAIMetaWarrior::MetaAIExecution(EnemySM_Warrior* enemyPtr, const MetaAIMode setMode)
{

	if (m_AIMetaList[setMode]->GetAIMetaProgram()->GetOneTimeUpdateFlag() == true &&
		m_AIMetaList[setMode]->GetOneTimeOnlyUpdate() == true)
	{
		return;
	}

	if (m_AIMetaList[setMode]->GetOneTimeOnlyUpdate() == true)
	{
		m_AIMetaList[setMode]->GetAIMetaProgram()->SetOneTimeUpdateFlag(true);
	}

	//���̊֐����Ăяo�����G�l�~�[�̃|�C���^���i�[����
	m_MainCallWarrior = enemyPtr;

	//���������s����
	m_AIMetaList[setMode]->GetAIMetaProgram()->MetaAIExecution(enemyPtr);

}

//���X�g�ɃE�H���A�[����
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//���X�g�ɃE�H���A�[��������
	m_warriorDataHolder->m_warriorDatas.push_back(enemyPtr);
}

void EnemyAIMetaWarrior::ListInitAIMeta(EnemyAIMetaBase* programData, const bool isOneTime)
{
	//�V�������^AI�̃f�[�^���쐬����
	MetaAIData* newProgramData = new MetaAIData;
	//���^AI�̃v���O�����f�[�^��ݒ肷��
	newProgramData->SetAIMetaProgram(programData);
	//���̃��^AI���I���܂ň�񂵂��N�����Ȃ��̂���ݒ肷��
	newProgramData->SetOneTimeOnlyUpdate(isOneTime);
	//�f�[�^���i�[����
	m_AIMetaList.push_back(newProgramData);
}

void EnemyAIMetaWarrior::ProcessEnd(const MetaAIMode setMode, EnemySMBase* initEnemy)
{

	//���ׂĂ̏������I�����Ă�����
	if (m_AIMetaList[setMode]->GetAIMetaProgram()->ProcessEnd(initEnemy) == true)
	{
		//������x�N���ł���悤�ɂ���
		m_AIMetaList[setMode]->GetAIMetaProgram()->SetOneTimeUpdateFlag(false);
	}

}
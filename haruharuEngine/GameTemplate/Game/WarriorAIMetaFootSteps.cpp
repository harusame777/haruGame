#include "stdafx.h"
#include "WarriorAIMetaFootSteps.h"
#include "GameSound.h"
#include "Player.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"

//�萔��
namespace {

	static const float HIGH_VALUME_INDEX = 1.0f;
	static const float MIDDLE_VALUME_INDEX = 0.0f;
	static const float LOW_VALUME_INDEX = 0.0f;

}

//���^AI�̏�����
void WarriorAIMetaFootSteps::MetaAIInit()
{
	m_player = FindGO<Player>("player");
}

//���^AI�̎��s
void WarriorAIMetaFootSteps::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	//�G�l�~�[�̐��擾
	m_enemyNum = m_sharedWarriorDatas->m_warriorDatas.size();

	if (m_enemyLengthDatas[0].m_enemyData == nullptr)
	{
		for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
		{
			m_enemyLengthDatas[enemyNo].m_enemyData
				= &m_sharedWarriorDatas->m_warriorDatas[enemyNo]->GetEnemyPtr();
		}

		return;
	}

	//�����f�[�^������
	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{
		m_enemyLengthDatas[enemyNo].m_length = 0.0f;

		m_enemyLengthDatas[enemyNo].m_priority = en_priority_non;
	}

	EnemyStateCheck();

	LengthCalc();

	DatasPriorityInit();
}

void WarriorAIMetaFootSteps::EnemyStateCheck()
{

	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{

		m_enemyLengthDatas[enemyNo].m_warriorStateNum
			= m_enemyLengthDatas[enemyNo].m_enemyData->GetStateNumber();

		if (m_enemyLengthDatas[enemyNo].m_warriorStateNum
			!= EnemySM_Warrior::en_warrior_tracking &&
			m_enemyLengthDatas[enemyNo].m_warriorStateNum
			!= EnemySM_Warrior::en_warrior_trackingMetaAI)
		{
			m_enemyLengthDatas[enemyNo].m_enemyData
				->SetFootStepValumeCalcValue(true);

			return;
		}
	}

}

//�����v�Z
void WarriorAIMetaFootSteps::LengthCalc()
{

	//�G�l�~�[�S�̂̃v���C���[�Ƃ̋����𑪂�
	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{
		
		Vector3 diff = m_player->GetPosition()
			- m_enemyLengthDatas[enemyNo].m_enemyData->GetPosition();

		m_enemyLengthDatas[enemyNo].m_length = diff.Length();

	}	

}

void WarriorAIMetaFootSteps::DatasPriorityInit()
{

	EnemyLength_Data* highData = nullptr;
	std::vector<EnemyLength_Data*> lowDatas;
	
	//�܂��擪�v�f�̃G�l�~�[����ԋ߂��G�l�~�[�Ɖے�����
	//�����Ċi�[�����f�[�^�Ƃق��̃f�[�^��
	//��ׂď���������high�ɑ������
	//low����̓�������
	highData = &m_enemyLengthDatas[0];
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{
		if (highData->m_length
			> m_enemyLengthDatas[enemyNo].m_length)
			highData = &m_enemyLengthDatas[enemyNo];
	}

	//�����Ă���ȊO�̃f�[�^��low�Ɏw��
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{
		if (&m_enemyLengthDatas[enemyNo] == highData)
			continue;
		else
			lowDatas.push_back(&m_enemyLengthDatas[enemyNo]);
	}

	//�ŏI�ݒ�
	highData->m_enemyData->SetFootStepValumeCalcValue(true);

	for (auto& listData : lowDatas)
	{
		listData->m_enemyData->SetFootStepValumeCalcValue(false);
	}
}

//�����I��
const bool WarriorAIMetaFootSteps::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}

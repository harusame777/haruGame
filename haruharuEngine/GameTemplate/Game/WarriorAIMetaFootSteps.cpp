#include "stdafx.h"
#include "WarriorAIMetaFootSteps.h"
#include "GameSound.h"
#include "Player.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"

//�萔��
namespace {

	static const float HIGH_VALUME_INDEX = 1.0f;
	static const float MIDDLE_VALUME_INDEX = 0.4f;
	static const float LOW_VALUME_INDEX = 0.3f;

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

	//�����f�[�^������
	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{
		m_enemyLengthDatas[enemyNo].m_enemyData 
			= &m_sharedWarriorDatas->m_warriorDatas[enemyNo]->GetEnemyPtr();

		m_enemyLengthDatas[enemyNo].m_length = 0.0f;

		m_enemyLengthDatas[enemyNo].m_priority = en_priority_non;
	}

	LengthCalc();

	DatasPriorityInit();
}

//�����v�Z
void WarriorAIMetaFootSteps::LengthCalc()
{

	//�G�l�~�[�S�̂̃v���C���[�Ƃ̋����𑪂�
	for (int enemyNo = 0; enemyNo < m_enemyNum; enemyNo++)
	{
		
		Vector3 diff = m_player->GetPosition() 
			- m_sharedWarriorDatas->m_warriorDatas[enemyNo]->GetEnemyPtr().GetPosition();

		m_enemyLengthDatas[enemyNo].m_length = diff.Length();

	}	

}

void WarriorAIMetaFootSteps::DatasPriorityInit()
{

	EnemyLength_Data* highData = nullptr;
	EnemyLength_Data* lowData = nullptr;
	std::vector<EnemyLength_Data*> middleData;
	
	//�܂��擪�v�f�̃G�l�~�[����ԋ߂��G�l�~�[�Ɖے�����
	//�����Ċi�[�����f�[�^�Ƃق��̃f�[�^��
	//��ׂď���������high�ɑ������
	//low����̓�������
	highData = &m_enemyLengthDatas[0];
	lowData = &m_enemyLengthDatas[0];
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{
		if (highData->m_length
			> m_enemyLengthDatas[enemyNo].m_length)
			highData = &m_enemyLengthDatas[enemyNo];

		if (lowData->m_length
			< m_enemyLengthDatas[enemyNo].m_length)
			lowData = &m_enemyLengthDatas[enemyNo];
	}

	//�����Ă���ȊO�̃f�[�^��middle�Ɏw��
	for (int enemyNo = 0;
		enemyNo < m_enemyNum;
		enemyNo++)
	{
		if (&m_enemyLengthDatas[enemyNo] == highData ||
			&m_enemyLengthDatas[enemyNo] == lowData)
			continue;
		else
			middleData.push_back(&m_enemyLengthDatas[enemyNo]);
	}

	//�ŏI�ݒ�
	highData->m_enemyData->SetFootStepValumeCalcValue(HIGH_VALUME_INDEX);

	lowData->m_enemyData->SetFootStepValumeCalcValue(LOW_VALUME_INDEX);

	for (auto& listData : middleData)
	{
		listData->m_enemyData->SetFootStepValumeCalcValue(MIDDLE_VALUME_INDEX);
	}
}

//�����I��
const bool WarriorAIMetaFootSteps::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}

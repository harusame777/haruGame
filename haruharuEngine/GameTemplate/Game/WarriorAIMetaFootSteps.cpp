#include "stdafx.h"
#include "WarriorAIMetaFootSteps.h"
#include "GameSound.h"
#include "Player.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"

namespace {

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

	LengthCalc();
}

//�����v�Z
void WarriorAIMetaFootSteps::LengthCalc()
{

	EnemyFootValumeData datas[3];

	int enemyNum = 3;

	//�G�l�~�[�S�̂̃v���C���[�Ƃ̋����𑪂�
	for (int enemyNo = 0; enemyNo < enemyNum; enemyNo++)
	{
		
		Vector3 diff = m_player->GetPosition() 
			- m_sharedWarriorDatas->m_warriorDatas[enemyNo]->GetEnemyPtr().GetPosition();

		datas[enemyNo].m_distance = diff.Length();

	}

	for ()
	{



	}

}

//�����I��
const bool WarriorAIMetaFootSteps::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}

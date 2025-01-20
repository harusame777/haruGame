#include "stdafx.h"
#include "WarriorAIMetaFootSteps.h"
#include "GameSound.h"
#include "Player.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"

namespace {

}

//メタAIの初期化
void WarriorAIMetaFootSteps::MetaAIInit()
{
	m_player = FindGO<Player>("player");
}

//メタAIの実行
void WarriorAIMetaFootSteps::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	LengthCalc();
}

//距離計算
void WarriorAIMetaFootSteps::LengthCalc()
{

	EnemyFootValumeData datas[3];

	int enemyNum = 3;

	//エネミー全体のプレイヤーとの距離を測る
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

//処理終了
const bool WarriorAIMetaFootSteps::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}

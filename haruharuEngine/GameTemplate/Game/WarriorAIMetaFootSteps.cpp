#include "stdafx.h"
#include "WarriorAIMetaFootSteps.h"
#include "GameSound.h"
#include "Player.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"

//定数等
namespace {

	static const float HIGH_VALUME_INDEX = 1.0f;
	static const float MIDDLE_VALUME_INDEX = 0.4f;
	static const float LOW_VALUME_INDEX = 0.3f;

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

	//エネミーの数取得
	m_enemyNum = m_sharedWarriorDatas->m_warriorDatas.size();

	//距離データ初期化
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

//距離計算
void WarriorAIMetaFootSteps::LengthCalc()
{

	//エネミー全体のプレイヤーとの距離を測る
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
	
	//まず先頭要素のエネミーを一番近いエネミーと課程する
	//そして格納したデータとほかのデータを
	//比べて小さい方をhighに代入する
	//lowも大体同じ処理
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

	//そしてそれ以外のデータをmiddleに指定
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

	//最終設定
	highData->m_enemyData->SetFootStepValumeCalcValue(HIGH_VALUME_INDEX);

	lowData->m_enemyData->SetFootStepValumeCalcValue(LOW_VALUME_INDEX);

	for (auto& listData : middleData)
	{
		listData->m_enemyData->SetFootStepValumeCalcValue(MIDDLE_VALUME_INDEX);
	}
}

//処理終了
const bool WarriorAIMetaFootSteps::ProcessEnd(EnemySMBase* initEnemy)
{
	return true;
}

#include "stdafx.h"
#include "WarriorAIMetapPatrol.h"
#include "Player.h"

//定数等
namespace {
	/// <summary>
	/// ウォリアーの最大数
	/// </summary>
	static const int WARRIOR_NUM = 3;
}

//メタAIの初期化
void WarriorAIMetapPatrol::MetaAIInit()
{
	//レベルレンダーを使用して巡回地点を取得する
	m_levelRender.Init("Assets/mapLevel/testLevel3.tkl", [&](LevelObjectData_Render& objData)
		{
			if (objData.ForwardMatchName(L"patrolroute") == true)
			{
				MetaAIPatrolRuteData* newData = new MetaAIPatrolRuteData;

				//レベルから位置を取得する
				newData->m_patrolPos = objData.m_position;

				//配列に格納する
				m_patrolRuteList.push_back(newData);

				return true;
			}
			return true;
		});

	//プレイヤーのインスタンスを取得する
	m_player = FindGO<Player>("player");
}

//メタAIの実行
void WarriorAIMetapPatrol::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;
}

void WarriorAIMetapPatrol::WarriorRangeCalc()
{
	//プレイヤーの位置を取得
	Vector3 playerPos = m_player->GetPosition();
	//ウォリアーの位置を取得する変数を宣言
	Vector3 warriorPos;
	//ウォリアーからプレイヤーに伸びるベクトル
	Vector3 warriorToPlayerVec;
	//ウォリアーとプレイヤーの距離
	float warriorToPlayerDis;
	//距離比較用変数
	float distanceComparisonMax = 0.0f;

	//ウォリアーの全体の距離を測り配列に格納する
	for (int i = 0; i < WARRIOR_NUM; i++)
	{



		//ウォリアーの位置を取得
		warriorPos = m_sharedWarriorDatas->m_warriorDatas[i]->GetEnemyPtr().GetPosition();

		//まずウォリアーからプレイヤーに伸びるベクトルを計算
		warriorToPlayerVec = playerPos - warriorPos;

		//ウォリアーからプレイヤーに伸びるベクトルから距離を計算
		warriorToPlayerDis = warriorToPlayerVec.Length();

		m_warriorDistanceList[i] = warriorToPlayerDis;

	}

	//距離リストの中身を降順に並べ替える
	//配列のサイズを取得する
	int listSize = sizeof(m_warriorDistanceList) / sizeof(m_warriorDistanceList[0]);

	//降順に並べ替える
	std::sort(m_warriorDistanceList,
		m_warriorDistanceList + listSize, std::greater<float>());

	

}
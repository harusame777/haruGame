#include "stdafx.h"
#include "EnemyAIMovePatrol.h"
#include "Player.h"
#include "EnemyBase.h"

//定数等
namespace {
	float LEAVE_OR_CLOSER_DIFF = 1500.0f;
}

//スタート関数
void EnemyAIMovePatrol::EnemyAIStart()
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

//アップデート関数
void EnemyAIMovePatrol::EnemyAIUpdate()
{

}

void EnemyAIMovePatrol::WarriorRangeCalc()
{
	//プレイヤーの座標
	Vector3 playerPos = m_player->GetPosition();
	//ウォリアーの位置を取得する変数を宣言
	Vector3 warriorPos;
	//ウォリアーとプレイヤーの距離
	float warriorToPlayerDis;
	
	//距離を計算
	warriorToPlayerDis = (playerPos - warriorPos).Length();

	if (warriorToPlayerDis < LEAVE_OR_CLOSER_DIFF)
	{

	}
	else
	{
		//プレイヤーから近い巡回ルートを探す
		SearchRute(SearchMode::en_Near);
	}

}

void EnemyAIMovePatrol::SearchRute(const SearchMode mode)
{

	//プレイヤーの座標
	Vector3 playerPos = m_player->GetPosition();
	//
	float ruteToPlayerDiff;
	//
	MetaAIPatrolRuteData* confirmedRute = nullptr;

	float confirmedDiff;

	for (auto& ptr : m_patrolRuteList)
	{
		
		if (ptr->m_isUse == true)
		{
			continue;
		}

		ruteToPlayerDiff = (playerPos - ptr->m_patrolPos).Length();

		if (mode == SearchMode::en_Near)
		{
			if (confirmedRute == nullptr
				|| ruteToPlayerDiff < confirmedDiff)
			{
				confirmedRute = ptr;

				confirmedDiff = ruteToPlayerDiff;
			}
		}
		else
		{
			if (confirmedRute == nullptr
				|| ruteToPlayerDiff > confirmedDiff)
			{
				confirmedRute = ptr;

				confirmedDiff = ruteToPlayerDiff;
			}
		}

	}

	if (confirmedRute != nullptr)
	{
		confirmedRute->m_isUse = true;

		GetEnemyPtr().SetMoveTargetPosition(confirmedRute->m_patrolPos);
	}
}
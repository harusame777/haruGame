#include "stdafx.h"
#include "WarriorAIMetapPatrol.h"
#include "Player.h"

//定数等
namespace {
	/// <summary>
	/// ウォリアーの最大数
	/// </summary>
	static const int WARRIOR_NUM = 3;
	float LEAVE_OR_CLOSER_DIFF = 1500.0f;
}

//メタAIの初期化
void WarriorAIMetapPatrol::MetaAIInit()
{
	//プレイヤーのインスタンスを取得する
	m_player = FindGO<Player>("player");
}

//メタAIの実行
void WarriorAIMetapPatrol::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	WarriorRangeCalc();
}

void WarriorAIMetapPatrol::WarriorRangeCalc()
{
	//プレイヤーの座標
	Vector3 playerPos = m_player->GetPosition();
	//ウォリアーの位置を取得する変数を宣言
	Vector3 warriorPos = m_MainCallWarrior->GetEnemyPtr().GetPosition();
	//ウォリアーとプレイヤーの距離
	float warriorToPlayerDis;

	//距離を計算
	warriorToPlayerDis = (playerPos - warriorPos).Length();

	if (warriorToPlayerDis < LEAVE_OR_CLOSER_DIFF)
	{
		//プレイヤーから遠い巡回ルートを探す
		SearchRute(SearchMode::en_Far);
	}
	else
	{
		//プレイヤーから近い巡回ルートを探す
		SearchRute(SearchMode::en_Near);
	}

}

void WarriorAIMetapPatrol::SearchRute(const SearchMode mode)
{

	//プレイヤーの座標
	Vector3 playerPos = m_player->GetPosition();
	//ゴール地点からプレイヤーまでの距離
	float ruteToPlayerDiff;
	//確定したパトロールルートのデータ
	PatrolRuteDataHolder::PatrolRuteData* confirmedRute = nullptr;
	//確定した距離
	float confirmedDiff;

	//ルートの数ぶん回す
	for (auto& ptr : m_sharedPatrolRuteDatas->m_patrolRuteList)
	{

		//そのパトロールルートが使用中だったら
		if (ptr->GetIsUse() == true)
		{
			//処理を飛ばす
			continue;
		}

		//ゴール地点からプレイヤーまでの距離を計算する
		ruteToPlayerDiff = (playerPos - ptr->GetPosition()).Length();

		//モードが近距離モードだったら
		if (mode == SearchMode::en_Near)
		{
			//データが未入力状態であるまたは、
			//既に入力された距離より近かったら
			if (confirmedRute == nullptr
				|| ruteToPlayerDiff < confirmedDiff)
			{
				//現在のポインタのデータを入力して
				confirmedRute = ptr;

				//距離を代入する
				confirmedDiff = ruteToPlayerDiff;
			}
		}
		//モードが遠距離モードだったら
		else if (mode == SearchMode::en_Far)
		{
			//データが未入力状態であるまたは、
			//既に入力された距離より遠かったら
			if (confirmedRute == nullptr
				|| ruteToPlayerDiff > confirmedDiff)
			{
				//現在のポインタのデータを入力して
				confirmedRute = ptr;

				//距離を代入する
				confirmedDiff = ruteToPlayerDiff;
			}
		}

	}

	//もしデータが未入力状態じゃなかったら
	if (confirmedRute != nullptr)
	{
		//そのルートを使用中にして
		confirmedRute->SetIsUse(true);

		//追跡地点をエネミーに送る
		m_MainCallWarrior->GetEnemyPtr().SetMoveTargetPosition(confirmedRute->GetPosition());
	}
}

void WarriorAIMetapPatrol::ProcessEnd()
{

	for (auto& ptr : m_sharedPatrolRuteDatas->m_patrolRuteList)
	{

		if (m_MainCallWarrior == ptr->GetUseEnemyPtr())
		{
			ptr->SetIsUse(false);
			SetProcessEndFlag(true);
		}

	}

}
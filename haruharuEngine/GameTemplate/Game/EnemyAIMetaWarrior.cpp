#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"
#include "Player.h"

//処理順
//
//1.プレイヤーを見つける
//
//2.自分の周りのエネミーに呼びかける
//
//3.呼びかけに気づいてくれた自分以外のエネミーの現在のステートを取得する
//
//4.自分のステート取得し、自分以外のエネミーのステートと見比べる
//
//5.結果によってステートの番号を返す
//
//どのタイミングで追跡ステートを変更するか？
//エネミーがプレイヤーに気づいて周囲に呼びかけを行ったタイミングで実行したい
//追跡中にほかのエネミーが気づいたりしたら、強制的に後ろを追うようにする。

namespace {
	/// <summary>
	/// ウォリアーの最大数
	/// </summary>
	static const int WARRIOR_NUM = 3;
	/// <summary>
	/// 半径計算用のやつ
	/// </summary>
	static const float CALL_RANGE_CALC = 100000.0f;
}

//スタート関数
bool EnemyAIMetaWarrior::Start()
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

	return true;
}

//ウォリアー全体の追跡ステートを変更する関数
void EnemyAIMetaWarrior::MetaAIExecution(EnemySM_Warrior* enemyPtr, const MetaAIMode setMode)
{

	//現在何かしらの処理中だったら
	if (m_isCurrentlyProcessed == true)
	{
		return;
	}
	else
	{
		//処理中にする
		m_isCurrentlyProcessed = true;
	}

	//この関数を呼び出したエネミーのポインタを格納する
	m_MainCallWarrior = enemyPtr;

	switch (m_nowMetaAIMode)
	{
	case EnemyAIMetaWarrior::mode_trackingStateChange:
		//周囲に呼びかけを行う
		CallWarrior();
		break;
	case EnemyAIMetaWarrior::mode_patrolRouteSet:
		break;
	default:
		break;
	}

}

//リストにウォリアーを代入
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//データを作成
	MetaAIWarriorData* initData = new MetaAIWarriorData;
	//エネミーのポインタを格納
	initData->m_warriorPtr = enemyPtr;
	//リストにウォリアーを代入する
	m_sharedWarriorDatas->m_warriorDatas.push_back(initData);
}

////////////////////////////////////////mode_trackingStateChange処理

void EnemyAIMetaWarrior::CallWarrior()
{

	if (m_enemyWarriorList[0] == nullptr)
	{
		return;
	}

	//まず呼びかけを行ったウォリアーの周囲にウォリアーが存在するか
	//を調べる
	Vector3 callEnemyPos = m_MainCallWarrior->GetEnemyPtr().GetPosition();
	Vector3 enemyPos;
	Vector3 faceVector;
	float len;
	
	//範囲for文で回す
	for (auto& ptr : m_enemyWarriorList)
	{
		//自分のアドレスと同じだったら
		if (m_MainCallWarrior == ptr->m_warriorPtr)
		{
			//処理を飛ばす
			continue;
		}

		//ウォリアーの位置を取得
		enemyPos = ptr->m_warriorPtr->GetEnemyPtr().GetPosition();

		//呼びかけをしたウォリアーの位置と減算を行って
		//呼びかけをしたウォリアーから周囲のウォリアーの座標に向かって伸びる
		//ベクトルを作る
		faceVector = enemyPos - callEnemyPos;
		//長さの2乗に変換
		len = faceVector.LengthSq();

		//もし250.0f圏内にウォリアーがいたら
		if (len < CALL_RANGE_CALC * CALL_RANGE_CALC)
		{		
			ptr->m_isCallCompliedWarrior = true;
		}
	}

	//エネミー全体の追跡ステートを変更する
	ChangeTrackingState();
}

void EnemyAIMetaWarrior::ChangeTrackingState()
{

	//もう回り込みステートのエネミーが存在しているか
	bool existsWrapAroundWarrior = false;

	//第一発見エネミーはとりあえず後ろから追わせる
	m_MainCallWarrior->SetTrackingState(WarriorTrackingState::en_chaseFromBehind);

	//範囲for文で回す
	for (auto& ptr : m_enemyWarriorList)
	{

		//自分のアドレスと同じだったら
		if (m_MainCallWarrior == ptr->m_warriorPtr)
		{
			//処理を飛ばす
			continue;
		}
		
		//イテレーターのウォリアーが呼びかけられたウォリアーだったら
		if (ptr->m_isCallCompliedWarrior == true)
		{
			//回り込みステートのウォリアーが存在していたら
			if (existsWrapAroundWarrior == true)
			{
				//後ろから追わせる
				ptr->m_warriorPtr->SetTrackingState(WarriorTrackingState::en_wrapAround);
				ptr->m_warriorPtr->SetState(EnemySM_Warrior::en_warrior_trackingMetaAI);
				continue;
			}
			//回り込みステートのウォリアーがまだ存在しなかったら

			//回り込ませる
			ptr->m_warriorPtr->SetTrackingState(WarriorTrackingState::en_wrapAround);
			ptr->m_warriorPtr->SetState(EnemySM_Warrior::en_warrior_trackingMetaAI);

			//フラグをtrueに
			existsWrapAroundWarrior = true;
		}

	}

}

////////////////////////////////////////

void EnemyAIMetaWarrior::WarriorRangeCalc()
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
		warriorPos = m_enemyWarriorList[i]->m_warriorPtr->GetEnemyPtr().GetPosition();

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
		m_warriorDistanceList + listSize,std::greater<float>());



}

void EnemyAIMetaWarrior::ProcessEnd()
{
	//処理フラグを終了にして
	m_isCurrentlyProcessed = false;

	//全員の追跡ステートを非追跡状態にする
	for (auto& ptr : m_enemyWarriorList)
	{
		ptr->m_warriorPtr->SetTrackingState(WarriorTrackingState::en_nonTracking);
	}
}
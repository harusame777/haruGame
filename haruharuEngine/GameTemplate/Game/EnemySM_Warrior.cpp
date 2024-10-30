#include "stdafx.h"
#include "EnemySM_Warrior.h"
#include "EnemyAIConSearch.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyAIConWaitTime.h"
#include "EnemyAIConColPlayer.h"
#include "EnemyAIMetaWarrior.h"

//スタート関数
void EnemySM_Warrior::EnemyAIStart()
{
	//AIのListをこのエネミーに必要な物で初期化する
	//経路探索
	m_enemyAIList.push_back(new EnemyAIMoveAstar);

	//紐づいているエネミーのインスタンスをAIListのプログラムに渡す
	for (auto& listPtr : m_enemyAIList)
	{
		listPtr->BinedEnemy(m_enemy);
	}

	//AIListの中のプログラムのスタート関数を起動する
	for (auto& listPtr : m_enemyAIList)
	{
		listPtr->EnemyAIStart();
	}

	//分岐のプログラムをリストに格納していく
	//視界探索
	m_enemyConList.push_back(new EnemyAIConSearch);

	//10秒タイマー
	m_enemyConList.push_back(new EnemyAIConWaitTime(10.0f));

	//プレイヤーとの衝突判定
	m_enemyConList.push_back(new EnemyAIConColPlayer);

	//紐づいているエネミーのインスタンスをConListのプログラムに渡す
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->BinedEnemy(m_enemy);
	}

	//ConListの中のプログラムのスタート関数を起動する
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->Start();
	}

	//メタAIのインスタンスを格納
	m_warriorMetaAI = FindGO<EnemyAIMetaWarrior>("MetaAI");
	//メタAIにエネミーのインスタンスを送る
	m_warriorMetaAI->ListInitEnemy(this);
}

//アップデート関数
void EnemySM_Warrior::EnemyAIUpdate()
{
	//時間更新
	TimeUpdate();

	switch (m_warriorState)
	{
		//待機ステート
	case EnemySM_Warrior::en_warrior_idle:
		//別のステートにする
		ChangeState();
		break;
		//追跡ステート
	case EnemySM_Warrior::en_warrior_tracking:
		//追跡するかしないか
		if (!m_isTrackingTimeOver)
		{
			//別のステートにする
			ChangeState();
		}
		//10秒経っていなかったら
		else
		{
			//追跡処理を更新
			m_enemyAIList[0]->EnemyAIUpdate();
		}
		break;
	case EnemySM_Warrior::en_warrior_trackingMetaAI:
		//追跡を開始する
		StateTransition_Tracking();
		break;
	default:
		break;
	}

}

//共通ステート変更関数
void EnemySM_Warrior::ChangeState()
{
	//プレイヤーとの接触判定
	if (m_enemyConList[2]->Execution())
	{

	}

	//待機ステートにする
	SetState(WarriorState::en_warrior_idle);

	//もし追跡ステートじゃなくて
	if (m_warriorState != WarriorState::en_warrior_tracking)
	{
		//視界内にプレイヤーがいて尚且つプレイヤーとの間に壁が無かったら
		if (m_enemyConList[0]->Execution())
		{
			StateTransition_Tracking();
		}
	}
}

void EnemySM_Warrior::StateTransition_Tracking()
{
	//[テスト]メタAIから指示をもらう
	m_warriorMetaAI->MetaAIExecution(this);
	//追跡ステートにする
	SetState(WarriorState::en_warrior_tracking);
	//追跡するように
	m_isTracking = true;
	m_isTrackingTimeOver = true;
	//追跡時間を初期化
	m_enemyConList[1]->Start();
}

//時間処理
void EnemySM_Warrior::TimeUpdate()
{
	//現在のステートが追跡状態だったら
	if (m_warriorState == WarriorState::en_warrior_tracking)
	{
		//追跡タイマーを更新して
		//残り秒数が0.0だったら
		if (m_enemyConList[1]->Execution())
		{
			//追跡から別のステートにするようにして
			m_isTracking = false;
			m_isTrackingTimeOver = false;
			//追跡時間を初期化
			m_enemyConList[1]->Start();
			//メタAIのプロセスを終了する
			m_warriorMetaAI->ProcessEnd();
		}
	}
}



#include "stdafx.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"
#include "EnemyAIConSearch.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyAIConWaitTime.h"

//スタート関数
void EnemySM_Warrior::Start()
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
		listPtr->Start();
	}

	//分岐のプログラムをリストに格納していく
	//視界探索
	m_enemyConList.push_back(new EnemyAIConSearch);

	//10秒タイマー
	m_enemyConList.push_back(new EnemyAIConWaitTime(10.0f));

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
}

//アップデート関数
void EnemySM_Warrior::Update()
{
	switch (m_warriorState)
	{
		//待機ステート
	case EnemySM_Warrior::en_warrior_idle:
		//別のステートにする
		ChangeState();
		break;
		//追跡ステート
	case EnemySM_Warrior::en_warrior_tracking:
		//10秒待機
		//10秒経っていたら
		if (m_enemyConList[1]->Execution())
		{
			//別のステートにする
			ChangeState();
		}
		//10秒経っていなかったら
		else
		{
			//追跡処理を更新
			m_enemyAIList[0]->Update();
		}
		break;
	default:
		break;
	}
}

//共通ステート変更関数
void EnemySM_Warrior::ChangeState()
{
	//待機ステートにする
	m_warriorState = WarriorState::en_warrior_idle;

	//もし追跡ステートじゃなくて
	if (m_warriorState != WarriorState::en_warrior_tracking)
	{
		//視界内にプレイヤーがいて尚且つプレイヤーとの間に壁が無かったら
		if (m_enemyConList[0]->Execution())
		{
			//追跡ステートにする
			m_warriorState = WarriorState::en_warrior_tracking;
		}
	}
}
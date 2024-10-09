#include "stdafx.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"
#include "EnemyAIConSearch.h"
#include "EnemyAIMoveAstar.h"

//スタート関数
void EnemySM_Warrior::Start()
{
	//AIのListをこのエネミーに必要な物で初期化する
	//経路探索
	m_EnemyAIList.push_back(new EnemyAIMoveAstar);

	//紐づいているエネミーのインスタンスをAIListのプログラムに渡す
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->BinedEnemy(m_enemy);
	}

	//AIListの中のプログラムのスタート関数を起動する
	for (auto& listPtr : m_EnemyAIList)
	{
		listPtr->Start();
	}

	//分岐のプログラムをリストに格納していく
	//視界探索
	m_enemyConList.push_back(new EnemyAIConSearch);

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

}

//共通ステート変更関数
void EnemySM_Warrior::ChangeState()
{
	
}
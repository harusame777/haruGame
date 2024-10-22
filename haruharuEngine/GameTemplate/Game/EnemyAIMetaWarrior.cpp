#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"

namespace {
	/// <summary>
	/// エネミーの最大数
	/// </summary>
	static const int WARRIOR_NUM = 3;
}

//スタート関数
bool EnemyAIMetaWarrior::Start()
{
	//リストのサイズをエネミーの数でリサイズ
	m_enemyWarriorList.resize(WARRIOR_NUM);
}

//アップデート関数
void EnemyAIMetaWarrior::Update()
{

	//エネミーが１体でも追跡中だったら
	if (SearchEnemyTracking())
	{
		//エネミー全体の追跡ステートを変更する
		ChangeTrackingState();
	}

}

//エネミー全体の追跡ステートを変更する関数
void EnemyAIMetaWarrior::ChangeTrackingState()
{

}

//リストにエネミーを代入
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//リストにエネミーを代入する
	m_enemyWarriorList.push_back(enemyPtr);
}

const bool EnemyAIMetaWarrior::SearchEnemyTracking() const
{
	for (auto& ptr: m_enemyWarriorList)
	{
		if (ptr->IsTracking())
		{
			return true;
		}
	}

	return false;
}

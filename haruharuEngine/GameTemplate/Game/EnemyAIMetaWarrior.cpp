#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "WarriorAIMetaTracking.h"
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

//スタート関数
bool EnemyAIMetaWarrior::Start()
{

	//共通のデータホルダーを初期化
	m_warriorDataHolder = std::make_shared<WarriorDataHolder>();

	//メタAIの処理プログラムを初期化
	m_AIMetaList.push_back(new WarriorAIMetaTracking(m_warriorDataHolder));

	for (auto& metaAIs : m_AIMetaList)
	{
		//初期化
		metaAIs->MetaAIInit();
	}

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

	//処理を実行する
	m_AIMetaList[setMode]->MetaAIExecution(enemyPtr);
}

//リストにウォリアーを代入
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//リストにウォリアーを代入する
	m_warriorDataHolder->m_warriorDatas.push_back(enemyPtr);
}

void EnemyAIMetaWarrior::ProcessEnd()
{
	//処理フラグを終了にして
	m_isCurrentlyProcessed = false;

	//全員の追跡ステートを非追跡状態にする
	for (auto& ptr : m_warriorDataHolder->m_warriorDatas)
	{
		ptr->SetTrackingState(WarriorTrackingState::en_nonTracking);
	}
}
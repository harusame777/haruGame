#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"

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
	static const float CALL_RANGE_CALC = 250.0f;
}

//スタート関数
bool EnemyAIMetaWarrior::Start()
{
	//リストのサイズをウォリアーの数でリサイズ
	m_enemyWarriorList.resize(WARRIOR_NUM);

	return true;
}

//ウォリアー全体の追跡ステートを変更する関数
void EnemyAIMetaWarrior::MetaAIExecution(EnemySM_Warrior* enemyPtr)
{
	//まず呼びかけたエネミーのポインタを格納
	//念のため初期化
	m_MainCallWarrior = nullptr;
	m_MainCallWarrior = enemyPtr;
	//周囲に呼びかけを行う
	CallWarrior();
}

//リストにウォリアーを代入
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//データを作成
	MetaAIWarriorData* initData = new MetaAIWarriorData;
	//エネミーのポインタを格納
	initData->m_warriorPtr = enemyPtr;
	//リストにウォリアーを代入する
	m_enemyWarriorList.push_back(initData);
}

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
			}
			//回り込みステートのウォリアーがまだ存在しなかったら

			//回り込ませる
			ptr->m_warriorPtr->SetTrackingState(WarriorTrackingState::en_wrapAround);

			//フラグをtrueに
			existsWrapAroundWarrior = true;
		}

	}

}
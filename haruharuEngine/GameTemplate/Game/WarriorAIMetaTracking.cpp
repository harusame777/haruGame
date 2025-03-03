#include "stdafx.h"
#include "WarriorAIMetaTracking.h"
#include "EnemySMBase.h"

//定数等
namespace {
	/// <summary>
	/// ウォリアーの最大数
	/// </summary>
	static const int WARRIOR_NUM = 3;
	/// <summary>
	/// 半径計算用のやつ
	/// </summary>
	static const float CALL_RANGE_CALC = 750.0f;
}

//メタAI初期化
void WarriorAIMetaTracking::MetaAIInit()
{

}

//メタAI実行
void WarriorAIMetaTracking::MetaAIExecution(EnemySMBase* initEnemy)
{
	m_MainCallWarrior = initEnemy;

	CallWarrior();
}

//周辺ウォリアーに呼び掛け
void WarriorAIMetaTracking::CallWarrior()
{

	if (m_sharedWarriorDatas->m_warriorDatas[0] == nullptr)
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
	for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
	{
		//自分のアドレスと同じだったら
		if (m_MainCallWarrior == ptr)
		{
			//処理を飛ばす
			continue;
		}

		//ウォリアーの位置を取得
		enemyPos = ptr->GetEnemyPtr().GetPosition();

		//呼びかけをしたウォリアーの位置と減算を行って
		//呼びかけをしたウォリアーから周囲のウォリアーの座標に向かって伸びる
		//ベクトルを作る
		faceVector = enemyPos - callEnemyPos;
		//長さの2乗に変換
		len = faceVector.LengthSq();

		//もし250.0f圏内にウォリアーがいたら
		if (len < CALL_RANGE_CALC * CALL_RANGE_CALC)
		{
			ptr->SetCallMetaAI(true);
		}
	}

	//エネミー全体の追跡ステートを変更する
	ChangeTrackingState();
}

void WarriorAIMetaTracking::ChangeTrackingState()
{

	//もう回り込みステートのエネミーが存在しているか
	bool existsWrapAroundWarrior = false;

	//範囲for文で回す
	for (auto& ptr : m_sharedWarriorDatas->m_warriorDatas)
	{

		//自分のアドレスと同じだったら
		if (m_MainCallWarrior == ptr)
		{
			ptr->SetTrackingState(WarriorTrackingState::en_chaseFromBehind);
			//処理を飛ばす
			continue;
		}

		//イテレーターのウォリアーが呼びかけられたウォリアーだったら
		if (ptr->GetCallMetaAI() == true)
		{
			//回り込みステートのウォリアーが存在していたら
			if (existsWrapAroundWarrior == true)
			{
				//後ろから追わせる
				ptr->SetTrackingState(WarriorTrackingState::en_usually);
				ptr->SetState(EnemySM_Warrior::en_warrior_trackingMetaAI);
				continue;
			}
			//回り込みステートのウォリアーがまだ存在しなかったら

			//回り込ませる
			ptr->SetTrackingState(WarriorTrackingState::en_wrapAround);
			ptr->SetState(EnemySM_Warrior::en_warrior_trackingMetaAI);

			//フラグをtrueに
			existsWrapAroundWarrior = true;
		}

	}

}

//処理終了処理
const bool WarriorAIMetaTracking::ProcessEnd(EnemySMBase* initEnemy)
{
	
	//自分の追跡ステートを初期化
	m_MainCallWarrior = initEnemy;

	int num = 0;

	for (auto & ptr : m_sharedWarriorDatas->m_warriorDatas)
	{
		if (&m_MainCallWarrior->GetEnemyPtr() == &ptr->GetEnemyPtr())
		{
			ptr->SetTrackingState(WarriorTrackingState::en_nonTracking);
		}

		if (ptr->GetEnemyPtr().GetTrackingStateNumber() == WarriorTrackingState::en_nonTracking)
		{
			num++;
		}
	}

	if (num >= 3)
	{
		//すべての処理が終了したと返す
		return true;
	}

	return false;

}
#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"
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
	//周囲に呼びかけを行う
	CallWarrior(enemyPtr);
}

//リストにウォリアーを代入
void EnemyAIMetaWarrior::ListInitEnemy(EnemySM_Warrior* enemyPtr)
{
	//リストにウォリアーを代入する
	m_enemyWarriorList.push_back(enemyPtr);
}

void EnemyAIMetaWarrior::CallWarrior(EnemySM_Warrior* enemyPtr)
{
	//クリアする
	m_CallRespondWarriorList.clear();

	//まず呼びかけを行ったウォリアーの周囲にウォリアーが存在するか
	//を調べる
	Vector3 callEnemyPos = enemyPtr->GetEnemyPtr().GetPosition();
	Vector3 enemyPos;
	Vector3 faceVector;
	float len;
	
	//範囲for文で回す
	for (auto& ptr : m_enemyWarriorList)
	{
		//もし今のポインタが自分だったら
		if (enemyPtr == ptr)
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
			//呼びかける、専用の配列にポインタを格納
			m_CallRespondWarriorList.push_back(ptr);
		}
	}

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

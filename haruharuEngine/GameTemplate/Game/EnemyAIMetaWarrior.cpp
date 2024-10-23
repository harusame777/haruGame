#include "stdafx.h"
#include "EnemyAIMetaWarrior.h"
#include "EnemySM_Warrior.h"
#include "EnemyBase.h"
#include "EnemyWarriorTrackingState.h"

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
	//まず呼びかけを行ったウォリアーの周囲にウォリアーが存在するか
	//を調べる
	Vector3 callEnemyPos = m_MainCallWarrior->GetEnemyPtr().GetPosition();
	Vector3 enemyPos;
	Vector3 faceVector;
	float len;

	//呼ばれたエネミーのポインタを初期化
	m_subCalledWarriorFirst = nullptr;
	m_subCalledWarriorSecond = nullptr;
	
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
			//配列の呼びかけに応じたエネミーのポインタを変数に格納
			if (m_subCalledWarriorFirst == nullptr)
			{
				m_subCalledWarriorFirst = ptr->m_warriorPtr;
			}
			else
			{
				m_subCalledWarriorSecond = ptr->m_warriorPtr;
			}
		}
	}

	//エネミー全体の追跡ステートを変更する
	ChangeTrackingState();
}

void EnemyAIMetaWarrior::ChangeTrackingState()
{

	//セコンドがnullだったら
	if (m_subCalledWarriorSecond == nullptr)
	{
		//単体処理を行う
		if (m_subCalledWarriorFirst->GetEnemyPtr().GetTrackingStateNumber()
			== WarriorTrackingState::en_nonTracking)
		{
			//自身のウォリアーを通常追跡ステートに
			m_MainCallWarrior->GetEnemyPtr().SetTrackingStateNumber(WarriorTrackingState::en_chaseFromBehind);
			//ファーストを回り込みステートに
			m_subCalledWarriorFirst->GetEnemyPtr().SetTrackingStateNumber(WarriorTrackingState::en_wrapAround);
		}
		else if(m_subCalledWarriorFirst->GetEnemyPtr().GetTrackingStateNumber()
			== WarriorTrackingState::en_chaseFromBehind)
		{
			
		}
	}
	//nullじゃなかったら
	else
	{
		//複数処理を行う

	}

	//まず呼びかけに応じたリストのサイズを取得する
	
	////呼びかけに応じたエネミーが2体以上だったら
	//if (callWarriorNum >= 2)
	//{
	//	//2体の時の判定を行う
	//	if (m_CallRespondWarriorList[0]->GetEnemyPtr().GetTrackingStateNumber() ==
	//		WarriorTrackingState::en_nonTracking && 
	//		m_CallRespondWarriorList[1]->GetEnemyPtr().GetTrackingStateNumber() ==
	//		WarriorTrackingState::en_nonTracking)
	//	{

	//	}
	//}
	////違ったら
	//else
	//{
	//	//1体の時の判定を行う
	//	if (m_CallRespondWarriorList[0]->GetEnemyPtr().GetTrackingStateNumber() ==
	//		WarriorTrackingState::en_nonTracking)
	//	{
	//		m_MainCallWarrior->GetEnemyPtr().SetTrackingStateNumber(WarriorTrackingState::en_chaseFromBehind);
	//	}
	//}

}
#include "stdafx.h"
#include "EnemySM_Warrior.h"
#include "EnemyAIConSearch.h"
#include "EnemyAIConWallSearch.h"
#include "EnemyAIMoveAstar.h"
#include "EnemyAIMove.h"
#include "EnemyAIConWaitTime.h"
#include "EnemyAIConColPlayer.h"
#include "EnemyAIMetaWarrior.h"
#include "Player.h"
#include "Game.h"

//エネミー全体を管理するメタAIを作成して、追跡を管理したい
//
//1.エネミーが追跡を開始する際に、メタAIにエネミー全体を見て、共に追跡させる
//エネミーを選抜する関数を実行させる
//
//2.メタAIに選抜したエネミーから、普通に追うエネミーと、回り込みをかけるエネミーを
//分別させる。
//
//3.エネミーが追跡を開始する
//
//なおメタAIの処理は追跡開始の1回のみの処理とする
//
//おそらく追跡続行の処理がよくないので改良の必要アリ

//スタート関数
void EnemySM_Warrior::EnemyAIStart()
{
	//メタAIのインスタンスを格納
	m_warriorMetaAI = FindGO<EnemyAIMetaWarrior>("MetaAI");
	//メタAIにエネミーのインスタンスを送る
	m_warriorMetaAI->ListInitEnemy(this);

	//ゲームのインスタンス
	m_game = FindGO<Game>("game");

	//共通のデータホルダーを初期化
	m_warriorDataHolder = m_warriorMetaAI->GetEnemyDatas();

	//AIのListをこのエネミーに必要な物で初期化する
	//経路探索
	m_enemyAIList.push_back(new EnemyAIMoveAstar(m_warriorDataHolder));

	//通常移動
	m_enemyAIList.push_back(new EnemyAIMove);

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
	m_enemyConList.push_back(new EnemyAIConSearch(45.0f,500.0f));

	//10秒タイマー
	m_enemyConList.push_back(new EnemyAIConWaitTime(10.0f));

	//プレイヤーとの衝突判定
	m_enemyConList.push_back(new EnemyAIConColPlayer);

	//追跡時視界探索
	m_enemyConList.push_back(new EnemyAIConSearch(75.0f, 700.0f));

	//5秒タイマー
	m_enemyConList.push_back(new EnemyAIConWaitTime(5.0f));

	//15秒タイマー
	m_enemyConList.push_back(new EnemyAIConWaitTime(15.0f));

	//壁を探索
	m_enemyConList.push_back(new EnemyAIConWallSearch);

	//20秒タイマー
	m_enemyConList.push_back(new EnemyAIConWaitTime(25.0f));

	//紐づいているエネミーのインスタンスをConListのプログラムに渡す
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->BinedEnemy(m_enemy);
	}

	//ConListの中のプログラムのスタート関数を起動する
	for (auto& listPtr : m_enemyConList)
	{
		listPtr->InitData();
	}

	m_player = FindGO<Player>("player");
}

//アップデート関数
void EnemySM_Warrior::EnemyAIUpdate()
{
	if (m_warriorDataHolder->m_warriorDatas.size() == 0)
	{
		return;
	}

	//時間更新
	TimeUpdate();

	//足音を調整
	m_warriorMetaAI->MetaAIExecution(this, EnemyAIMetaWarrior::mode_footStep);


	switch (m_warriorState)
	{
		//待機ステート
	case EnemySM_Warrior::en_warrior_idle:

		m_enemy->SetPlayAnimationState(EnemyBase::en_idle);

		//別のステートにする
		ChangeState();
		break;
		//追跡ステート
	case EnemySM_Warrior::en_warrior_tracking:

		m_enemy->SetPlayAnimationState(EnemyBase::en_patrol);

		//もし退却状態じゃなかったら
		if (m_isRetreat == false)
		{
			Vector3 plaPos = m_player->GetPosition();

			GetEnemyPtr().SetMoveTargetPosition(plaPos);
		}
		else
		{
			//[テスト]メタAIから指示をもらう
			m_warriorMetaAI->MetaAIExecution(this, EnemyAIMetaWarrior::mode_retreat);
		}

		//追跡処理を更新
		m_enemyAIList[en_enemyAIMoveAstar]->EnemyAIUpdate();

		ChangeState();
		break;
	case EnemySM_Warrior::en_warrior_patrol:

		m_enemy->SetPlayAnimationState(EnemyBase::en_patrol);

		//巡回処理を更新して
		m_enemyAIList[en_enemyAIMoveAstar]->EnemyAIUpdate();
		//別のステートにする
		ChangeState();
		break;
	case EnemySM_Warrior::en_warrior_trackingMetaAI:
		//追跡を開始する
		StateTransition_Tracking();

		m_enemy->SetPlayAnimationState(EnemyBase::en_patrol);

		break;
	case EnemySM_Warrior::en_stop:

		m_enemy->SetPlayAnimationState(EnemyBase::en_idle);

		break;
	case EnemySM_Warrior::en_attack:

		m_enemy->SetPlayAnimationState(EnemyBase::en_attack);

		if (GetEnemyPtr().IsAnimationClipEnd() == true)
		{
			GetEnemyPtr().SetAnimationEnd(true);
		}

		break;
	default:
		break;
	}

}

//共通ステート変更関数
void EnemySM_Warrior::ChangeState()
{

	//プレイヤーとの接触判定
	if (m_enemyConList[en_enemyAIConColPlayer]->Execution())
	{
		if (GetEnemyPtr().GetAttackFlag())
		{
			return;
		}

		GetEnemyPtr().SetAttackFlag(true);

		m_warriorMetaAI->MetaAIExecution(this,EnemyAIMetaWarrior::mode_stop);

		SetState(WarriorState::en_attack);

		m_game->PlayerGameOver();

		return;
	}

	if (m_warriorState == WarriorState::en_warrior_tracking ||
		m_warriorState == WarriorState::en_warrior_trackingMetaAI &&
		m_isTrackingTimeOver == true)
	{
		return;
	}

	if (m_warriorState != WarriorState::en_warrior_idle)
	{

		float diff = (GetEnemyPtr().GetPosition() - GetEnemyPtr().GetMoveTargetPosition()).Length();

		if (diff < 200.0f)
		{
			//待機ステートにする
			SetState(WarriorState::en_warrior_idle);

			m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_patrolRouteSet,this);

			m_isWaitIdle = false;
		}
	}
	
	//もし巡回ステートじゃなくて
	if (m_warriorState != WarriorState::en_warrior_patrol)
	{
		//待機状態から5秒立っていたら
		if (m_isWaitIdle == true)
		{
			//[テスト]メタAIから指示をもらう
			m_warriorMetaAI->MetaAIExecution(this, EnemyAIMetaWarrior::mode_patrolRouteSet);
			//巡回ステートにする
			SetState(WarriorState::en_warrior_patrol);

			m_enemyConList[7]->InitData();

			m_isWaitIdle = false;
		}
	}


	//もし追跡ステートじゃなくて
	if (m_warriorState != WarriorState::en_warrior_tracking)
	{
		//視界内にプレイヤーがいて尚且つプレイヤーとの間に壁が無かったら
		if (m_enemyConList[en_enemyAIConSearch]->Execution())
		{
			m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_patrolRouteSet, this);

			StateTransition_Tracking();
		}
	}
}

void EnemySM_Warrior::StateTransition_Tracking()
{
	//今の状態だと、一度待機状態になった後にもう一度追跡状態になると、役割を何も持てないので、対策を検討する。
	//[テスト]メタAIから指示をもらう
	m_warriorMetaAI->MetaAIExecution(this,EnemyAIMetaWarrior::mode_trackingStateChange);
	//追跡ステートにする
	SetState(WarriorState::en_warrior_tracking);
	//追跡するように
	m_isTrackingTimeOver = true;
	//追跡時間を初期化
	m_enemyConList[en_enemyAIConWaitTime10f]->InitData();
}

//時間処理
void EnemySM_Warrior::TimeUpdate()
{

	if (m_isRetreat == true)
	{
		if (m_enemyConList[5]->Execution())
		{
			//[テスト]メタAIから指示をもらう
			m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_retreat, this);

			StateTransition_Tracking();

			m_isRetreat = false;
		}
	}
	else
	{
		//追跡時間を初期化
		m_enemyConList[5]->InitData();
	}

	if (m_warriorState == WarriorState::en_warrior_patrol)
	{
		//待機タイマーを更新して
		//残り秒数が0.0だったら
		if (m_enemyConList[7]->Execution())
		{
			//待機ステートにする
			SetState(WarriorState::en_warrior_idle);

			m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_patrolRouteSet, this);

			m_isWaitIdle = false;
		}
	}

	//現在のステートが待機状態だったら
	if (m_warriorState == WarriorState::en_warrior_idle)
	{
		//待機タイマーを更新して
		//残り秒数が0.0だったら
		if (m_enemyConList[4]->Execution())
		{
			//巡回にする
			m_isWaitIdle = true;
		}
	}
	else
	{
		//追跡時間を初期化
		m_enemyConList[4]->InitData();
	}

	//現在のステートが追跡状態だったら
	if (m_warriorState == WarriorState::en_warrior_tracking)
	{
		//プレイヤーが視角外にいて
		if (!m_enemyConList[3]->Execution())
		{
			//追跡タイマーを更新して
			//残り秒数が0.0だったら
			if (m_enemyConList[en_enemyAIConWaitTime10f]->Execution())
			{
				//追跡から別のステートにするようにして
				m_isTrackingTimeOver = false;
				//追跡時間を初期化
				m_enemyConList[en_enemyAIConWaitTime10f]->InitData();

				SetState(WarriorState::en_warrior_idle);

				//メタAIのプロセスを終了する
				m_warriorMetaAI->ProcessEnd(EnemyAIMetaWarrior::mode_trackingStateChange,this);
			}
		}
		else
		{
			//追跡時間を初期化
			m_enemyConList[en_enemyAIConWaitTime10f]->InitData();
		}
	}
}



#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"

class EnemyAIMetaWarrior;
class WarriorDataHolder;
class Player;

class EnemySM_Warrior : public EnemySMBase, public virtual EnemyAIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemySM_Warrior(){};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemySM_Warrior(){};
	/// <summary>
	/// エネミーウォリアーのステート
	/// </summary>
	enum WarriorState
	{
		//待機状態
		en_warrior_idle,
		//追跡状態
		en_warrior_tracking,
		//巡回状態
		en_warrior_patrol,
		//メタAI指令追跡状態
		en_warrior_trackingMetaAI,
	};
public:
	enum EnemyAINum
	{
		en_enemyAIMoveAstar
	};
	enum EnemyAIConNum
	{
		en_enemyAIConSearch,
		en_enemyAIConWaitTime10f,
		en_enemyAIConColPlayer
	};
	/// <summary>
	/// スタート関数
	/// </summary>
	void EnemyAIStart() override;
	/// <summary>
	/// アップデート関数
	/// </summary>
	void EnemyAIUpdate() override;
	/// <summary>
	/// 共通ステート変更関数
	/// </summary>
	void ChangeState() override;
	/// <summary>
	/// 時間処理関数
	/// </summary>
	void TimeUpdate();
	/// <summary>
	/// ステート遷移：追跡
	/// </summary>
	void StateTransition_Tracking();
	/// <summary>
	/// 追跡ステートナンバーを設定
	/// </summary>
	/// <param name="stateNum = ステートナンバー"></param>
	void SetTrackingState(const WarriorTrackingState setState)
	{
		GetEnemyPtr().SetTrackingStateNumber(setState);
		m_warriorTrackingState = setState;
	}
	/// <summary>
	/// 追跡ステートナンバーを取得
	/// </summary>
	/// <returns></returns>
	const WarriorTrackingState GetTrackingState()
	{
		return m_warriorTrackingState;
	}
	/// <summary>
	/// ステートナンバーを設定
	/// </summary>
	/// <param name="stateNum = ステートナンバー"></param>
	void SetState(const WarriorState setState)
	{
		GetEnemyPtr().SetStateNumber(setState);
		m_warriorState = setState;
	}
	/// <summary>
	/// ステートナンバーを取得
	/// </summary>
	/// <returns></returns>
	const WarriorState GetState()
	{
		return m_warriorState;
	}
	/// <summary>
	/// メタAIに呼ばれたかどうか
	/// </summary>
	/// <param name="setBool"></param>
	void SetCallMetaAI(const bool setBool)
	{
		m_isCallMetaAI = setBool;
	}
	/// <summary>
	/// メタAIに呼ばれたかどうか
	/// </summary>
	/// <returns></returns>
	const bool GetCallMetaAI()
	{
		
		return m_isCallMetaAI;
	}
private:
	/// <summary>
	/// エネミーウォリアーのステート、待機状態で初期化
	/// </summary>
	WarriorState m_warriorState = WarriorState::en_warrior_idle;
	/// <summary>
	/// エネミーウォリアーの追跡ステート、待機状態で非追跡状態
	/// </summary>
	WarriorTrackingState m_warriorTrackingState = WarriorTrackingState::en_nonTracking;
	/// <summary>
	/// 時間によって追跡し続けるかどうか
	/// </summary>
	bool m_isTrackingTimeOver = false;
	/// <summary>
	/// 待機状態か
	/// </summary>
	bool m_isWaitIdle = false;
	/// <summary>
	/// 
	/// </summary>
	bool m_isCallMetaAI = false;
	/// <summary>
	/// ウォリアーのメタAI
	/// </summary>
	EnemyAIMetaWarrior* m_warriorMetaAI;
	/// <summary>
	/// ウォリアーの共通データホルダ～
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
	Player* m_player = nullptr;
};


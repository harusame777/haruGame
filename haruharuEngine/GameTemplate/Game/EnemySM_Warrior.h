#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"

class EnemyAIMetaWarrior;

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
		//メタAI指令追跡状態
		en_warrior_trackingMetaAI,
	};
public:
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
	/// 追跡状態か？
	/// </summary>
	/// <returns></returns>
	const bool IsTracking() const
	{
		return m_isTracking;
	}
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
	/// 追跡状態かどうか
	/// </summary>
	bool m_isTracking = false;
	/// <summary>
	/// ウォリアーのメタAI
	/// </summary>
	EnemyAIMetaWarrior* m_warriorMetaAI;
};


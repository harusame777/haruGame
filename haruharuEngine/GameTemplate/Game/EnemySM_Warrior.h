#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"
#include "EnemyWarriorTrackingState.h"

class EnemyBase;
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
private:
	/// <summary>
	/// エネミーウォリアーのステート
	/// </summary>
	enum WarriorState
	{
		//待機状態
		en_warrior_idle,
		//追跡状態
		en_warrior_tracking,
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
	/// 追跡状態か？
	/// </summary>
	/// <returns></returns>
	const bool IsTracking() const
	{
		return m_isTracking;
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


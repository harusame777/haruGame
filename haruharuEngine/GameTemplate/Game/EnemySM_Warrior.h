#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"

class EnemyBase;

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
	void Start() override;
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update() override;
	/// <summary>
	/// 共通ステート変更関数
	/// </summary>
	void ChangeState() override;
	/// <summary>
	/// 時間処理
	/// </summary>
	void TimeUpdate();
private:
	/// <summary>
	/// エネミーウォリアーのステート、待機状態で初期化
	/// </summary>
	WarriorState m_warriorState = WarriorState::en_warrior_idle;
	/// <summary>
	/// 時間によって追跡し続けるかどうか
	/// </summary>
	bool m_isTrackingTimeOver = false;
};


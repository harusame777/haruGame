#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"
#include "EnemyWarriorTrackingState.h"
#include "EnemyBase.h"

class EnemyAIMetaWarrior;
class WarriorDataHolder;
class Player;
class Game;
class GameSound;

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
	~EnemySM_Warrior()
	{
		for (auto& listPtr : m_enemyAIList)
		{
			delete listPtr;
		}

		m_enemyAIList.clear();

		for (auto& listPtr : m_enemyConList)
		{
			delete listPtr;
		}

		m_enemyConList.clear();
	};
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
		//停止
		en_stop,
		//攻撃
		en_attack
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
	/// <summary>
	/// 退却するかしないか
	/// </summary>
	/// <param name="setBool"></param>
	void SetRetreat(const bool setBool)
	{
		m_isRetreat = setBool;
	}
	/// <summary>
	/// 退却するかしないか
	/// </summary>
	/// <returns></returns>
	const bool GetRetreat()
	{
		return m_isRetreat;
	}
private:
	/// <summary>
	/// エネミーウォリアーのステート、待機状態で初期化
	/// </summary>
	WarriorState m_warriorState = WarriorState::en_stop;
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
	/// 退却するかしないか
	/// </summary>
	bool m_isRetreat = false;
	/// <summary>
	/// ウォリアーのメタAI
	/// </summary>
	EnemyAIMetaWarrior* m_warriorMetaAI;
	/// <summary>
	/// ウォリアーの共通データホルダ〜
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// ゲームのインスタンス
	/// </summary>
	Game* m_game = nullptr;
	/// <summary>
	/// ゲームサウンドのインスタンス
	/// </summary>
	GameSound* m_gameSound = nullptr;
};


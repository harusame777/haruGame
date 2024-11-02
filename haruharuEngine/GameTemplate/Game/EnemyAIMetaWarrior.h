#pragma once
#include "WarriorDataHolder.h"

class EnemySM_Warrior;
class EnemyBase;
class Player;

class EnemyAIMetaWarrior : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAIMetaWarrior() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyAIMetaWarrior() {};
	/// <summary>
	///	メタAIのどのプログラムを起動するか
	/// </summary>
	enum MetaAIMode
	{
		/// <summary>
		///追跡ステート変更 
		/// </summary>
		mode_trackingStateChange,
		/// <summary>
		/// 巡回ルート設定
		/// </summary>
		mode_patrolRouteSet,
	};
	/// <summary>
	/// パトロールルートの種類
	/// </summary>
	enum PatrolRuteState
	{
		/// <summary>
		/// プレイヤーの近く
		/// </summary>
		en_playerToNear,
		/// <summary>
		/// マップの端の方
		/// </summary>
		en_goToEdge,
	};
	/// <summary>
	/// スタート関数
	/// </summary>
	bool Start();
	/// <summary>
	/// リストにエネミーを格納する
	/// </summary>
	/// <param name="enemyPtr"></param>
	void ListInitEnemy(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// メタAIを実行する関数
	/// </summary>
	void MetaAIExecution(EnemySM_Warrior* enemyPtr,const MetaAIMode setMode);
	/// <summary>
	/// ウォリアーに呼びかけを行う
	/// </summary>
	void CallWarrior();
	/// <summary>
	/// エネミー全体の追跡ステートを変更する関数
	/// </summary>
	void ChangeTrackingState();
	/// <summary>
	/// ウォリアーの距離を計算する関数
	/// </summary>
	void WarriorRangeCalc();
	/// <summary>
	/// 処理を終了する
	/// </summary>
	void ProcessEnd();
private:
	/// <summary>
	/// プレイヤーのインスタンスを格納する変数
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// メタAIのモード
	/// </summary>
	MetaAIMode m_nowMetaAIMode;
	/// <summary>
	/// メタAIに保存するエネミーのデータ
	/// </summary>
	struct MetaAIWarriorData
	{
		/// <summary>
		/// trueであれば呼びかけに応じたエネミー
		/// </summary>
		bool m_isCallCompliedWarrior = false;
		/// <summary>
		/// エネミーのポインタ
		/// </summary>
		EnemySM_Warrior* m_warriorPtr = nullptr;
	};
	/// <summary>
	/// メタAIの巡回ルートのデータ
	/// </summary>
	struct MetaAIPatrolRuteData
	{
		/// <summary>
		/// このルートを使用しているウォリアーが存在するか
		/// </summary>
		bool m_isUse = false;
		/// <summary>
		/// 終了地点
		/// </summary>
		Vector3 m_patrolPos;
	};
	struct DistanceListData	
	{
		/// <summary>
		/// 距離
		/// </summary>
		float Distance;
		/// <summary>
		/// ウォリアーのデータ
		/// </summary>
		EnemySM_Warrior* m_warriorData;

	};
	/// <summary>
	/// レベルレンダー
	/// </summary>
	LevelRender m_levelRender;
	/// <summary>
	/// 呼びかけたエネミー
	/// </summary>
	EnemySM_Warrior* m_MainCallWarrior = nullptr;
	/// <summary>
	/// エネミーウォリアーのリスト
	/// </summary>
	std::vector<MetaAIWarriorData*> m_enemyWarriorList;
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
	/// <summary>
	/// パトロールルートのリスト
	/// </summary>
	std::vector<MetaAIPatrolRuteData*> m_patrolRuteList;
	/// <summary>
	/// ウォリアーの距離リスト
	/// </summary>
	float m_warriorDistanceList[WARRIOR_NUM];
	/// <summary>
	/// 現在処理中かどうか
	/// </summary>
	bool m_isCurrentlyProcessed = false;
};


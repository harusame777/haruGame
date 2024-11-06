#pragma once
#include "EnemyAIMetaBase.h"

class EnemyBase;
class Player;

class WarriorAIMetapPatrol : public EnemyAIMetaBase
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WarriorAIMetapPatrol(std::shared_ptr<WarriorDataHolder> data) : EnemyAIMetaBase(data)
	{
		m_sharedWarriorDatas = data;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WarriorAIMetapPatrol() {};
	/// <summary>
	/// メタAIの初期化関数
	/// </summary>
	void MetaAIInit();
	/// <summary>
	/// メタAIの実行関数
	/// </summary>
	/// <param name="initEnemy"></param>
	void MetaAIExecution(EnemySMBase* initEnemy);
	/// <summary>
	/// ウォリアーの距離を計算する関数
	/// </summary>
	void WarriorRangeCalc();
private:
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
	/// レベルレンダー
	/// </summary>
	LevelRender m_levelRender;
	/// <summary>
	/// プレイヤーのインスタンスを格納する変数
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// パトロールルートのリスト
	/// </summary>
	std::vector<MetaAIPatrolRuteData*> m_patrolRuteList;
	/// <summary>
	/// 呼び出したエネミー
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;

	float m_warriorDistanceList[3];
};


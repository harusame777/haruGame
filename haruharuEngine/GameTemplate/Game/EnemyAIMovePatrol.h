#pragma once
#include "EnemyAIBase.h"

class EnemyBase;
class WarriorDataHolder;
class Player;

class EnemyAIMovePatrol : public EnemyAIBase
{
	/// <summary>
	/// スタート関数
	/// </summary>
	void EnemyAIStart() override;
	/// <summary>
	/// アップデート関数
	/// </summary>
	void EnemyAIUpdate() override;
private:
	enum SearchMode {

		en_Near,

		en_Far,
	};
	/// <summary>
	/// ウォリアーの距離を計算する関数
	/// </summary>
	void WarriorRangeCalc();
	void SearchRute(const SearchMode mode);
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
};


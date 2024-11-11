#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "PatrolRuteDataHolder.h"

class EnemyBase;
class Player;

class WarriorAIMetapPatrol : public EnemyAIMetaBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WarriorAIMetapPatrol(std::shared_ptr<WarriorDataHolder> enemyData,
		std::shared_ptr<PatrolRuteDataHolder> patrolData)
	{
		m_sharedWarriorDatas = enemyData;

		m_sharedPatrolRuteDatas = patrolData;

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
	/// 処理終了
	/// </summary>
	void ProcessEnd();
private:
	enum SearchMode {

		en_Near,

		en_Far,
	};
	/// <summary>
	/// ウォリアーの距離を計算する関数
	/// </summary>
	void WarriorRangeCalc();
	/// <summary>
	/// 巡回ルートを探す
	/// </summary>
	/// <param name="mode"></param>
	void SearchRute(const SearchMode mode);
	/// <summary>
	/// レベルレンダー
	/// </summary>
	LevelRender m_levelRender;
	/// <summary>
	/// プレイヤーのインスタンスを格納する変数
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// 呼び出したエネミー
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;
protected:
	/// <summary>
	/// 共通しているウォリアーのデータ
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
	/// <summary>
	/// 共通している巡回ルートのデータ
	/// </summary>
	std::shared_ptr<PatrolRuteDataHolder> m_sharedPatrolRuteDatas;

	float m_warriorDistanceList[3];
};


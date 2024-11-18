#pragma once
#include "EnemyAIMetaBase.h"
#include "PatrolRuteDataHolder.h"

class EnemyBase;

class WarriorAIMetaRetreat : public EnemyAIMetaBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WarriorAIMetaRetreat(std::shared_ptr<PatrolRuteDataHolder> patrolData)
	{
		m_sharedPatrolRuteDatas = patrolData;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WarriorAIMetaRetreat() {};
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
	const bool ProcessEnd(EnemySMBase* initEnemy);
private:
	/// <summary>
	/// 
	/// </summary>
	void SearchRute();
	/// <summary>
	/// ルートを取得したかどうか
	/// </summary>
	bool m_isOneTimeGetRute = false;
	/// <summary>
	/// 移動が終了したかどうか
	/// </summary>
	bool m_isMoveEnd = false;
	/// <summary>
	/// 呼び出したエネミー
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;
protected:
	/// <summary>
	/// 共通している巡回ルートのデータ
	/// </summary>
	std::shared_ptr<PatrolRuteDataHolder> m_sharedPatrolRuteDatas;
};


#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"

class EnemyBase;

class WarriorAIMetaStop : public EnemyAIMetaBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WarriorAIMetaStop(std::shared_ptr<WarriorDataHolder> enemyData)
	{
		m_sharedWarriorDatas = enemyData;
	}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WarriorAIMetaStop(){}
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
protected:
	/// <summary>
	/// 共通しているウォリアーのデータ
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
};


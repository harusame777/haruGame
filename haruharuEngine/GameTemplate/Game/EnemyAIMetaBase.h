#pragma once
#include "WarriorDataHolder.h"
#include "EnemyAIBase.h"

class EnemyAIConBase;
class EnemyBase;

class EnemyAIMetaBase : public EnemyAIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAIMetaBase(std::shared_ptr<WarriorDataHolder> data)
	{
		m_sharedWarriorDatas = data;
	}
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyAIMetaBase(){}
	/// <summary>
	/// メタAIの初期化
	/// </summary>
	virtual void MetaAIInit() = 0;
	/// <summary>
	/// メタAI実行
	/// </summary>
	virtual void MetaAIExecution(EnemySMBase* initEnemy) = 0;
protected:
	/// <summary>
	/// 共通しているウォリアーのデータ
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
};


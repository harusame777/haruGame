#pragma once
#include "EnemyAIBase.h"
#include "EnemySMBase.h"

class EnemyAIConBase;
class EnemyBase;

class EnemyAIMetaBase : public EnemyAIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAIMetaBase() {};
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
	/// <summary>
	///	処理終了
	/// </summary>
	virtual void ProcessEnd() = 0;
};


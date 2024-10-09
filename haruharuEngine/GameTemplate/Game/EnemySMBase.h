#pragma once
#include "EnemyAIBase.h"

class EnemyAIConBase;

class EnemySMBase : public virtual EnemyAIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemySMBase(){};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemySMBase() {};
protected:
	/// <summary>
	/// 共通ステート変更関数
	/// </summary>
	virtual void ChangeState() {};
	/// <summary>
	/// 条件リスト
	/// </summary>
	std::vector<EnemyAIConBase*> m_enemyConList;
};


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
	virtual const bool ProcessEnd(EnemySMBase* initEnemy) = 0;
	/// <summary>
	/// 一回起動したかどうかのフラグ
	/// </summary>
	bool m_isOneTimeUpdateFlag = false;
	/// <summary>
	/// 一回プログラムが起動したかどうかを設定
	/// </summary>
	/// <param name="is"></param>
	void SetOneTimeUpdateFlag(const bool is)
	{
		m_isOneTimeUpdateFlag = is;
	}
	/// <summary>
	/// 一回プログラムが起動したかどうかを取得
	/// </summary>
	/// <returns></returns>
	const bool GetOneTimeUpdateFlag() const
	{
		return m_isOneTimeUpdateFlag;
	}
};


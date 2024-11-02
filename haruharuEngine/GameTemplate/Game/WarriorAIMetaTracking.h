#pragma once
#include "EnemyAIMetaBase.h"

class EnemyBase;
class EnemySMBase;

class WarriorAIMetaTracking : public EnemyAIMetaBase 
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WarriorAIMetaTracking(std::shared_ptr<WarriorDataHolder> data) : EnemyAIMetaBase(data) 
	{
		m_sharedWarriorDatas = data;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WarriorAIMetaTracking() {};
	/// <summary>
	/// メタAIの初期化関数
	/// </summary>
	void MetaAIInit();
	/// <summary>
	/// メタAIの実行関数
	/// </summary>
	/// <param name="initEnemy"></param>
	void MetaAIExecution(EnemySMBase* initEnemy);
private:
	/// <summary>
	/// ウォリアーに呼びかけを行う
	/// </summary>
	void CallWarrior();
	/// <summary>
	/// エネミー全体の追跡ステートを変更する関数
	/// </summary>
	void ChangeTrackingState();
	/// <summary>
	/// 呼び出したエネミー
	/// </summary>
	EnemySM_Warrior* m_MainCallWarrior = nullptr;

};


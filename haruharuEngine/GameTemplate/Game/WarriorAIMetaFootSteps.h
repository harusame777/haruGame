#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"

class Player;
class GameSound;

class WarriorAIMetaFootSteps : public EnemyAIMetaBase
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WarriorAIMetaFootSteps(std::shared_ptr<WarriorDataHolder> enemyData)
	{
		m_sharedWarriorDatas = enemyData;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WarriorAIMetaFootSteps(){}
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
	/// 距離計算
	/// </summary>
	void LengthCalc();
	/// <summary>
	/// 割合計算
	/// </summary>
	/// <returns></returns>
	const float& RatioCalc();
	/// <summary>
	/// プレイヤーからエネミーまでの距離
	/// </summary>
	float m_playerToEnemyDiffSq = 0.0f;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// ゲームサウンドのインスタンス
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// 呼び出したエネミー
	/// </summary>
	EnemySMBase* m_MainCallWarrior = nullptr;
	/// <summary>
	/// 共通しているウォリアーのデータ
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
};


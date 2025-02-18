#pragma once
#include "EnemyAIMetaBase.h"
#include "WarriorDataHolder.h"
#include "EnemyBase.h"

class Player;
class GameSound;

class WarriorAIMetaFootSteps : public EnemyAIMetaBase
{
public:
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
	/// エネミーのステートを確認する
	/// </summary>
	void EnemyStateCheck();
	/// <summary>
	/// データに数値を入力
	/// </summary>
	void DatasPriorityInit();
	/// <summary>
	/// レイテスト、壁判定
	/// </summary>
	/// <returns></returns>
	const bool& RayTestWall(EnemyBase* initEnemy);
	/// <summary>
	/// カメラ内判定
	/// </summary>
	const bool& IsinCamera(EnemyBase* initEnemy);
	/// <summary>
	/// データのエネミーとプレイヤーの間に壁があるかどうかを確認する
	/// </summary>
	void DatasEnemyWallCheck();
	/// <summary>
	/// 優先度
	/// </summary>
	enum EnemyDistance_Kinds
	{
		//優先度一番
		en_priority_high,
		//優先度二番
		en_priority_middle,
		//優先度三番
		en_priority_low,
		//設定なし
		en_priority_non = 4,
	};
	/// <summary>
	/// エネミーデータ
	/// </summary>
	struct EnemyLength_Data
	{
		EnemyBase* m_enemyData = nullptr;

		float m_length = 0.0f;

		EnemyDistance_Kinds m_priority
			= EnemyDistance_Kinds::en_priority_non;

		int m_warriorStateNum = -1;
	};
	/// <summary>
	/// 距離計算
	/// </summary>
	void LengthCalc();
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
	/// コライダー
	/// </summary>
	SphereCollider m_sphereCollider;
	/// <summary>
	/// 共通しているウォリアーのデータ
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_sharedWarriorDatas;
	/// <summary>
	/// エネミーのデータ
	/// </summary>
	EnemyLength_Data m_enemyLengthDatas[3];
	/// <summary>
	/// エネミーの数
	/// </summary>
	int m_enemyNum = 0;
};


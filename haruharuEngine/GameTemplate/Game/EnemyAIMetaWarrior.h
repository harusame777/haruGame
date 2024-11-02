#pragma once
#include "WarriorDataHolder.h"

class EnemySM_Warrior;
class EnemyBase;
class WarriorDataHolder;
class Player;
class EnemyAIMetaBase;

class EnemyAIMetaWarrior : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAIMetaWarrior() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyAIMetaWarrior() {};
	/// <summary>
	///	メタAIのどのプログラムを起動するか
	/// </summary>
	enum MetaAIMode
	{
		/// <summary>
		///追跡ステート変更 
		/// </summary>
		mode_trackingStateChange,
		/// <summary>
		/// 巡回ルート設定
		/// </summary>
		mode_patrolRouteSet,
		/// <summary>
		/// 初期化用
		/// </summary>
		mode_init,
	};
	/// <summary>
	/// スタート関数
	/// </summary>
	bool Start();
	/// <summary>
	/// リストにエネミーを格納する
	/// </summary>
	/// <param name="enemyPtr"></param>
	void ListInitEnemy(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// メタAIを実行する関数
	/// </summary>
	void MetaAIExecution(EnemySM_Warrior* enemyPtr,const MetaAIMode setMode);
	/// <summary>
	/// 処理を終了する
	/// </summary>
	void ProcessEnd();
private:
	/// <summary>
	/// メタAIのモード
	/// </summary>
	MetaAIMode m_nowMetaAIMode;
	/// <summary>
	/// 呼びかけたエネミー
	/// </summary>
	EnemySM_Warrior* m_MainCallWarrior = nullptr;
	/// <summary>
	/// メタAIのリスト
	/// </summary>
	std::vector<EnemyAIMetaBase*> m_AIMetaList;
	/// <summary>
	/// ウォリアーの共通データホルダ～
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
	/// <summary>
	/// 現在処理中かどうか
	/// </summary>
	bool m_isCurrentlyProcessed = false;
};


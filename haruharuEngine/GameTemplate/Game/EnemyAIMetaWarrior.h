#pragma once
#include "WarriorDataHolder.h"
#include "PatrolRuteDataHolder.h"

class EnemySM_Warrior;
class EnemyBase;
class Player;
class EnemyAIMetaBase;

class DebugEnemyTrackingState;

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
	~EnemyAIMetaWarrior() 
	{
		for (auto& metaAIs : m_AIMetaList)
		{
			metaAIs->DeleteAIMetaProgram();

			delete metaAIs;
		}

		m_AIMetaList.clear();

		m_patrolRuteDataHolder->DelteListData();
	};
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
		/// 退却
		/// </summary>
		mode_retreat,
		/// <summary>
		/// 停止
		/// </summary>
		mode_stop,
		/// <summary>
		/// 足音
		/// </summary>
		mode_footStep,
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
	/// リストにメタAIのプログラムを格納する
	/// </summary>
	/// <param name="programData"></param>
	/// <param name="isOneTime"></param>
	void ListInitAIMeta(EnemyAIMetaBase* programData, const bool isOneTime);
	/// <summary>
	/// メタAIを実行する関数
	/// </summary>
	void MetaAIExecution(EnemySM_Warrior* enemyPtr,const MetaAIMode setMode);
	/// <summary>
	/// 処理を終了する
	/// </summary>
	void ProcessEnd(const MetaAIMode setMode, EnemySMBase* initEnemy);
	
	std::shared_ptr<WarriorDataHolder> GetEnemyDatas()
	{
		return m_warriorDataHolder;
	}
private:
	/// <summary>
	/// メタAIプログラムのデータ
	/// </summary>
	struct MetaAIData
	{
	private:
		/// <summary>
		/// 一回きりの起動かどうか
		/// </summary>
		bool m_isOneTimeOnlyUpdate = false;
		/// <summary>
		/// メタAIのプログラムデータ
		/// </summary>
		EnemyAIMetaBase* m_metaAIProgramData;
	public:
		/// <summary>
		/// 一回きりか
		/// </summary>
		/// <param name="is"></param>
		void SetOneTimeOnlyUpdate(const bool is)
		{
			m_isOneTimeOnlyUpdate = is;
		}
		/// <summary>
		/// 一回きりかどうか
		/// </summary>
		/// <returns></returns>
		const bool GetOneTimeOnlyUpdate() const
		{
			return m_isOneTimeOnlyUpdate;
		}
		/// <summary>
		/// メタAIプログラムを設定
		/// </summary>
		/// <param name="initData"></param>
		void SetAIMetaProgram(EnemyAIMetaBase* initData)
		{
			m_metaAIProgramData = initData;
		}
		void DeleteAIMetaProgram()
		{
			delete m_metaAIProgramData;
		}
		/// <summary>
		/// メタAIのプログラムを取得
		/// </summary>
		/// <returns></returns>
		EnemyAIMetaBase* GetAIMetaProgram()
		{
			return m_metaAIProgramData;
		}
	};
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
	std::vector<MetaAIData*> m_AIMetaList;
	/// <summary>
	/// ウォリアーの共通データホルダ～
	/// </summary>
	std::shared_ptr<WarriorDataHolder> m_warriorDataHolder;
	/// <summary>
	/// ステートデバック
	/// </summary>
	DebugEnemyTrackingState* m_debugWarriorTrackingState = nullptr;
	/// <summary>
	/// レベルレンダー
	/// </summary>
	LevelRender m_patrolRuteLevelRender;
	/// <summary>
	/// 巡回ルートの共通データホルダー
	/// </summary>
	std::shared_ptr<PatrolRuteDataHolder> m_patrolRuteDataHolder;
};


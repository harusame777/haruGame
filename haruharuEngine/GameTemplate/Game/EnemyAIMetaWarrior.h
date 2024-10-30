#pragma once

class EnemySM_Warrior;
class EnemyBase;

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
	void MetaAIExecution(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// ウォリアーに呼びかけを行う
	/// </summary>
	void CallWarrior();
	/// <summary>
	/// エネミー全体の追跡ステートを変更する関数
	/// </summary>
	void ChangeTrackingState();
private:
	struct MetaAIWarriorData
	{
		/// <summary>
		/// trueであれば呼びかけに応じたエネミー
		/// </summary>
		bool m_isCallCompliedWarrior = false;
		/// <summary>
		/// エネミーのポインタ
		/// </summary>
		EnemySM_Warrior* m_warriorPtr = nullptr;
	};
	/// <summary>
	/// 呼びかけたエネミー
	/// </summary>
	EnemySM_Warrior* m_MainCallWarrior = nullptr;
	/// <summary>
	/// エネミーウォリアーのリスト
	/// </summary>
	std::vector<MetaAIWarriorData*> m_enemyWarriorList;
};


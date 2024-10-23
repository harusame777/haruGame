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
	/// エネミー全体の追跡ステートを変更する関数
	/// </summary>
	void MetaAIExecution(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// ウォリアーに呼びかけを行う
	/// </summary>
	void CallWarrior(EnemySM_Warrior* enemyPtr);
	/// <summary>
	/// リスト内のエネミーが追跡状態か調べる変数
	/// </summary>
	/// <returns></returns>
	const bool SearchEnemyTracking() const;
private:
	/// <summary>
	/// エネミーウォリアーのリスト
	/// </summary>
	std::vector<EnemySM_Warrior*> m_enemyWarriorList;
	/// <summary>
	/// 呼びかけに応じたエネミーのリスト
	/// </summary>
	std::list<EnemySM_Warrior*> m_CallRespondWarriorList;
};


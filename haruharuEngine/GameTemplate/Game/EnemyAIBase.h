#pragma once

class EnemyBase;

class EnemyAIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAIBase(){};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyAIBase(){};
	/// <summary>
	/// スタート関数
	/// </summary>
	virtual void EnemyAIStart() {};
	/// <summary>
	/// アップデート関数
	/// </summary>
	virtual void EnemyAIUpdate() {};
	/// <summary>
	/// エネミーを紐づけ
	/// </summary>
	/// <param name="enemy"></param>
	void BinedEnemy(EnemyBase* enemypt)
	{
		m_enemy = enemypt;
	}
	/// <summary>
	/// 紐づいているエネミーを取得
	/// </summary>
	/// <returns></returns>
	EnemyBase& GetEnemyPtr()
	{
		return *m_enemy;
	}
protected:
	/// <summary>
	/// このプログラムに紐づいているエネミー
	/// </summary>
	EnemyBase* m_enemy = nullptr;
};


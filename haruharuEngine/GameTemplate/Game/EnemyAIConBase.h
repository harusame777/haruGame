#pragma once

class EnemyBase;

class EnemyAIConBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAIConBase() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyAIConBase() 
	{

	};
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void InitData()
	{

	};
	/// <summary>
	/// 条件実行
	/// </summary>
	/// <returns></returns>
	virtual bool Execution() 
	{
		return true;
	};
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


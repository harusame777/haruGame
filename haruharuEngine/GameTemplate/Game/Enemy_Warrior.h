#pragma once

class EnemyBase;

class Enemy_Warrior : public EnemyBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy_Warrior();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	~Enemy_Warrior();
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ドロー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
};


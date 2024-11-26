#pragma once
#include "EnemyAIConBase.h"

class Player;
class EnemyBase;

class EnemyAIConColPlayer : public EnemyAIConBase
{
public:
	/// <summary>
	/// スタート関数
	/// </summary>
	void InitData() override;
	/// <summary>
	/// 条件実行
	/// </summary>
	/// <returns></returns>
	bool Execution() override;
private:
	/// <summary>
	/// プレイヤーのインスタンスを格納する変数
	/// </summary>
	Player* m_player = nullptr;
};


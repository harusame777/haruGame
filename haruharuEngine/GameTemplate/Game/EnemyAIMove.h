#pragma once
#include "EnemyAIBase.h"

class EnemyBase;
class WarriorDataHolder;
class Player;
class EnemyAIConBase;

class EnemyAIMove : public EnemyAIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAIMove(){}
	/// <summary>
	/// スタート関数
	/// </summary>
	void EnemyAIStart() override;
	/// <summary>
	/// アップデート関数
	/// </summary>
	void EnemyAIUpdate() override;
private:
	/// <summary>
	/// 回転値の計算
	/// </summary>
	void RotationCalc(const Vector3& moveSpeed);
	/// <summary>
	/// プレイヤー
	/// </summary>
	Player* m_player = nullptr;
};


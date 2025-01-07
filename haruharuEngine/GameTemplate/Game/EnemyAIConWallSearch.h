#pragma once
#include "EnemyAIConBase.h"

class Player;
class EnemyBase;

class EnemyAIConWallSearch : public EnemyAIConBase
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
	/// レイでエネミーとプレイヤーの間に壁が無いかを調べる関数
	/// </summary>
	bool RayTestWall();
	/// <summary>
	/// プレイヤーインスタンス
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// コライダー
	/// </summary>
	SphereCollider m_sphereCollider;
};


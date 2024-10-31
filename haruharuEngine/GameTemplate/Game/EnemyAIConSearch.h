#pragma once
#include "EnemyAIConBase.h"

class Player;
class EnemyBase;

class EnemyAIConSearch : public EnemyAIConBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAIConSearch(const float setViewingAngle,const float setSearchRad)
	{
		m_viewingAngle = setViewingAngle;
		m_enemySearchRad = setSearchRad;
	}
	/// <summary>
	/// スタート関数
	/// </summary>
	void Start() override;
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
	/// 視野角
	/// </summary>
	/// <returns></returns>
	bool AngleCheck();
	/// <summary>
	/// 視野角
	/// </summary>
	float m_viewingAngle = 0.0f;
	/// <summary>
	/// 索敵範囲
	/// </summary>
	float m_enemySearchRad = 500.0f;
	/// <summary>
	/// プレイヤーインスタンス
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// コライダー
	/// </summary>
	SphereCollider m_sphereCollider;
};


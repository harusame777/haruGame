#pragma once
#include "EnemyAIBase.h"


class EnemyAIMovePatrol : public EnemyAIBase
{
public:
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
	/// 巡回ルートのパスを取得するためのレベルレンダー
	/// </summary>
	LevelRender m_patrolVecPath;
	/// <summary>
	/// 巡回ルートのリスト
	/// </summary>
	std::vector<Vector3*> m_patrolPathList;
};


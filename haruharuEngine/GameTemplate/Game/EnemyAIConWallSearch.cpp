#include "stdafx.h"
#include "EnemyAIConWallSearch.h"
#include "EnemyBase.h"
#include "Player.h"

//スタート関数
void EnemyAIConWallSearch::InitData()
{
	//プレイヤーのインスタンスを取得
	m_player = FindGO<Player>("player");
	//コライダーを初期化
	m_sphereCollider.Create(1.0f);
}

//壁の判定を取る構造体
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	/// <summary>
	/// 対象属性にレイが当たったかどうか
	/// </summary>
	bool isHit = false;
	/// <summary>
	///	判定
	/// </summary>
	/// <param name="covexResult"></param>
	/// <param name="normalInWorldSpace"></param>
	/// <returns></returns>
	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& covexResult,
		bool normalInWorldSpace)
	{
		//壁とぶつかっていなかったら
		if (covexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall)
		{
			//衝突したのは壁ではない
			return 0.0f;
		}

		//壁とぶつかってたらフラグをtrueにする
		isHit = true;
		return 0.0f;
	}
};

bool EnemyAIConWallSearch::RayTestWall()
{
	//壁越しに見つけないようにレイを使用して壁の判定を取る
	//コライダーの始点と終点を初期化
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();

	//始点位置決定
	Vector3 startPos = GetEnemyPtr().GetPosition();
	startPos.y += 70.0f;
	start.setOrigin(btVector3(startPos.x, startPos.y, startPos.z));

	//終点位置決定
	Vector3 endPos = m_player->GetPosition();
	endPos.y += 75.0f;
	end.setOrigin(btVector3(endPos.x, endPos.y, endPos.z));

	SweepResultWall callback;

	//衝突検出
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(),
		start, end, callback);
	if (callback.isHit) {
		//当たった
		return true;
	}

	//当たってない
	return false;
}

//条件実行
bool EnemyAIConWallSearch::Execution()
{
	if (RayTestWall())
	{
		return true;
	}

	return false;
}
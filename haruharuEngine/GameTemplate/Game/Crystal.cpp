#include "stdafx.h"
#include "Crystal.h"
#include "Player.h"

//コンストラクタ
Crystal::Crystal()
{

}

//デストラクタ
Crystal::~Crystal()
{

}

//スタート関数
bool Crystal::Start()
{

	//クリスタル01をモデルに設定
	m_mainModel.Init("Assets/modelData/objects/crystal/crystal01_Model.tkm", nullptr, 0, enModelUpAxisZ, true);

	//シャドウマップに描画するようにする
	m_mainModel.SetShadowChasterFlag(true);

	//座標を設定
	m_mainModel.SetPosition(m_position);
	//回転を設定
	m_mainModel.SetRotation(m_rotation);
	//拡大率を設定
	m_mainModel.SetScale(m_scale);
	//初期設定を確定
	m_mainModel.Update();

	//プレイヤーのインスタンスを取得する
	m_player = FindGO<Player>("player");

	//コライダーを初期化する
	m_sphereCollider.Create(1.0f);

	return true;
}

//アップデート関数
void Crystal::Update()
{
	//クリスタル取得処理
	GetCrystal();
	//描画更新
	m_mainModel.Update();
}

//レンダー関数
void Crystal::Render(RenderContext& rc)
{
	//取得されていなかったら
	if (m_isGetObject)
	{
		//描画しない
		m_mainModel.Draw(rc);
	}
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

bool Crystal::RayTestWall()
{
	//壁越しに見つけないようにレイを使用して壁の判定を取る
	//コライダーの始点と終点を初期化
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();

	//始点位置決定
	Vector3 startPos = GetPosition();
	startPos.y += 70.0f;
	start.setOrigin(btVector3(startPos.x, startPos.y, startPos.z));

	//終点位置決定
	Vector3 endPos = m_player->GetPosition();
	endPos.y += 70.0f;
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

void Crystal::GetCrystal()
{

}
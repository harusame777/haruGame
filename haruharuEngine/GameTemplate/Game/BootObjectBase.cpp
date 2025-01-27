#include "stdafx.h"
#include "BootObjectBase.h"
#include "Player.h"

//定数等
namespace {
	/// <summary>
	/// 取得距離の計算に使うやつ
	/// </summary>
	static const float GET_RANGE_CALC = 90.0f;
}

//初期化関数
void BootObjectBase::InitBootObject(const char* filePath)
{
	//コライダーを初期化する
	m_sphereCollider.Create(0.1f);

	m_bootPlayer = FindGO<Player>("player");

	m_getBootPosition.Init(filePath, [&](LevelObjectData_Render& objData)
		{
			if (objData.EqualObjectName(L"bootPosition") == true)
			{

				m_levelPosition = objData.m_position;

				return true;
			}
			return true;
		});

	m_bootPosition = m_levelPosition + m_position;
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

//オブジェクトが起動できる条件にあるかどうか調べる関数
const bool BootObjectBase::IsObjectBootConditions()
{
	if (IsObjectBootingRange() == true &&
		IsObjectBootingCameraVector() == true &&
		IsRayTestWall() == false)
	{
		return true;
	}

	return false;
}

//オブジェクトが起動可能カメラベクター方向内にあるかどうか調べる関数
const bool BootObjectBase::IsObjectBootingCameraVector()
{
	//カメラの正面ベクトルを取得
	Vector3 camForward = g_camera3D->GetForward();

	//プレイヤーの座標を取得
	Vector3 playerPos = g_camera3D->GetPosition();

	//プレイヤーの座標から自身の座標を引いて
	//自身からプレイヤーへ伸びるベクトルを計算する
	Vector3 diff = playerPos - GetBootPosition();

	//正規化して単位ベクトルにする
	diff.Normalize();

	//内積を計算し、相似性を測る
	float similarity = Dot(camForward, diff);

	//もし-0.95よりも相似性が小さかったら
	if (similarity <= -0.95)
	{
		//trueを返す
		return true;
	}

	return false;
}

//オブジェクトが起動可能な範囲内座標にあるかどうかを調べる関数
const bool BootObjectBase::IsObjectBootingRange()
{
	//プレイヤーの座標を取得
	Vector3 playerPos = m_bootPlayer->GetPosition();

	//プレイヤーの座標から自身の座標を引いて
	//自身からプレイヤーへ伸びるベクトルを計算する
	Vector3 diff = playerPos - GetBootPosition();

	//自身からプレイヤーへ伸びるベクトルの２乗を計算する
	float range = diff.LengthSq();

	//もし取得範囲内だったら
	if (range <= GET_RANGE_CALC * GET_RANGE_CALC)
	{
		//trueを返す
		return true;
	}

	return false;
}

const bool BootObjectBase::IsRayTestWall()
{
	//壁越しに見つけないようにレイを使用して壁の判定を取る
//コライダーの始点と終点を初期化
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();

	//始点位置決定
	Vector3 startPos = m_bootPlayer->GetPosition();
	startPos.y += 70.0;
	start.setOrigin(btVector3(startPos.x, startPos.y, startPos.z));

	//終点位置決定
	Vector3 endPos = GetBootPosition();
	endPos.y += 5.0f;
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
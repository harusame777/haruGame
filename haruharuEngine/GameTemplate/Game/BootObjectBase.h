#pragma once

class Player;
class PlayerInteractableUi;

class BootObjectBase : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BootObjectBase(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BootObjectBase(){}
	/// <summary>
	/// 位置設定
	/// </summary>
	/// <param name="pos = 座標"></param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 位置取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// 回転設定
	/// </summary>
	/// <param name="rot = 回転"></param>
	void SetRotation(const Quaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転取得
	/// </summary>
	/// <returns></returns>
	const Quaternion& GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// 拡大率設定
	/// </summary>
	/// <param name="sca = 拡大率"></param>
	void SetScale(const Vector3& sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// 拡大率取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetScale()
	{
		return m_scale;
	}
	/// <summary>
	/// 正面ベクトル設定
	/// </summary>
	/// <param name="forward = 正面ベクトル"></param>
	void SetForward(const Vector3& forward)
	{
		m_forward = forward;
	}
	/// <summary>
	/// 正面ベクトル取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetFoward()
	{
		return m_forward;
	}
	/// <summary>
	/// 起動座標を初期化
	/// レベルで取得、位置の名前はbootPosition固定
	/// </summary>
	/// <param name="filePath"></param>
	void InitBootObject(const char* filePath);
	/// <summary>
	/// 起動座標取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetBootPosition() const
	{
		return m_bootPosition;
	}
	/// <summary>
	/// オブジェクトが起動できる条件にあるかどうか調べる関数
	/// </summary>
	/// <returns></returns>
	const bool IsObjectBootConditions();
	/// <summary>
	/// 位置リセット
	/// </summary>
	/// <param name="resetPos"></param>
	void UpdateBootData();
private:
	/// <summary>
	/// オブジェクトが起動可能カメラベクター方向内にあるかどうか調べる関数
	/// </summary>
	/// <returns></returns>
	const bool IsObjectBootingCameraVector();
	/// <summary>
	/// オブジェクトが起動可能な範囲内座標にあるかどうかを調べる関数
	/// </summary>
	/// <returns></returns>
	const bool IsObjectBootingRange();
	/// <summary>
	/// レイを使用して壁にレイが当たったか調べる関数
	/// </summary>
	/// <returns></returns>
	const bool IsRayTestWall();
protected:
	/// <summary>
	/// 現在座標
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// 現在回転
	/// </summary>
	Quaternion m_rotation;
	/// <summary>
	/// 現在拡大率
	/// </summary>
	Vector3 m_scale = Vector3::One;
	/// <summary>
	/// 現在正面ベクトル
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// 当たり判定
	/// </summary>
	PhysicsStaticObject m_physicsStaticObject;
	/// <summary>
	/// メインモデル
	/// </summary>
	ModelRender m_mainModel;
private:
	/// <summary>
	/// レベル上の座標
	/// </summary>
	Vector3 m_levelPosition = Vector3::Zero;
	/// <summary>
	/// レベル
	/// </summary>
	LevelRender m_getBootPosition;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	Player* m_bootPlayer = nullptr;
	/// <summary>
	/// 起動座標
	/// </summary>
	Vector3 m_bootPosition = Vector3::Zero;
	/// <summary>
	/// インタラクト可能スプライトUiのインスタンス
	/// </summary>
	PlayerInteractableUi* m_playerInteractableUi = nullptr;
	/// <summary>
	/// コライダー
	/// </summary>
	SphereCollider m_sphereCollider;
};


#pragma once

class BackGroundWalls : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BackGroundWalls();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BackGroundWalls();
	/// <summary>
	/// 壁の種類
	/// </summary>
	enum WallType
	{
		/// <summary>
		/// 壁1_4
		/// </summary>
		en_wallType1_4,
		/// <summary>
		/// 壁2_4
		/// </summary>
		en_wallType2_4,
		/// <summary>
		/// 壁4_4
		/// </summary>
		en_wallType4_4,
		/// <summary>
		/// 壁4_6
		/// </summary>
		en_wallType4_6,
		/// <summary>
		/// 壁ドア付き4_4
		/// </summary>
		en_wallTypeDoorWay4_4,
		/// <summary>
		/// 一体化
		/// </summary>
		en_wallOnes,
		/// <summary>
		/// 壁の数
		/// </summary>
		en_wallNum,
		/// <summary>
		/// 未設定
		/// </summary>
		en_wallTypeNone,
	};
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
	/// 壁の種類を設定
	/// </summary>
	/// <param name="walltype"></param>
	void SetWallType(const WallType& walltype);
	/// <summary>
	/// 壁の種類が設定されているかどうか
	/// </summary>
	const bool& IsSetWallType()
	{
		bool isSetWallType;
		isSetWallType = (m_wallType != WallType::en_wallTypeNone);
		return isSetWallType;
	}
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
	/// 壁の種類
	/// </summary>
	WallType m_wallType = WallType::en_wallTypeNone;
	/// <summary>
	/// メインモデル
	/// </summary>
	ModelRender m_mainModel;
};


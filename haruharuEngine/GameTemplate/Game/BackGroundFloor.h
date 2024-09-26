#pragma once

class BackGroundFloor : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BackGroundFloor();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BackGroundFloor();
	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos = 座標"></param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot = 回転"></param>
	void SetRotation(const Quaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns></returns>
	const Quaternion& GetRotation()
	{
		return m_rotation;
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="sca = 拡大率"></param>
	void SetScale(const Vector3& sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <returns></returns>
	const Vector3& GetScale()
	{
		return m_scale;
	}
	/// <summary>
	/// 正面ベクトルを設定
	/// </summary>
	/// <param name="forward = 正面ベクトル"></param>
	void SetForward(const Vector3& forward)
	{
		m_forward = forward;
	}
	/// <summary>
	/// 正面ベクトルを取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetForward()
	{
		return m_forward;
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
	/// 座標
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// 回転
	/// </summary>
	Quaternion m_rotation;
	/// <summary>
	/// 拡大率
	/// </summary>
	Vector3 m_scale = Vector3::Zero;
	/// <summary>
	/// 正面ベクトル
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// 当たり判定
	/// </summary>
	PhysicsStaticObject m_physicsStaticObject;
	/// <summary>
	/// モデルレンダー
	/// </summary>
	ModelRender m_modelRender;
};


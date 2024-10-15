#pragma once
class Player : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ　
	/// </summary>
	~Player();
public:
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
	/// キャラコンを取得
	/// </summary>
	/// <returns></returns>
	CharacterController& GetCharacterController()
	{
		return m_CController;
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
	/// 移動関数
	/// </summary>
	void Move();
	/// <summary>
	/// プレイヤーが走り状態か歩き状態化を調べる関数
	/// </summary>
	void IsWalkOrRun();
	/// <summary>
	/// 現在座標
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// 現在回転値
	/// </summary>
	Quaternion m_rotation;
	/// <summary>
	/// 現在拡大値
	/// </summary>
	Vector3 m_scale = Vector3::One;
	/// <summary>
	/// 現在正面ベクトル
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// 基本移動速度
	/// </summary>
	float m_moveSpeed;
	/// <summary>
	/// 移動ベクトル
	/// </summary>
	Vector3 m_moveVector;
	/// <summary>
	/// キャラコン
	/// </summary>
	CharacterController m_CController;
};


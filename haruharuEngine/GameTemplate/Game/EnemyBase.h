#pragma once
#include "EnemyAIBase.h"

class EnemyBase : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyBase()
	{

	}
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyBase()
	{

	}
protected:
	/// <summary>
	/// AIListの初期化
	/// </summary>
	virtual void InitAIList() = 0;
	/// <summary>
	/// AIList内のプログラムのアップデート
	/// </summary>
	virtual void AIListUpdate() = 0;
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
	/// キャラコン
	/// </summary>
	CharacterController m_CController;
	/// <summary>
	/// 移動先の位置
	/// </summary>
	Vector3 m_moveTargetPosition = Vector3::Zero;
	/// <summary>
	/// エネミーウォリアーのステートマシン
	/// </summary>
	EnemyAIBase* m_enemyWarriorSM = nullptr;
	/// <summary>
	/// 現在のステートの数値
	/// </summary>
	int m_stateNumber = -1;
	/// <summary>
	/// デバック用フォントレンダー
	/// </summary>
	FontRender m_debugStateDisplayRender;
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
	/// 移動先位置を設定
	/// </summary>
	/// <param name="movePosition = 移動先座標"></param>
	void SetMoveTargetPosition(const Vector3& movePosition)
	{
		m_moveTargetPosition = movePosition;
	}
	/// <summary>
	/// 移動先位置を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetMoveTargetPosition()
	{
		return m_moveTargetPosition;
	}
	/// <summary>
	/// ステートナンバーを設定
	/// </summary>
	/// <param name="stateNum = ステートナンバー"></param>
	void SetStateNumber(const int stateNum)
	{
		m_stateNumber = stateNum;
	}
	/// <summary>
	/// ステートナンバーを取得
	/// </summary>
	/// <returns></returns>
	const int GetStateNumber()
	{
		return m_stateNumber;
	}
	/// <summary>
	/// デバックディスプレイ文字設定
	/// </summary>
	void DebugStateDisplay()
	{
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"NowState[%01d]", int(m_stateNumber));

		m_debugStateDisplayRender.SetText(wcsbuf);
	}
};


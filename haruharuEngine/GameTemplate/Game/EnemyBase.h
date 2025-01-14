#pragma once
#include "EnemyAIBase.h"

class EnemyBase : public IGameObject
{
public:
	enum EnAnimationClip
	{
		en_idle,
		en_tracking,
		en_patrol,
		en_attack,
		en_animationNum,
	};
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
	/// モデル
	/// </summary>
	ModelRender m_modelRender;
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
	int m_stateNumber = 0;
	/// <summary>
	/// 現在のステートの数値
	/// </summary>
	int m_trackingStateNumber = 0;
	/// <summary>
	/// デバック用フォントレンダー
	/// </summary>
	FontRender m_debugStateDisplayRender;

	/// <summary>
	/// アニメーションクリップ
	/// </summary>
	AnimationClip m_animationClip[en_animationNum];

	EnAnimationClip m_animationClipState = EnAnimationClip::en_idle;
	/// <summary>
	///	攻撃フラグ
	/// </summary>
	bool m_attackFlag = false;

	char m_colName[20] = "";
	/// <summary>
	/// アニメーションが終わった
	/// </summary>
	bool m_isAnimationEnd = false;

	bool m_isAttackImpact = false;

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
	const Vector3& GetPosition() const 
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
	/// 追跡ステートナンバーを設定
	/// </summary>
	/// <param name="stateNum = ステートナンバー"></param>
	void SetTrackingStateNumber(const int setNum)
	{
		m_trackingStateNumber = setNum;
	}
	/// <summary>
	/// 追跡ステートナンバーを取得
	/// </summary>
	/// <returns></returns>
	const int GetTrackingStateNumber()
	{
		return m_trackingStateNumber;
	}
	/// <summary>
	/// ステートナンバーを設定
	/// </summary>
	/// <param name="stateNum = ステートナンバー"></param>
	void SetStateNumber(const int setNum)
	{
		m_stateNumber = setNum;
	}
	/// <summary>
	/// ステートナンバーを取得
	/// </summary>
	/// <returns></returns>
	const int GetStateNumber()
	{
		return m_stateNumber;
	}

	CharacterController* GetCController()
	{
		return &m_CController;
	}

	/// <summary>
	/// アニメーションのステートを設定
	/// </summary>
	/// <param name="setState"></param>
	void SetPlayAnimationState(const EnAnimationClip& setState)
	{
		m_animationClipState = setState;
	}

	void SetAttackFlag(const bool& flag)
	{
		m_attackFlag = flag;
	}

	const bool& GetAttackFlag() const
	{
		return m_attackFlag;
	}

	void SetCollisionName(const char* name)
	{
		std::strcat(m_colName, name);
	}

	const char* GetCollisionName() const
	{
		return m_colName;
	}

	void SetAnimationEnd(const bool& setBool)
	{
		m_isAnimationEnd = setBool;
	}

	const bool& GetAnimationEnd() const
	{
		return m_isAnimationEnd;
	}

	const bool& IsAnimationClipEnd() const 
	{
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			return true;
		}

		return false;
	}

	void SetAttackImpact(const bool& is)
	{
		m_isAttackImpact = is;
	}

	const bool& GetAttackImpact() const
	{
		return m_isAttackImpact;
	}
};


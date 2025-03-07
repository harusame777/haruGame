#pragma once
#include "BootObjectBase.h"

class ManagerLocker;

class Locker : public BootObjectBase
{
public:
	enum LockerState 
	{
		en_standby,

		en_lockerInCameraEasing,

		en_playerInUse,

		en_lockerOutCameraEasing,

	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Locker() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Locker() {};
	/// <summary>
	/// ロッカーが使用中かどうか
	/// </summary>
	/// <returns></returns>
	const bool IsLockerInUse() const
	{
		return m_isLockerInUse;
	}
	/// <summary>
	/// マネージャーのインスタンスを設定
	/// </summary>
	/// <param name="address"></param>
	void SetManegerInstance(ManagerLocker& address)
	{
		m_lockerManager = &address;
	}
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アニメーションイベント関数
	/// </summary>
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ロッカー実行
	/// </summary>
	void LockerStateUpdate();
	/// <summary>
	/// ロッカーのステート
	/// </summary>
	LockerState m_lockerState = LockerState::en_standby;
	/// <summary>
	/// ロッカー入る時のカメライージング処理
	/// </summary>
	const bool LockerInCameraEasing(const bool swap);
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// アニメーションクリップ
	/// </summary>
	enum EnAnimationClip
	{
		en_idle,

		en_OpenLocker,

		en_animationNum
	};
	/// <summary>
	/// アニメーションクリップ
	/// </summary>
	AnimationClip m_animationClip[en_animationNum];
	/// <summary>
	/// このロッカーが使用中かどうか
	/// </summary>
	bool m_isLockerInUse = false;
	/// <summary>
	/// カメライージング用変数
	/// </summary>
	Vector3 m_cameraEasingStart = Vector3::Zero;
	Vector3 m_cameraEasingEnd = Vector3::Zero;
	float m_cameraEasingRatio = 0.0f;
	/// <summary>
	/// アニメーションステート
	/// </summary>
	EnAnimationClip m_animationClipState = EnAnimationClip::en_idle;
	/// <summary>
	/// ロッカーのマネージャーのインスタンス
	/// </summary>
	ManagerLocker* m_lockerManager = nullptr;
	/// <summary>
	/// カメラ座標取得用
	/// </summary>
	LevelRender m_cameraPosInLevel;
	/// <summary>
	/// カメラのターゲットポジション
	/// </summary>
	Vector3 m_cameraTargetPos = Vector3::Zero;
};


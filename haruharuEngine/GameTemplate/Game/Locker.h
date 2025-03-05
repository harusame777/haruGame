#pragma once
#include "BootObjectBase.h"

class ManagerLocker;

class Locker : public BootObjectBase
{
public:
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
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ロッカー実行
	/// </summary>
	void LockerExecution();
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
	/// アニメーションステート
	/// </summary>
	EnAnimationClip m_animationClipState = EnAnimationClip::en_idle;
	/// <summary>
	/// ロッカーのマネージャーのインスタンス
	/// </summary>
	ManagerLocker* m_lockerManager = nullptr;
};


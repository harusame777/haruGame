#pragma once
#include "Locker.h"
#include "LockerDataHolder.h"

class Player;
class GameCamera;

class ManagerLocker : public IGameObject
{
public:
	/// <summary>
	/// ロッカー管理ステート
	/// </summary>
	enum LockerManageState
	{
		//設置前
		en_standby,
		//配置中
		en_underplacement,
		//壊れてる
		en_broken,
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ManagerLocker() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ManagerLocker() {};
	/// <summary>
	/// データホルダーを取得
	/// </summary>
    /// <returns></returns>
	std::shared_ptr<LockerDataHolder> GetLockerDataHolder()
	{
		return m_lockerDataHolder;
	}
	/// <summary>
	/// 全体の中でロッカーが一つでも使用中かどうか
	/// </summary>
	/// <returns></returns>
	const bool IsWholeLockersInUse();
	/// <summary>
	/// プレイヤーがロッカーに入った時の処理
	/// </summary>
	void SetPlayerInLocker();
	/// <summary>
	/// プレイヤーがロッカーから出た時の処理
	/// </summary>
	void SetPlayerOutLocker();
	/// <summary>
	/// カメラのターゲットを設定
	/// </summary>
	void SetCameraTarget(const Vector3& pos);
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 配置処理
	/// </summary>
	void InitArrangement();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ロッカーの管理用データ
	/// </summary>
	struct LockerManageData
	{
	private:
		/// <summary>
		/// ロッカーのアドレス
		/// </summary>
		Locker* m_lockerAddress = nullptr;
		/// <summary>
		/// ロッカー管理ステート
		/// </summary>
		LockerManageState m_lockerManageState = LockerManageState::en_standby;
	public:
		/// <summary>
		/// ロッカーのアドレスを設定
		/// </summary>
		/// <param name="address"></param>
		void SetLockerAddress(Locker* address)
		{
			m_lockerAddress = address;
		}
		/// <summary>
		/// ロッカーのアドレスを返す
		/// </summary>
		/// <returns></returns>
		Locker* GetLockerAddress() const
		{
			return m_lockerAddress;
		}
		/// <summary>
		/// ロッカーの管理ステートを設定
		/// </summary>
		/// <param name="state"></param>
		void SetLockerRelocationState(const LockerManageState state)
		{
			m_lockerManageState = state;
		}
		/// <summary>
		/// ロッカーの管理ステートを取得
		/// </summary>
		/// <returns></returns>
		const LockerManageState GetLockerRelocationState() const
		{
			return m_lockerManageState;
		}
	};
	/// <summary>
	/// ロッカーの管理用データ配列
	/// </summary>
	LockerManageData m_lockerManageDatas[MAX_LOCKER_NUM];
	/// <summary>
	/// ロッカー配置位置データ
	/// </summary>
	struct LockerArrangementData
	{
	private:
		/// <summary>
		/// 配置位置
		/// </summary>
		Vector3 m_arrangementPos = Vector3::Zero;
		/// <summary>
		/// 配置回転
		/// </summary>
		Quaternion m_arrangementRot;
		/// <summary>
		/// この位置に配置されているクリスタルのアドレス
		/// </summary>
		Locker* m_lockerAddress = nullptr;
		/// <summary>
		/// ロッカーが配置中かどうか
		/// </summary>
		bool m_isLockerUnderInstallation = false;
	public:
		/// <summary>
		/// 位置設定
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3 pos)
		{
			m_arrangementPos = pos;
		}
		void LockerPosAndRotUpdate()
		{
			m_lockerAddress->SetPosition(m_arrangementPos);

			m_lockerAddress->SetRotation(m_arrangementRot);
		}
		/// <summary>
		/// 位置取得
		/// </summary>
		/// <returns></returns>
		const Vector3 GetPosition() const
		{
			return m_arrangementPos;
		}
		/// <summary>
		/// 回転設定
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion rot)
		{
			m_arrangementRot = rot;
		}
		/// <summary>
		/// 回転取得
		/// </summary>
		/// <returns></returns>
		const Quaternion GetRotation() const
		{
			return m_arrangementRot;
		}
		/// <summary>
		/// アドレス初期化
		/// </summary>
		/// <param name="crystal"></param>
		void InitAddress(Locker* locker)
		{
			m_lockerAddress = locker;
		}
		/// <summary>
		/// アドレス取得
		/// </summary>
		/// <returns></returns>
		Locker* GetAddress() const
		{
			return m_lockerAddress;
		}
		/// <summary>
		/// 配置中かどうかを設定
		/// </summary>
		/// <param name="is"></param>
		void SetIsLockerUnderInstallation(const bool is)
		{
			m_isLockerUnderInstallation = is;
		}
		/// <summary>
		/// 配置中かどうかを取得
		/// </summary>
		/// <returns></returns>
		bool GetIsCrystalUnderInstallation() const
		{
			return m_isLockerUnderInstallation;
		}
	};
	/// <summary>
	/// ロッカーのデータホルダー
	/// </summary>
	std::shared_ptr<LockerDataHolder> m_lockerDataHolder;
	/// <summary>
	/// ロッカーの位置データを格納しておく
	/// </summary>
	std::vector<LockerArrangementData*> m_lockerArrangementDatas;
	/// <summary>
	/// ロッカーの配置位置を取得するためのレベルレンダー
	/// </summary>
	LevelRender m_lockerArrangementLevelRender;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// プレイヤーカメラのインスタンス
	/// </summary>
	GameCamera* m_gameCamera = nullptr;
};


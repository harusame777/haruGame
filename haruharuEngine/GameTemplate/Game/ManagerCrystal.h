#pragma once
#include "Crystal.h"

//定数等
namespace {
	/// <summary>
	/// クリスタルの最大数
	/// </summary>
	static const int MAX_CRYSTAL_NUM = 3;
	/// <summary>
	/// 再配置までの時間
	/// </summary>
	static const float RELOCATION_TIME = 5.0f;
}

class ManagerCrystal : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ManagerCrystal() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ManagerCrystal() {};
	/// <summary>
	/// 配置データを再設定可能な状態にする
	/// </summary>
	/// <param name="crystal"></param>
	void ArrangementDataRefresh(Crystal* crystal);
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
	/// 配列の中に採取されているクリスタルがあるかどうかを調べる
	/// </summary>
	/// <returns></returns>
	const bool IsCrystalsAppearance()
	{

		//クリスタルの最大数繰り返す
		for (int CryNo = 0; CryNo < MAX_CRYSTAL_NUM; CryNo++)
		{
			//もし取得されているクリスタルがあったら
			if (m_crystalManageDatas[CryNo]->GetCrystalRelocationState() 
				== CrystalRelocationState::en_notArrangement_State)
			{
				//trueを返す
				return true;
			}
		}

		return false;
	}
	/// <summary>
	/// 再配置設定
	/// </summary>
	void InitRelocation();
	/// <summary>
	/// クリスタルの設置管理ステート
	/// </summary>
	enum CrystalRelocationState
	{
		/// <summary>
		/// 未設置状態
		/// </summary>
		en_notArrangement_State,
		/// <summary>
		/// 配置位置決定
		/// </summary>
		en_relocationPosDecision_State,
		/// <summary>
		/// 設置タイマー処理中
		/// </summary>
		en_relocationTimerProcessing_State,
		/// <summary>
		/// 設置状態
		/// </summary>
		en_arrangement_State
	};
	/// <summary>
	/// クリスタル管理用データ
	/// </summary>
	struct CrystalManageData
	{
	private:
		/// <summary>
		/// クリスタルのアドレス
		/// </summary>
		Crystal* m_crystalAddress = nullptr;
		/// <summary>
		/// クリスタル再配置までの時間
		/// </summary>
		float m_RelocationTimer = 0.0f;
		/// <summary>
		/// クリスタルの設置管理ステート
		/// </summary>
		CrystalRelocationState m_manageCrystalState = CrystalRelocationState::en_arrangement_State;
	public:
		/// <summary>
		/// クリスタルのアドレスを設定
		/// </summary>
		/// <param name="address"></param>
		void SetCrystalAddress(Crystal* address)
		{
			m_crystalAddress = address;
		}
		/// <summary>
		/// クリスタルのアドレスを返す
		/// </summary>
		/// <returns></returns>
		Crystal* GetCrystalAddress() const
		{
			return m_crystalAddress;
		}
		/// <summary>
		/// タイマーを初期化
		/// </summary>
		void InitCrystalRelocationTimer()
		{
			m_RelocationTimer = RELOCATION_TIME;
		}
		/// <summary>
		/// 減算
		/// </summary>
		/// <param name="subTime"></param>
		void SubtractionCrystalRelocationTimer(const float subTime)
		{
			m_RelocationTimer -= subTime;
		}
		/// <summary>
		/// 現在の再配置までの時間を表示
		/// </summary>
		/// <returns></returns>
		const float GetNowCrystalRelocationTimer() const 
		{
			return m_RelocationTimer;
		}
		/// <summary>
		/// クリスタルの管理ステートを設定
		/// </summary>
		/// <param name="state"></param>
		void SetCrystalRelocationState(const CrystalRelocationState state)
		{
			m_manageCrystalState = state;
		}
		/// <summary>
		/// クリスタルの管理ステートを取得
		/// </summary>
		/// <returns></returns>
		const CrystalRelocationState GetCrystalRelocationState() const
		{
			return m_manageCrystalState;
		}
	};
	/// <summary>
	/// クリスタルのデータホルダー
	/// </summary>
	CrystalManageData* m_crystalManageDatas[MAX_CRYSTAL_NUM];
	/// <summary>
	/// 配置位置決定
	/// </summary>
	void RelocationPosDecision(CrystalManageData* crystalData);
	/// <summary>
	///　再配置タイマー処理
	/// </summary>
	void RelocationTimerProcess();
	/// <summary>
	/// 配置データ
	/// </summary>
	struct CrystalArrangementData
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
		Crystal* m_crystalAddress = nullptr;
		/// <summary>
		/// クリスタルが配置中かどうか
		/// </summary>
		bool m_isCrystalUnderInstallation = false;
	public:
		/// <summary>
		/// 位置設定
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3 pos)
		{
			m_arrangementPos = pos;
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
		void InitAddress(Crystal* crystal)
		{
			m_crystalAddress = crystal;
		}
		/// <summary>
		/// アドレス取得
		/// </summary>
		/// <returns></returns>
		Crystal* GetAddress() const
		{
			return m_crystalAddress;
		}
		/// <summary>
		/// 配置中かどうかを設定
		/// </summary>
		/// <param name="is"></param>
		void SetIsCrystalUnderInstallation(const bool is)
		{
			m_isCrystalUnderInstallation = is;
		}
		/// <summary>
		/// 配置中かどうかを取得
		/// </summary>
		/// <returns></returns>
		const bool GetIsCrystalUnderInstallation() const
		{
			return m_isCrystalUnderInstallation;
		}
	};
	/// <summary>
	/// クリスタルの位置データを格納しておく
	/// </summary>
	std::vector<CrystalArrangementData*> m_crystalArrangementDatas;
	/// <summary>
	/// クリスタルの配置位置を取得するためのレベルレンダー
	/// </summary>
	LevelRender m_crystalArrangementLevelRender;
};


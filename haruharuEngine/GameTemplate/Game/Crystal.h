#pragma once
#include "BootObjectBase.h"

class Player;
class CrystalGetCommandSprite;
class ManagerCrystal;
class PlayerScoreUi;

class Crystal : public BootObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Crystal();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Crystal();
	/// <summary>
	/// このクリスタルは採取されました
	/// </summary>
	void CrystalCollected();
	/// <summary>
	/// このクリスタルの採取に失敗しました
	/// </summary>
	void CollectedFailure()
	{
		//採取クールタイムを初期化
		m_collectCoolTime = 2.0f;
	}
	//クリスタルを配置する
	void CrystalArrangement()
	{
		m_isGetObject = false;
	}
	/// <summary>
	/// 採取されているかどうかを取得
	/// </summary>
	/// <returns></returns>
	const bool GetCollected() const
	{
		return m_isGetObject;
	}
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// クリスタル取得関数
	/// </summary>
	void GetCrystal();
	/// <summary>
	/// レイテストを行って壁がないかどうかを調べる関数
	/// </summary>
	/// <returns></returns>
	const bool IsLookCrystal();
	/// <summary>
	/// 取得範囲内にプレイヤーがいるかどうか調べる関数
	/// </summary>
	/// <returns></returns>
	const bool IsInGetRange();
	/// <summary>
	/// レンダー関数
	/// </summary>
	void Render(RenderContext& rc); 
	/// <summary>
	/// このオブジェクトが取得されているかどうか
	/// </summary>
	bool m_isGetObject = false;
	/// <summary>
	/// 採取クールタイム
	/// </summary>
	float m_collectCoolTime = 0.0f;
	/// <summary>
	/// コライダー
	/// </summary>
	SphereCollider m_sphereCollider;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	Player* m_player = nullptr;
	/// <summary>
	/// クリスタルの取得コマンド表示プログラムのインスタンス
	/// </summary>
	CrystalGetCommandSprite* m_GetCOMSprite = nullptr;
	/// <summary>
	/// デバック用のfontrender
	/// </summary>
	FontRender m_debugFontRender;
	/// <summary>
	/// クリスタルのメタAIのインスタンス
	/// </summary>
	ManagerCrystal* m_managerCrystalPtr = nullptr;
	/// <summary>
	/// スコアのUi
	/// </summary>
	PlayerScoreUi* m_scoreUi = nullptr;
	/// <summary>
	/// スコア
	/// </summary>
	float m_score = 160.0f;
};


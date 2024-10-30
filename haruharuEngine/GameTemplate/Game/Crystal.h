#pragma once
#include "ObjectBase.h"

class Player;
class CrystalGetCommandSprite;

class Crystal : public ObjectBase
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
	void CrystalCollected()
	{
		//取得フラグをtrueに
		m_isGetObject = true;
	}
	/// <summary>
	/// このクリスタルの採取に失敗しました
	/// </summary>
	void CollectedFailure()
	{
		//採取クールタイムを初期化
		m_collectCoolTime = 2.0f;
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
};


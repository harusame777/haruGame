#pragma once
#include "PlayerUIBase.h"
//一時的なモノ↓後で時間処理を実装する
#include "EnemyAIConBase.h"

class Player;

class PlayerScanCrystalUi : public PlayerUIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerScanCrystalUi() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerScanCrystalUi() {};
private:
	enum ScanState
	{
		/// <summary>
		/// 待機状態
		/// </summary>
		en_scanStandby,
		/// <summary>
		/// 走査線を描画
		/// </summary>
		en_scanLineEasing,
		/// <summary>
		/// アルファ値をイージング
		/// </summary>
		en_scanAEasing,
		/// <summary>
		/// マーカーを描画
		/// </summary>
		en_scanMarkerDraw,
	};
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
	/// スプライト更新
	/// </summary>
	void SpriteUpdate();
	/// <summary>
	/// アルファ値のイージング
	/// </summary>
	/// <returns></returns>
	const float AlphaEasing();
	/// <summary>
	/// ワイプのイージング関数
	/// </summary>
	/// <returns></returns>
	const float WipeEasing();
	/// <summary>
	/// ドロー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// スキャンステート
	/// </summary>
	ScanState m_scanState = ScanState::en_scanStandby;
	/// <summary>
	/// 走査線のスプライト
	/// </summary>
	SpriteRender m_scanlineSprite;
	/// <summary>
	/// 走査線のデータ
	/// </summary>
	struct ScanLineSpriteData
	{
		/// <summary>
		/// ワイプ方向
		/// </summary>
		Vector2 m_wipeDir;
		/// <summary>
		/// ワイプサイズ
		/// </summary>
		float m_wipeSize;
		/// <summary>
		/// アルファ値
		/// </summary>
		float m_paramA = 1.0f;
	};
	/// <summary>
	/// 走査線のデータ変数
	/// </summary>
	ScanLineSpriteData m_scanLineData;
	/// <summary>
	/// アルファ値割合
	/// </summary>
	float m_alphaRatio = 0.0f;
	/// <summary>
	/// イージング入れ替え
	/// </summary>
	bool m_swapEasing = true;
	/// <summary>
	/// ワイプ割合
	/// </summary>
	float m_wipeRatio = 1.0f;
	/// <summary>
	/// スキャンフラグ
	/// </summary>
	bool m_scanFlag = false;
	/// <summary>
	/// スキャン開始
	/// </summary>
	void ScanStart()
	{
		//スキャンフラグをtrueにする
		m_scanFlag = true;
		//スキャンステートをアルファ値イージングに変更する
		m_scanState = ScanState::en_scanLineEasing;
		//イージング割合を初期化する
		//アルファ値イージング
		m_swapEasing = true;
		m_scanLineData.m_paramA = 0.3;
		m_alphaRatio = 0.0f;
		//ワイプイージング
		m_scanLineData.m_wipeSize = 0.0f;
		m_wipeRatio = 0.0f;
	}
	/// <summary>
	/// スキャン終了
	/// </summary>
	void ScanEnd()
	{
		m_scanFlag = false;
	}
	/// <summary>
	/// flaot用線形補間
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}

	//仮時間処理
	EnemyAIConBase* m_waitTime = nullptr;
};


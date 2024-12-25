#pragma once
#include "PlayerUIBase.h"

class Game;

class PlayerOxygenUi : public PlayerUIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerOxygenUi() {}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerOxygenUi(){}
	/// <summary>
	/// 外部からタイマーのポインタを格納する関数
	/// </summary>
	/// <param name="timerPtr"></param>
	void InitTimerPtr(float* timerPtr)
	{
		m_gameTimer = timerPtr;
	}
private:
	/// <summary>
	/// 酸素ゲージステート
	/// </summary>
	enum OxygenGaugeState
	{
		en_oxygenHigh,

		en_oxygenLow,

		en_oxygenMin,
	};
	OxygenGaugeState m_oxygenGaugeState = OxygenGaugeState::en_oxygenHigh;
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
	/// 酸素ゲージステート更新関数
	/// </summary>
	const OxygenGaugeState& OxygenGaugeStateUpdate();
	/// <summary>
	/// 酸素ゲージ点滅処理関数
	/// </summary>
	void BlinkingOxygenGaugeCalc();
	/// <summary>
	/// ワイプ計算
	/// </summary>
	const float& WipeCalc();
	/// <summary>
	/// アルファ値イージング関数
	/// </summary>
	const float& AlphaEasing(const float& speed);
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 酸素ゲージのデータ
	/// </summary>
	struct OxygenGaugeSpriteData
	{
	private:
		/// <summary>
		/// ワイプ方向
		/// </summary>
		Vector2 m_wipeDir;
		/// <summary>
		/// ワイプサイズ
		/// </summary>
		float m_wipeSize = 0;
		/// <summary>
		/// アルファ値
		/// </summary>
		float m_alpha = 0.7f;
		/// <summary>
		/// カラーステート
		/// </summary>
		int m_colorState = OxygenGaugeState::en_oxygenHigh;
	public:
		/// <summary>
		/// 割合初期化
		/// </summary>
		/// <param name="value"></param>
		void SetDegree(const float value)
		{
			m_wipeSize = value;
		}
		/// <summary>
		/// 割合加算
		/// </summary>
		/// <param name="addValue"></param>
		void AddDegree(const float addValue)
		{
			m_wipeSize += addValue;
		}
		/// <summary>
		/// 割合取得
		/// </summary>
		/// <returns></returns>
		const float& GetDegree() const
		{
			return m_wipeSize;
		}
		/// <summary>
		/// 方向決定
		/// </summary>
		/// <param name="value"></param>
		void SetDirction(const Vector2 value)
		{
			m_wipeDir = value;
		}
		/// <summary>
		/// 方向取得
		/// </summary>
		/// <returns></returns>
		const Vector2& GetDirction() const
		{
			return m_wipeDir;
		}
		/// <summary>
		/// アルファ値初期化
		/// </summary>
		/// <param name="value"></param>
		void SetAlpha(const float value)
		{
			m_alpha = value;
		}
		/// <summary>
		/// アルファ値加算
		/// </summary>
		/// <param name="addValue"></param>
		void AddAlpha(const float addValue)
		{
			m_alpha += addValue;
		}
		/// <summary>
		/// アルファ値取得
		/// </summary>
		/// <returns></returns>
		const float& GetAlpha() const
		{
			return m_alpha;
		}
		/// <summary>
		/// カラーステート設定
		/// </summary>
		/// <param name="value"></param>
		void SetColorState(const OxygenGaugeState value)
		{
			m_colorState = value;
		}
	};
	/// <summary>
	/// 酸素ゲージのデータ
	/// </summary>
	OxygenGaugeSpriteData m_oxygenGaugeSpriteData;
	/// <summary>
	/// ゲームタイマー
	/// </summary>
	float* m_gameTimer = nullptr;
	/// <summary>
	/// タイマー
	/// </summary>
	float m_mainOxygenIndex = 0.0f;
	/// <summary>
	/// アルファ値イージング割合
	/// </summary>
	float m_alphaRatio = 0.0f;
	/// <summary>
	/// アルファ値イージング反転フラグ
	/// </summary>
	bool m_alphaEasingInversionFlag = true;
	/// <summary>
	/// UI枠
	/// </summary>
	SpriteRender m_oxygenUiBase;
	/// <summary>
	/// UIゲージ
	/// </summary>
	SpriteRender m_oxygenUiGauge;
	/// <summary>
	/// ゲージのアルファ値調整テクスチャ
	/// </summary>
	Texture m_m_oxygenGaugeAlphaTexture;
	/// <summary>
	/// ゲームのインスタンス
	/// </summary>
	Game* m_game = nullptr;
	/// <summary>
	/// デバック用のフォントレンダー
	/// </summary>
	FontRender m_debugFontRender;
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
};


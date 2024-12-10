#pragma once
#include "PlayerUIBase.h"

//定数等
namespace {
	/// <summary>
	/// スタミナ最大値
	/// </summary>
	static const float MAX_STAMINA_INDEX = 100; 

	static const float INIT_DEGREE_VALUE = 2.7f;

	static const float MAX_DEGREE_VALUE = 3.6f;
}

class PlayerStaminaUi : public PlayerUIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerStaminaUi(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerStaminaUi(){}
	/// <summary>
	/// プレイヤーのスタミナの変数のポインタで初期化
	/// </summary>
	/// <param name="staminaPtr"></param>
	void InitPlayerStaminaPtr(float* staminaPtr)
	{
		m_playerStamina = staminaPtr;
	}
private:
	/// <summary>
	/// スタミナUiのステート
	/// </summary>
	enum StaminaUiState
	{
		en_staminaHigh,

		en_staminaLow,

		en_staminaOut,
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
	/// スタミナステートアップデート関数
	/// </summary>
	void StaminaStateUpdate();
	/// <summary>
	/// スタミナバー点滅関数
	/// </summary>
	void BlinkingBarCalc();
	/// <summary>
	/// アルファ値イージング関数
	/// </summary>
	const float& AlphaEasing();
	/// <summary>
	/// ワイプ計算関数
	/// </summary>
	/// <returns></returns>
	const float& WipeCalc();
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// スタミナバーのデータ
	/// </summary>
	struct StaminaBarData
	{
	private:
		//割合
		float m_degree = INIT_DEGREE_VALUE;
		//α値
		float m_alpha = 0.7f;
		//r値
		bool m_redAddFlag = false;
	public:
		/// <summary>
		/// 割合初期化
		/// </summary>
		/// <param name="value"></param>
		void SetDegree(const float value)
		{
			m_degree = value;
		}
		/// <summary>
		/// 割合加算
		/// </summary>
		/// <param name="addValue"></param>
		void AddDegree(const float addValue)
		{
			m_degree += addValue;
		}
		/// <summary>
		/// 割合取得
		/// </summary>
		/// <returns></returns>
		const float& GetDegree() const
		{
			return m_degree;
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
		/// 赤加算フラグ設定
		/// </summary>
		/// <param name="setFlag"></param>
		void SetRedAddFlag(const bool setFlag)
		{
			m_redAddFlag = setFlag;
		}
	};
	StaminaBarData m_staminaBarData;
	/// <summary>
	/// スタミナUiステート
	/// </summary>
	StaminaUiState m_staminaState = StaminaUiState::en_staminaHigh;
	/// <summary>
	/// プレイヤーのスタミナ
	/// </summary>
	float* m_playerStamina = nullptr;
	/// <summary>
	/// Ui内のスタミナ
	/// </summary>
	float m_mainStamina = 0;
	/// <summary>
	/// アルファ値イージング割合
	/// </summary>
	float m_alphaRatio = 0.0f;
	/// <summary>
	/// スタミナが空になったかのフラグ
	/// </summary>
	bool m_staminaOutFlag = false;
	/// <summary>
	/// アルファ値イージング反転フラグ
	/// </summary>
	bool m_alphaEasingInversionFlag = true;
	/// <summary>
	/// スタミナベースUi
	/// </summary>
	SpriteRender m_staminaBase;
	/// <summary>
	/// スタミナバーUi
	/// </summary>
	SpriteRender m_staminaBar;
	/// <summary>
	/// スタミナバーUiのアルファ操作用テクスチャ
	/// </summary>
	Texture m_staminaBarAlphaTexture;
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


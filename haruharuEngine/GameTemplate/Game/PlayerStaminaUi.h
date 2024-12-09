#pragma once
#include "PlayerUIBase.h"

//定数等
namespace {
	/// <summary>
	/// スタミナ最大値
	/// </summary>
	static const float MAX_STAMINA_INDEX = 100; 

	static const float INIT_DEGREE_VALUE = 0.7f;

	static const float MAX_DEGREE_VALUE = 5.6f;
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
	void InitPlayerStaminaPtr(int* staminaPtr)
	{
		m_playerStamina = staminaPtr;
	}
private:
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
		float m_alpha = 1.0f;
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
		void AddDegree(const float& addValue)
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
	};
	StaminaBarData m_staminaBarData;
	/// <summary>
	/// プレイヤーのスタミナ
	/// </summary>
	int* m_playerStamina = nullptr;
	/// <summary>
	/// Ui内のスタミナ
	/// </summary>
	int m_mainStamina = 0;
	/// <summary>
	/// イージング割合
	/// </summary>
	float m_ratio = 0.0f;
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


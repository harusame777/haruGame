#pragma once
#include "PlayerUIBase.h"

//定数等
namespace {
	/// <summary>
	/// スタミナ最大値
	/// </summary>
	static const int MAX_STAMINA_INDEX = 100; 
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
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// スタミナバーのデータ
	/// </summary>
	struct StaminaBarData
	{
	
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
	/// スタミナベースUi
	/// </summary>
	SpriteRender m_staminaBase;
	/// <summary>
	/// スタミナバーUi
	/// </summary>
	SpriteRender m_staminaBar;

};


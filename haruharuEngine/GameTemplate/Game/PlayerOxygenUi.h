#pragma once
#include "PlayerUIBase.h"

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
	/// ゲームタイマー
	/// </summary>
	float* m_gameTimer = nullptr;
	/// <summary>
	/// タイマー
	/// </summary>
	float m_mainTimer = 0.0f;
};


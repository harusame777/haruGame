#pragma once
#include "PlayerUIBase.h"

class PlayerScoreUi : public PlayerUIBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerScoreUi() {}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerScoreUi() {}
	/// <summary>
	/// スコアを増やす関数
	/// </summary>
	/// <param name="scoreAddIndex"></param>
	void ScoreAdd(int scoreAddIndex)
	{
		if (m_isScoreUpdate == true)
		{
			return;
		}

		m_isScoreUpdate = true;

		m_addScoreIndex = scoreAddIndex / 2.0f;

		m_newScoreIndex = m_mainScore + scoreAddIndex;
		
		return;
	}
	/// <summary>
	/// メインスコアを設定
	/// </summary>
	/// <param name="ptr"></param>
	void InitMainScorePtr(float& ptr)
	{
		m_gameScore = &ptr;
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
	/// スコアナンバーのアップデート
	/// </summary>
	void ScoreNumUpdate();
	/// <summary>
	/// スコアの計算
	/// </summary>
	const float ScoreCalc();
	/// <summary>
	/// レンダー関数
	/// </summary>
	void Render(RenderContext& rc);
	/// <summary>
	/// スコアベーススプライト
	/// </summary>
	SpriteRender m_scoreBase;
	/// <summary>
	/// スコアの数スプライト
	/// </summary>
	FontRender m_scoreNum;
	/// <summary>
	/// スコア
	/// </summary>
	FontRender m_socore;
	/// <summary>
	/// メインスコア
	/// </summary>
	float m_mainScore = 0;
	/// <summary>
	/// ゲームのスコア
	/// </summary>
	float* m_gameScore = nullptr;
	/// <summary>
	/// 新しいスコアの数値
	/// </summary>
	float m_newScoreIndex = 0;
	/// <summary>
	/// 加算値
	/// </summary>
	float m_addScoreIndex = 0;
	/// <summary>
	/// スコアのスプライトに表示する文字
	/// </summary>
	wchar_t wcsbuf[256];
	/// <summary>
	/// スコアが更新中かどうか
	/// </summary>
	bool m_isScoreUpdate = false;
};


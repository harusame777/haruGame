#pragma once

class Load;

class Result : public IGameObject
{
private:

	enum ResultState
	{
		en_standby,

		en_infoDrowTop,

		en_infoDrowMiddle,

		en_infoDrowBottom,

		en_infoIndexAdd,

		en_infoResultEnd,
	};
	ResultState m_resultState = ResultState::en_standby;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Result(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Result(){}
	/// <summary>
	/// 最終スコア設定
	/// </summary>
	/// <param name="score"></param>
	void SetFinalScore(const float& score)
	{
		m_scoreIndex = score;
	}
	/// <summary>
	/// リザルトが終了したかどうか
	/// </summary>
	/// <returns></returns>
	const bool& IsResultEnd()
	{
		return m_isResultEnd;
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
	/// リザルトステートのアップデート
	/// </summary>
	void ResultStateUpdate();
	/// <summary>
	/// フォントアップデート
	/// </summary>
	void FontUpdate();
	/// <summary>
	/// 時間指定待機ステート
	/// </summary>
	/// <param name="time"></param>
	/// <returns></returns>
	const bool& WaitTime(const float& time);
	/// <summary>
	/// タイマー
	/// </summary>
	float m_timer = 0.0f;
	/// <summary>
	/// タイマー最大値
	/// </summary>
	float m_timerMax = 0.0f;
	/// <summary>
	/// スコア値のイージング関数
	/// </summary>
	void ScoreEasing();
	/// <summary>
	/// スコア加算値
	/// </summary>
	float m_scoreAddIndex = 0.0f;
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 文字列
	/// </summary>
	FontRender m_resultInfoTop;
	FontRender m_resultInfoBottom;
	FontRender m_resultInfoMiddle;
	/// <summary>
	/// 後ろ側のスプライト
	/// </summary>
	SpriteRender  m_backSideSprite;
	/// <summary>
	/// スコア数値
	/// </summary>
	float m_scoreIndex = 0.0f;
	/// <summary>
	/// インフォメーションに書き込まれる数値
	/// </summary>
	float m_infoDrawIndex = 0.0f;
	/// <summary>
	/// リザルトが終了したかどうか
	/// </summary>
	bool m_isResultEnd = false;
	/// <summary>
	/// ロードのインスタンス
	/// </summary>
	Load* m_load = nullptr;
};


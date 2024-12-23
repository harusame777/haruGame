#pragma once
class Result : public IGameObject
{
private:

	enum ResultState
	{
		en_standby,

		en_infoDrowTop,

		en_infoDrowMiddle,

		en_infoDrowBottom,

		en_infoIndexAdd
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

	void ResultStateUpdate();

	void FontUpdate();

	const bool& WaitTime(const float& time);

	float m_timer = 0.0f;

	float m_timerMax = 0.0f;

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

	float m_infoDrawIndex = 0.0f;
};


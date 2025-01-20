#include "stdafx.h"
#include "PlayerScoreUi.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//定数等
namespace {
	static const float SCOREBASE_SPRITE_W_SIZE = 1600.0f;
	static const float SCOREBASE_SPRITE_H_SIZE = 900.0f;

	static const Vector3 SCOREBASE_SPRITE_POSITION = { -630.0f,350.0f,0.0f };
	static const Vector3 SCOREBASE_SPRITE_SIZE = { 0.2f,0.2f,0.0f };

	static const Vector3 SCORENUM_SPRITE_POSITION = { -920.0f,460.0f,0.0f };
	static const float SCORENUM_SPRITE_SIZE = 2.0f;
}

//スタート関数
bool PlayerScoreUi::Start()
{
	//スコア枠の初期化
	m_scoreBase.Init("Assets/modelData/playerUI/PlayerScoreUi/Score_Base_1.DDS",
		SCOREBASE_SPRITE_W_SIZE,
		SCOREBASE_SPRITE_H_SIZE);

	m_scoreBase.SetPosition(SCOREBASE_SPRITE_POSITION);

	m_scoreBase.SetScale(SCOREBASE_SPRITE_SIZE);

	m_scoreNum.SetPosition(SCORENUM_SPRITE_POSITION);

	m_scoreNum.SetScale(SCORENUM_SPRITE_SIZE);

	m_scoreBase.Update();

	return true;
}

//アップデート関数
void PlayerScoreUi::Update()
{
#ifdef DEBUG_MODE
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		ScoreAdd(60);
	};
#endif

	//スコアナンバーを更新する
	ScoreNumUpdate();

	*m_gameScore = m_mainScore;

	m_scoreBase.Update();
}

//スコアナンバーを更新する関数
void PlayerScoreUi::ScoreNumUpdate()
{
	if (m_gameScore == nullptr)
	{
		return;
	}

	m_mainScore = ScoreCalc();

	swprintf_s(wcsbuf, 256, L"%06.1fg",float(m_mainScore));

	m_scoreNum.SetText(wcsbuf);
}

const float PlayerScoreUi::ScoreCalc()
{
	float finalScoreNum = m_mainScore;

	if (m_isScoreUpdate == false)
	{
		return finalScoreNum;
	}

	//もし、今のスコアよりも新しいスコアの方が大きかったら
	if (m_mainScore < m_newScoreIndex)
	{
		//スコアを増やす
		finalScoreNum += m_addScoreIndex * g_gameTime->GetFrameDeltaTime();

		return finalScoreNum;
	}
	//違ったら
	else
	{
		finalScoreNum = m_newScoreIndex;
		//スコアの更新処理を終了する
		m_isScoreUpdate = false;

		return finalScoreNum;
	}
}

//レンダー関数
void PlayerScoreUi::Render(RenderContext& rc)
{
	m_scoreBase.Draw(rc);

	m_scoreNum.Draw(rc);
}
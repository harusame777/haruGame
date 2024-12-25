#include "stdafx.h"
#include "Result.h"
#include "Load.h"

namespace {
	static const float BACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float BACKSIDE_SPRITE_H_SIZE = 900.0f;

	static const Vector3 FONT_TOP_POSITION = { -920.0f,400.0f,0.0f };
	static const Vector3 FONT_MIDDLE_POSITION = { -920.0f,200.0f,0.0f };
	static const Vector3 FONT_BOTTOM_POSITION = { -920.0f,0.0f,0.0f };

	static const float FONT_SIZE = 2.0f;

	static const Vector4 FONT_COLOR = { 0.5f,0.5f,1.0f,1.0f };
}

bool Result::Start()
{
	m_backSideSprite.Init("Assets/modelData/title/back_side_1.DDS",
		BACKSIDE_SPRITE_W_SIZE,
		BACKSIDE_SPRITE_H_SIZE);

	m_load = FindGO<Load>("load");

	return true;
}

void Result::Update()
{

	ResultStateUpdate();

	FontUpdate();

	m_backSideSprite.Update();
}

void Result::ResultStateUpdate()
{
	switch (m_resultState)
	{
	case Result::en_standby:

		if (WaitTime(2.0f))
		{
			m_resultState = ResultState::en_infoDrowTop;
		}

		break;
	case Result::en_infoDrowTop:

		if (WaitTime(0.5f))
		{
			m_resultState = ResultState::en_infoDrowMiddle;
		}

		break;
	case Result::en_infoDrowMiddle:

		if (WaitTime(0.5f))
		{
			m_resultState = ResultState::en_infoDrowBottom;
		}

		break;
	case Result::en_infoDrowBottom:

		if (WaitTime(2.0f))
		{
			m_resultState = ResultState::en_infoIndexAdd;

			m_scoreAddIndex = m_scoreIndex / 2.0f;
		}

		break;
	case Result::en_infoIndexAdd:

		ScoreEasing();

		break;
	case Result::en_infoResultEnd:

		if (WaitTime(5.0f))
		{

			m_load->LoadExecutionFadeOut({Load::en_loadOrdinary,Load::en_loadOrdinary});

		}

		break;
	case Result::en_ResultDelete:

		if (m_load->IsLoadBlackout())
		{
			DeleteGO(this);
		}

		break;
	default:
		break;
	}
}

void Result::FontUpdate()
{
	//トップインフォ
	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"RESULT");

	m_resultInfoTop.SetColor(FONT_COLOR);

	m_resultInfoTop.SetPivot({ 0.0f,0.0f });

	m_resultInfoTop.SetScale(FONT_SIZE);

	m_resultInfoTop.SetPosition(FONT_TOP_POSITION);

	m_resultInfoTop.SetText(wcsbuf);
	//ミドルインフォ
	swprintf_s(wcsbuf, 256, L"REMAINING AMOUNT");

	m_resultInfoMiddle.SetColor(FONT_COLOR);

	m_resultInfoMiddle.SetPivot({ 0.0f,0.0f });

	m_resultInfoMiddle.SetScale(FONT_SIZE);

	m_resultInfoMiddle.SetPosition(FONT_MIDDLE_POSITION);

	m_resultInfoMiddle.SetText(wcsbuf);
	//ボトムインフォ
	swprintf_s(wcsbuf, 256, L"[%06.1fg]", float(m_infoDrawIndex));

	m_resultInfoBottom.SetColor(FONT_COLOR);

	m_resultInfoBottom.SetPivot({ 0.0f,0.0f });

	m_resultInfoBottom.SetScale(FONT_SIZE);

	m_resultInfoBottom.SetPosition(FONT_BOTTOM_POSITION);

	m_resultInfoBottom.SetText(wcsbuf);
}

const bool& Result::WaitTime(const float& time)
{
	if (m_timerMax <= 0.0f)
	{
		m_timerMax = time;
	}

	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= m_timerMax)
	{
		m_timerMax = 0.0f;

		m_timer = 0.0f;

		return true;
	}

	return false;
}

void Result::ScoreEasing()
{
	float finalScoreNum = m_scoreIndex;

	//もし、今のスコアよりも新しいスコアの方が大きかったら
	if (m_infoDrawIndex < m_scoreIndex)
	{
		//スコアを増やす
		//m_infoDrawIndex += g_gameTime->GetFrameDeltaTime() * (m_scoreAddIndex + 0.1f);
		m_infoDrawIndex += 0.1f * m_scoreAddIndex;
	}
	//違ったら
	else
	{
		m_infoDrawIndex = m_scoreIndex;

		m_resultState = ResultState::en_infoResultEnd;
	}
}

void Result::Render(RenderContext& rc)
{
	m_backSideSprite.Draw(rc);

	if (m_resultState >= ResultState::en_infoDrowTop)
	m_resultInfoTop.Draw(rc);

	if (m_resultState >= ResultState::en_infoDrowMiddle)
	m_resultInfoMiddle.Draw(rc);

	if (m_resultState >= ResultState::en_infoDrowBottom)
	m_resultInfoBottom.Draw(rc);
}
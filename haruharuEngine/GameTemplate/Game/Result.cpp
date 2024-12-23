#include "stdafx.h"
#include "Result.h"

namespace {
	static const float BACKSIDE_SPRITE_W_SIZE = 1600.0f;
	static const float BACKSIDE_SPRITE_H_SIZE = 900.0f;

	static const Vector3 FONT_TOP_POSITION = { 0.0f,200.0f,0.0f };
	static const Vector3 FONT_MIDDLE_POSITION = { 0.0f,100.0f,0.0f };
	static const Vector3 FONT_BOTTOM_POSITION = { 0.0f,0.0f,0.0f };

	static const Vector4 FONT_COLOR = { 0.5f,0.5f,1.0f,1.0f };
}

bool Result::Start()
{
	m_backSideSprite.Init("Assets/modelData/title/back_side_1.DDS",
		BACKSIDE_SPRITE_W_SIZE,
		BACKSIDE_SPRITE_H_SIZE);

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
		}

		break;
	case Result::en_infoIndexAdd:



		break;
	default:
		break;
	}
}

void Result::FontUpdate()
{
	//トップインフォ
	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"Result");

	m_resultInfoTop.SetColor(FONT_COLOR);

	m_resultInfoTop.SetPivot({ 0.5f,0.5f });

	m_resultInfoTop.SetPosition(FONT_TOP_POSITION);

	m_resultInfoTop.SetText(wcsbuf);
	//ミドルインフォ
	swprintf_s(wcsbuf, 256, L"Remaining amount");

	m_resultInfoMiddle.SetColor(FONT_COLOR);

	m_resultInfoMiddle.SetPivot({ 0.5f,0.5f });

	m_resultInfoMiddle.SetPosition(FONT_MIDDLE_POSITION);

	m_resultInfoMiddle.SetText(wcsbuf);
	//ボトムインフォ
	swprintf_s(wcsbuf, 256, L"[%06.1fg]", float(m_infoDrawIndex));

	m_resultInfoBottom.SetColor(FONT_COLOR);

	m_resultInfoBottom.SetPivot({ 0.5f,0.5f });

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

void Result::Render(RenderContext& rc)
{
	m_backSideSprite.Draw(rc);

	if (m_resultState <= ResultState::en_infoDrowTop)
	m_resultInfoTop.Draw(rc);

	if (m_resultState <= ResultState::en_infoDrowMiddle)
	m_resultInfoMiddle.Draw(rc);

	if (m_resultState <= ResultState::en_infoDrowBottom)
	m_resultInfoBottom.Draw(rc);
}
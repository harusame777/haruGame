#include "stdafx.h"
#include "GameInformation.h"
#include "GameWindow.h"

//定数等
namespace {
	/// <summary>
	/// フォントのカラー
	/// </summary>
	static const Vector4 FONT_COLOR = { 0.3f,0.3f,1.0f,1.0f };
	static const Vector4 FONT_COLOR_TEST = { 1.0f,1.0f,1.0f,1.0f };
	static const float TIME_N = 0.05f;

}

//スタート関数
bool GameInformation::Start()
{
	m_gameWindow = NewGO<GameWindow>(1, "gameWindow");

	return true;
}

//アップデート関数
void GameInformation::Update()
{

	//if (g_pad[0]->IsTrigger(enButtonA))
	//{
	//	InitTextData(L"I am haruse takeda");
	//	InitTextData(L"I like harusame");
	//	InitTextData(L"Eigo amari tokuizyanai");
	//	InitTextData(L"test dayo");
	//	InitTextData(L"test5");
	//	InitTextData(L"test6");
	//	InitTextData(L"test7");
	//	InitTextData(L"test8");
	//	InitTextData(L"test9");
	//	GoInformation();
	//}

	InformationStateUpdate();

	DisplayTextUpdate();

}

void GameInformation::InformationStateUpdate()
{
	switch (m_gameInformationState)
	{
	case GameInformation::en_standby:

		//待機

		break;
	case GameInformation::en_windowOpen:

		//ウィンドウ開くまで待機
		if (m_gameWindow->IsWindowOpen())
		{
			//開いたらステートを変更
			StateChange(GameInformationState::en_textDraw);
		}

		break;
	case GameInformation::en_textDraw:

		if (m_textDataList[m_listNowNum].
			m_externalInputTextList[m_nowTextNum] == L'\0')
		{
			if (m_listNowNum > m_listEndNum)
			{
				StateChange(GameInformationState::en_openWait);

				return;
			}

			m_nowTextNum = 0;

			m_listNowNum++;
		}

		if (Delay(TIME_N))
		{
			DisplayTextListUpdate();
		}

		break;
	case GameInformation::en_openWait:

		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_gameWindow->WindowClose();

			StateChange(GameInformationState::en_windowClose);
		}

		break;
	case GameInformation::en_windowClose:

		if (m_gameWindow->IsWindowClose())
		{
			StateChange(GameInformationState::en_end);
		}

		break;
	case GameInformation::en_end:

		for (int listNo = 0;
			listNo < MAX_TEXTDATALIST_EXP;
			listNo++)
		{

			m_textDataList[listNo].m_mainFontRender.SetText(L"");

			std::memset(m_textDataList[listNo].m_displayTextList,
				0,
				sizeof(m_textDataList[listNo].m_displayTextList));

			std::memset(m_textDataList[listNo].m_externalInputTextList,
				0,
				sizeof(m_textDataList[listNo].m_externalInputTextList));

			m_textDataList[listNo].m_textPos = Vector3::Zero;

			m_textDataList[listNo].m_isUse = false;

			m_nowTextNum = 0;

			m_listEndNum = 0;

			m_listNowNum = 0;
		}

		StateChange(GameInformationState::en_standby);

		break;
	default:
		break;
	}
}

//遅延関数
bool GameInformation::Delay(const float delayTime)
{
	if (m_textDelayTime < 0.0f)
	{
		m_textDelayTime = delayTime;

		return true;
	}

	m_textDelayTime -= g_gameTime->GetFrameDeltaTime();

	return false;
}

void GameInformation::DisplayTextUpdate()
{
	m_textDataList[m_listNowNum].m_mainFontRender.SetColor(FONT_COLOR_TEST);

	m_textDataList[m_listNowNum].m_mainFontRender.SetPivot({ 0.5f,0.5f });

	m_textDataList[m_listNowNum].m_mainFontRender
		.SetPosition(m_textDataList[m_listNowNum].m_textPos);

	m_textDataList[m_listNowNum].m_mainFontRender.
		SetText(m_textDataList[m_listNowNum].m_displayTextList);
}

//表示文字配列更新関数
void GameInformation::DisplayTextListUpdate()
{

	m_nowTextNum++;

	wcsncpy_s(m_textDataList[m_listNowNum].m_displayTextList,
		_countof(m_textDataList[m_listNowNum].m_displayTextList),
		m_textDataList[m_listNowNum].m_externalInputTextList,
		m_nowTextNum
	);

}

//レンダー関数
void GameInformation::Render(RenderContext& rc)
{
	if (m_gameInformationState != GameInformationState::en_textDraw &&
		m_gameInformationState != GameInformationState::en_openWait)
	{
		return;
	}

	for (int listNo = 0;
		listNo < MAX_TEXTDATALIST_EXP;
		listNo++)
	{
		m_textDataList[listNo].m_mainFontRender.Draw(rc);
	}
}
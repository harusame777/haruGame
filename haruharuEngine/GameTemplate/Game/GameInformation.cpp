#include "stdafx.h"
#include "GameInformation.h"
#include "GameWindow.h"
#include "GameSound.h"

//定数等
namespace GameInfoNS_CPP{
	/// <summary>
	/// フォントのカラー
	/// </summary>
	static const Vector4 FONT_COLOR = { 0.3f,0.3f,1.0f,1.0f };
	static const Vector4 MAINTEXT_COLOR = { 1.0f,1.0f,1.0f,1.0f };
	static const Vector4 CLOSETEXT_COLOR = { 0.3f,0.1f,0.1f,1.0f };
	static const float TIME_TEXT_DELAY = 0.02f;
	static const wchar_t TEXT_UNDER_BAR[2] = { L"_" };

}

//スタート関数
bool GameInformation::Start()
{
	m_gameWindow = NewGO<GameWindow>(1, "informationGameWindow");

	m_gameSound = FindGO<GameSound>("gameSound");

	return true;
}

//起動関数
void GameInformation::GoInformation()
{
	if (m_gameInformationState != GameInformationState::en_standby)
	{
		return;
	}

	for (int listNo = 0;
		listNo < GameInfoNS_H::MAX_TEXTDATALIST_EXP;
		listNo++)
	{

		m_listEndNum = listNo - 1;

		if (m_textDataList[listNo].m_isUse == false)
		{
			break;
		}

	}

	//ウィンドウを開ける
	m_gameWindow->WindowOpen();
	//ステートをwindowOpenに変更
	StateChange(GameInformationState::en_windowOpen);
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

		//文字送り
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			for (int listNo = m_listNowNum;
				listNo < GameInfoNS_H::MAX_TEXTDATALIST_EXP - 1;
				listNo++)
			{
				m_nowTextNum = (wcslen(m_textDataList[listNo]
					.m_externalInputTextList) - 1);

				DisplayTextListUpdate();

				DisplayTextUpdate();

				m_listNowNum++;
			}

			m_closeButtonTextDrawFlag = true;

			StateChange(GameInformationState::en_openWait);

			return;
		}

		//文字リスト更新
		if (m_textDataList[m_listNowNum].
			m_externalInputTextList[m_nowTextNum] == L'\0')
		{
			if (m_listNowNum > m_listEndNum)
			{
				m_closeButtonTextDrawFlag = true;

				StateChange(GameInformationState::en_openWait);

				return;
			}

			DisplayTextListUpdate();

			m_nowTextNum = 0;

			m_listNowNum++;
		}

		//表示文字更新
		if (Delay(GameInfoNS_CPP::TIME_TEXT_DELAY))
		{
			DisplayTextListUpdate();
		}

		break;
	case GameInformation::en_openWait:

		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_gameWindow->WindowClose();

			m_isInformationCloseing = true;

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
			listNo < GameInfoNS_H::MAX_TEXTDATALIST_EXP;
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

		m_isInformationCloseing = false;

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
	m_textDataList[m_listNowNum].m_mainFontRender.SetColor(GameInfoNS_CPP::MAINTEXT_COLOR);

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

	if (m_textDataList[m_listNowNum].
		m_externalInputTextList[m_nowTextNum] != L' ')
		m_gameSound->LocalSoundOrder(GameSound::en_fontIn, false, 0.5f);

	wcsncpy_s(m_textDataList[m_listNowNum].m_displayTextList,
		_countof(m_textDataList[m_listNowNum].m_displayTextList),
		m_textDataList[m_listNowNum].m_externalInputTextList,
		m_nowTextNum
	);

	if (m_textDataList[m_listNowNum].
		m_externalInputTextList[m_nowTextNum] == L'\0')
		return;

	wcsncat_s(m_textDataList[m_listNowNum].m_displayTextList,
		GameInfoNS_CPP::TEXT_UNDER_BAR, 1);

}

//レンダー関数
void GameInformation::Render(RenderContext& rc)
{
	if (m_gameInformationState != GameInformationState::en_textDraw &&
		m_gameInformationState != GameInformationState::en_openWait)
	{
		return;
	}

	if (m_closeButtonTextDrawFlag == true)
	{
		wchar_t wcsbuf[256] = {};

		swprintf_s(wcsbuf, 256, L"Close Push Button B");

		m_closeButtonText.SetText(wcsbuf);

		m_closeButtonText.SetPosition({ 230.0f,-400.0f,0.0f });

		m_closeButtonText.SetColor(GameInfoNS_CPP::CLOSETEXT_COLOR);

		m_closeButtonText.Draw(rc);
	}

	for (int listNo = 0;
		listNo < GameInfoNS_H::MAX_TEXTDATALIST_EXP;
		listNo++)
	{
		m_textDataList[listNo].m_mainFontRender.Draw(rc);
	}
}
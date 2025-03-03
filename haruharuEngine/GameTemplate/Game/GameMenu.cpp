#include "stdafx.h"
#include "GameMenu.h"
#include "GameWindow.h"
#include "GameSound.h"

//定数等
namespace GameMenuNS_CPP{
	/// <summary>
	/// フォントのカラー
	/// </summary>
	static const Vector4 FONT_COLOR = { 0.3f,0.3f,1.0f,1.0f };
	static const Vector4 MAINTEXT_COLOR = { 1.0f,1.0f,1.0f,1.0f };
	static const float TIME_TEXT_DELAY = 0.02f;
	static const float TIME_TEXT_SELECTION_DELAY = 0.5f;
	static const wchar_t TEXT_UNDER_BAR[2] = { L"_" };

	static const float MOUSECORSOR_SPRITE_W_SIZE = 34.0f;
	static const float MOUSECORSOR_SPRITE_H_SIZE = 38.0f;
}

bool GameMenu::Start()
{
	m_gameWindow = NewGO<GameWindow>(1,"menuGameWindow");

	m_gameSound = FindGO<GameSound>("gameSound");

	m_mouseCursor.Init("Assets/modelData/window/mouse_cursor.DDS",
		GameMenuNS_CPP::MOUSECORSOR_SPRITE_W_SIZE,
		GameMenuNS_CPP::MOUSECORSOR_SPRITE_H_SIZE
	);

	m_mouseCursor.SetPivot({ 1.0f,1.0f });

	return true;
}

void GameMenu::GoMenuOpen()
{
	if (m_gameMenuState != GameMenuState::en_standby)
	{
		return;
	}

	for (int listNo = 0;
		listNo < GameMenuNS_H::MAX_TEXTDATALIST_EXP;
		listNo++)
	{

		m_listEndNum = listNo - 1;

		if (m_menuDatas[listNo].m_isUse == false)
		{
			break;
		}

	}

	m_gameWindow->WindowOpen();

	m_gameMenuState = GameMenuState::en_windowOpen;

}

void GameMenu::Update()
{
	//メニューのステートのアップデート
	MenuStateUpdate();
	//表示テキストのアップデート
	DisplayTextUpdate();
	//マウスカーソルのアップデート
	m_mouseCursor.Update();
}

void GameMenu::MenuStateUpdate()
{
	bool func = false;

	switch (m_gameMenuState)
	{
	case GameMenu::en_standby:

		//待機

		break;
	case GameMenu::en_windowOpen:

		//ウィンドウ開くまで待機
		if (m_gameWindow->IsWindowOpen())
		{
			//開いたらステートを変更
			StateChange(GameMenuState::en_textDraw);
		}

		break;
	case GameMenu::en_textDraw:

		TextDrawUpdate();

		break;
	case GameMenu::en_menuSelection:

		MenuSelectionUpdate();

		break;
	case GameMenu::en_windowClose:

		if (m_gameWindow->IsWindowClose())
		{			
			if (m_isFuncBoot == false)
			{
				StateChange(GameMenu::en_end);

				return;
			}

			if (m_isInitCloseFunc == true)
				StateChange(GameMenuState::en_closeMenuFuntionGo);
			else
				StateChange(GameMenuState::en_selectionMenuFunctionGo);
		}

		break;
	case GameMenu::en_closeMenuFuntionGo:

		func = m_menuCloseFunction();

		m_isMenuClose = true;

		StateChange(GameMenu::en_end);

		break;
	case GameMenu::en_selectionMenuFunctionGo:

		func = m_menuDatas[m_confirmedMenuSelectionNum].m_menuBootFunction();

		m_isMenuClose = true;

		StateChange(GameMenu::en_end);
			
		break;
	case GameMenu::en_end:

		m_isMenuClose = false;

		m_isFuncBoot = false;

		InitMenuDetasList();

		StateChange(GameMenuState::en_standby);

		break;
	default:
		break;
	}

}

void GameMenu::TextDrawUpdate()
{
	//文字送り
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		for (int listNo = m_listNowNum;
			listNo < GameMenuNS_H::MAX_TEXTDATALIST_EXP - 1;
			listNo++)
		{
			m_nowTextNum = (wcslen(m_menuDatas[listNo]
				.m_externalInputTextList) - 1);

			DisplayTextListUpdate();

			DisplayTextUpdate();

			m_listNowNum++;
		}

		m_isMouseCorsorDraw = true;

		StateChange(GameMenu::en_menuSelection);

		return;
	}

	//文字リスト更新
	if (m_menuDatas[m_listNowNum].
		m_externalInputTextList[m_nowTextNum] == L'\0')
	{
		if (m_listNowNum > m_listEndNum)
		{
			m_isMouseCorsorDraw = true;

			StateChange(GameMenu::en_menuSelection);

			return;
		}

		DisplayTextListUpdate();

		m_nowTextNum = 0;

		m_listNowNum++;
	}

	//表示文字更新
	if (Delay(GameMenuNS_CPP::TIME_TEXT_DELAY))
	{
		DisplayTextListUpdate();
	}
}

//遅延関数
bool GameMenu::Delay(const float delayTime)
{
	if (m_textDelayTime < 0.0f)
	{
		m_textDelayTime = delayTime;

		return true;
	}

	m_textDelayTime -= g_gameTime->GetFrameDeltaTime();

	return false;
}

void GameMenu::DisplayTextUpdate()
{
	m_menuDatas[m_listNowNum].m_fontRender.SetColor(GameMenuNS_CPP::MAINTEXT_COLOR);

	m_menuDatas[m_listNowNum].m_fontRender.SetPivot({ 0.5f,0.5f });

	m_menuDatas[m_listNowNum].m_fontRender
		.SetPosition(m_menuDatas[m_listNowNum].m_textPos);

	m_menuDatas[m_listNowNum].m_fontRender.
		SetText(m_menuDatas[m_listNowNum].m_displayTextList);
}


//表示文字配列更新関数
void GameMenu::DisplayTextListUpdate()
{

	m_nowTextNum++;

	if (m_menuDatas[m_listNowNum].
		m_externalInputTextList[m_nowTextNum] != L' ')
		m_gameSound->LocalSoundOrder(GameSound::en_fontIn, false, 0.5f);

	wcsncpy_s(m_menuDatas[m_listNowNum].m_displayTextList,
		_countof(m_menuDatas[m_listNowNum].m_displayTextList),
		m_menuDatas[m_listNowNum].m_externalInputTextList,
		m_nowTextNum
	);

	if (m_menuDatas[m_listNowNum].
		m_externalInputTextList[m_nowTextNum] == L'\0')
		return;

	wcsncat_s(m_menuDatas[m_listNowNum].m_displayTextList,
		GameMenuNS_CPP::TEXT_UNDER_BAR, 1);

}

void GameMenu::MenuSelectionUpdate()
{
	//メニュー選択で上を選択する処理
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		if (m_nowMenuSelectionNum <= 0)
			return;

		m_menuDatas[m_nowMenuSelectionNum].m_isTextSelectionDraw
			= false;

		m_nowMenuSelectionNum--;
	}
	//メニュー選択で下を選択する処理
	else if(g_pad[0]->IsTrigger(enButtonDown))
	{
		if (m_maxMenuNum <= m_nowMenuSelectionNum)
			return;

		m_menuDatas[m_nowMenuSelectionNum].m_isTextSelectionDraw
			= false;

		m_nowMenuSelectionNum++;
	}
	else if(g_pad[0]->IsTrigger(enButtonB))
	{
		//起動するものを確定
		m_confirmedMenuSelectionNum = m_nowMenuSelectionNum;

		m_isFuncBoot = true;

		m_gameWindow->WindowClose();
		
		StateChange(GameMenuState::en_windowClose);
	}
	else if(g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_isInitCloseFunc == true)
			m_isFuncBoot = true;

		m_gameWindow->WindowClose();

		StateChange(GameMenuState::en_windowClose);

	}

	//マウスカーソルのアップデート
	MouseCursorSpriteUpdate();
	//選択文字表示更新
	TextSelectionUpdate();
}

void GameMenu::MouseCursorSpriteUpdate()
{
	Vector3 mouseCurSorPos;

	//補正値計算
	mouseCurSorPos.x = m_menuDatas[m_nowMenuSelectionNum].m_textPos.x + 20.0f;

	mouseCurSorPos.y = m_menuDatas[m_nowMenuSelectionNum].m_textPos.y 
		+ -80.0f + (m_nowMenuSelectionNum * 15.0f);

	m_mouseCursor.SetPosition(mouseCurSorPos);
}

void GameMenu::TextSelectionUpdate()
{
	if (Delay(GameMenuNS_CPP::TIME_TEXT_SELECTION_DELAY))
	{
		//反転
		m_menuDatas[m_nowMenuSelectionNum].m_isTextSelectionDraw
			= !m_menuDatas[m_nowMenuSelectionNum].m_isTextSelectionDraw;
	}
}

void GameMenu::InitMenuDetasList()
{
	for (int listNo = 0;
		listNo < GameMenuNS_H::MAX_TEXTDATALIST_EXP;
		listNo++)
	{

		m_menuDatas[listNo].m_fontRender.SetText(L"");

		std::memset(m_menuDatas[listNo].m_displayTextList,
			0,
			sizeof(m_menuDatas[listNo].m_displayTextList));

		m_menuDatas[listNo].m_isTextSelectionDraw = false;

		m_nowTextNum = 0;

		m_listEndNum = 0;

		m_listNowNum = 0;
		//メニュー選択番号
		m_nowMenuSelectionNum = 0;
		//メニュー決定番号
		m_confirmedMenuSelectionNum = -1;
	}

	m_isMouseCorsorDraw = false;
}

void GameMenu::Render(RenderContext& rc)
{
	if (m_gameMenuState != GameMenuState::en_textDraw &&
		m_gameMenuState != GameMenuState::en_menuSelection)
	{
		return;
	}

	for (int listNo = 0;
		listNo < GameMenuNS_H::MAX_TEXTDATALIST_EXP;
		listNo++)
	{
		if (m_menuDatas[listNo].m_isTextSelectionDraw == true)
			continue;

		m_menuDatas[listNo].m_fontRender.Draw(rc);
	}

	if (m_isMouseCorsorDraw == true)
	{
		m_mouseCursor.Draw(rc);
	}
}
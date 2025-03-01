#include "stdafx.h"
#include "GameMenu.h"
#include "GameWindow.h"
#include "GameSound.h"

//�萔��
namespace {
	/// <summary>
	/// �t�H���g�̃J���[
	/// </summary>
	static const Vector4 FONT_COLOR = { 0.3f,0.3f,1.0f,1.0f };
	static const Vector4 MAINTEXT_COLOR = { 1.0f,1.0f,1.0f,1.0f };
	static const float TIME_TEXT_DELAY = 0.02f;
	static const float TIME_TEXT_SELECTION_DELAY = 1.0f;
	static const wchar_t TEXT_UNDER_BAR[2] = { L"_" };

	static const float MOUSECORSOR_SPRITE_W_SIZE = 34.0f;
	static const float MOUSECORSOR_SPRITE_H_SIZE = 38.0f;
}

bool GameMenu::Start()
{
	m_gameWindow = NewGO<GameWindow>(1,"menuGameWindow");

	m_gameSound = FindGO<GameSound>("gameSound");

	m_mouseCursor.Init("Assets/modelData/window/mouse_cursor.DDS",
		MOUSECORSOR_SPRITE_W_SIZE,
		MOUSECORSOR_SPRITE_H_SIZE
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
		listNo < MAX_TEXTDATALIST_EXP;
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

	MenuStateUpdate();

	DisplayTextUpdate();

	m_mouseCursor.Update();
}

void GameMenu::MenuStateUpdate()
{

	switch (m_gameMenuState)
	{
	case GameMenu::en_standby:

		//�ҋ@

		break;
	case GameMenu::en_windowOpen:

		//�E�B���h�E�J���܂őҋ@
		if (m_gameWindow->IsWindowOpen())
		{
			//�J������X�e�[�g��ύX
			StateChange(GameMenuState::en_textDraw);
		}

		break;
	case GameMenu::en_textDraw:

		TextDrawUpdate();

		break;
	case GameMenu::en_menuSelection:

		MenuSelectionUpdate();

		break;
	default:
		break;
	}

}

void GameMenu::TextDrawUpdate()
{
	//��������
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		for (int listNo = m_listNowNum;
			listNo < MAX_TEXTDATALIST_EXP - 1;
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

	//�������X�g�X�V
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

	//�\�������X�V
	if (Delay(TIME_TEXT_DELAY))
	{
		DisplayTextListUpdate();
	}
}

//�x���֐�
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
	m_menuDatas[m_listNowNum].m_fontRender.SetColor(MAINTEXT_COLOR);

	m_menuDatas[m_listNowNum].m_fontRender.SetPivot({ 0.5f,0.5f });

	m_menuDatas[m_listNowNum].m_fontRender
		.SetPosition(m_menuDatas[m_listNowNum].m_textPos);

	m_menuDatas[m_listNowNum].m_fontRender.
		SetText(m_menuDatas[m_listNowNum].m_displayTextList);
}


//�\�������z��X�V�֐�
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
		TEXT_UNDER_BAR, 1);

}

void GameMenu::MenuSelectionUpdate()
{
	//���j���[�I���ŏ��I�����鏈��
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		if (m_nowMenuSelectionNum <= 0)
			return;

		m_menuDatas[m_nowMenuSelectionNum].m_isTextSelectionDraw
			= false;

		m_nowMenuSelectionNum--;
	}
	//���j���[�I���ŉ���I�����鏈��
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
		//�N��������̂��m��
		m_confirmedMenuSelectionNum = m_nowMenuSelectionNum;
		
		StateChange(GameMenuState::en_windowClose);
	}

	//�}�E�X�J�[�\���̃A�b�v�f�[�g
	MouseCursorSpriteUpdate();
	//�I�𕶎��\���X�V
	TextSelectionUpdate();
}

void GameMenu::MouseCursorSpriteUpdate()
{
	Vector3 mouseCurSorPos;

	//�␳�l�v�Z
	mouseCurSorPos.x = m_menuDatas[m_nowMenuSelectionNum].m_textPos.x + 20.0f;

	mouseCurSorPos.y = m_menuDatas[m_nowMenuSelectionNum].m_textPos.y 
		+ -80.0f + (m_nowMenuSelectionNum * 15.0f);

	m_mouseCursor.SetPosition(mouseCurSorPos);
}

void GameMenu::TextSelectionUpdate()
{
	if (Delay(TIME_TEXT_SELECTION_DELAY))
	{
		//���]
		m_menuDatas[m_nowMenuSelectionNum].m_isTextSelectionDraw
			= !m_menuDatas[m_nowMenuSelectionNum].m_isTextSelectionDraw;
	}
}

void GameMenu::Render(RenderContext& rc)
{
	for (int listNo = 0;
		listNo < MAX_TEXTDATALIST_EXP;
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
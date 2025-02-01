#include "stdafx.h"
#include "GameInformation.h"
#include "GameWindow.h"

//�萔��
namespace {
	/// <summary>
	/// �t�H���g�̃J���[
	/// </summary>
	static const Vector4 FONT_COLOR = { 0.3f,0.3f,1.0f,1.0f };
	static const Vector4 FONT_COLOR_TEST = { 1.0f,1.0f,1.0f,1.0f };
	static const float TIME_N = 0.2f;

}

//�X�^�[�g�֐�
bool GameInformation::Start()
{
	m_gameWindow = NewGO<GameWindow>(1, "gameWindow");

	return true;
}

//�A�b�v�f�[�g�֐�
void GameInformation::Update()
{

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		InitAndGoInformation(L"testAndtestAndtest");
	}

	InformationStateUpdate();

	DisplayTextUpdate();

}

void GameInformation::InformationStateUpdate()
{
	switch (m_gameInformationState)
	{
	case GameInformation::en_standby:

		//�ҋ@

		break;
	case GameInformation::en_windowOpen:

		//�E�B���h�E�J���܂őҋ@
		if (m_gameWindow->IsWindowOpen())
		{
			//�J������X�e�[�g��ύX
			StateChange(GameInformationState::en_textDraw);
		}

		break;
	case GameInformation::en_textDraw:

		if (m_externalInputTextList[m_nowTextNum] == L'\0')
		{
			StateChange(GameInformationState::en_openWait);
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
			StateChange(GameInformationState::en_standby);
		}

		break;
	default:
		break;
	}
}

//�x���֐�
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
	m_mainFontRender.SetColor(FONT_COLOR_TEST);

	m_mainFontRender.SetPivot({ 0.5f,0.5f });

	//m_mainFontRender.SetPosition();

	m_mainFontRender.SetText(m_displayTextList);
}

//�\�������z��X�V�֐�
void GameInformation::DisplayTextListUpdate()
{

	m_nowTextNum++;

	wcsncpy_s(m_displayTextList,
		_countof(m_displayTextList),
		m_externalInputTextList,
		m_nowTextNum
	);

}

//�����_�[�֐�
void GameInformation::Render(RenderContext& rc)
{
	if (m_gameInformationState != GameInformationState::en_textDraw &&
		m_gameInformationState != GameInformationState::en_openWait)
	{
		return;
	}

	m_mainFontRender.Draw(rc);
}
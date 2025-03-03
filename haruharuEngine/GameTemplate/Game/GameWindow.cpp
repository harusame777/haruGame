#include "stdafx.h"
#include "GameWindow.h"
#include "GameSound.h"

//�萔��
namespace WindowConstants_CPP {

	static const float WINDOWTOP_SPRITE_W_SIZE = 1508.0f;
	static const float WINDOWTOP_SPRITE_H_SIZE = 50.0f;

	static const float WINDOWBOTTOM_SPRITE_W_SIZE = 1500.0f;
	static const float WINDOWBOTTOM_SPRITE_H_SIZE = 55.0f;

	static const float WINDOWBASE_SPRITE_W_SIZE = 1500.0f;
	static const float WINDOWBASE_SPRITE_H_SIZE = 810.0f;


	static const float WINDOWBASE_WIPE_MAX = 0.0f;
	static const float WINDOWBASE_WIPE_MIN = 450.0f;

}

void GameWindow::WindowOpen()
{
	if (m_windowState != WindowState::en_state_standby)
	{
		return;
	}

	m_windowTopPos = Vector3::Zero;

	m_windowBottomPos = Vector3::Zero;

	m_windowDatas.SetWipeRatio(0.0);

	m_windowState = WindowState::en_state_windowOpen;

	m_windowFrameEasingMax = WindowConstants_H::WINDOWTOP_OPEN_POSITION.y;

	m_windowFrameEasingMin = WindowConstants_H::WINDOWTOP_CLOSE_POSITION.y;

	m_windowFrameRatio = 0.0f;

	m_isWindowCloseCompletion = false;

	m_isWindowDraw = true;

	m_gameSound->LocalSoundOrder(GameSound::en_syuwin, false, 0.5f);
}

void GameWindow::WindowClose()
{
	if (m_windowState != WindowState::en_state_openWait)
	{
		return;
	}

	m_windowState = WindowState::en_state_windowClose;

	m_windowFrameEasingMax = WindowConstants_H::WINDOWTOP_CLOSE_POSITION.y;

	m_windowFrameEasingMin = WindowConstants_H::WINDOWTOP_OPEN_POSITION.y;

	m_windowFrameRatio = 0.0f;

	m_gameSound->LocalSoundOrder(GameSound::en_syuwin, false, 0.5f);
}

//�X�^�[�g�֐�
bool GameWindow::Start()
{
	//�E�B���h�E�̃t���[����
	m_window_top.Init("Assets/modelData/window/window_sprite_top_1.DDS",
		WindowConstants_CPP::WINDOWTOP_SPRITE_W_SIZE,
		WindowConstants_CPP::WINDOWTOP_SPRITE_H_SIZE);

	m_window_top.SetPosition(WindowConstants_H::WINDOWTOP_CLOSE_POSITION);

	//�E�B���h�E�̃t���[����
	m_window_bottom.Init("Assets/modelData/window/window_sprite_bottom_1.DDS",
		WindowConstants_CPP::WINDOWBOTTOM_SPRITE_W_SIZE,
		WindowConstants_CPP::WINDOWBOTTOM_SPRITE_H_SIZE);

	m_window_bottom.SetPosition(WindowConstants_H::WINDOWBOTTOM_CLOSE_POSITION);

	SpriteInitData windowBaseInitData;

	//�摜��ݒ�
	windowBaseInitData.m_ddsFilePath[0] = "Assets/modelData/window/window_sprite_base_1.DDS";
	//�V�F�[�_�[�t�@�C����ݒ�
	windowBaseInitData.m_fxFilePath = "Assets/shader/haruharuWindowSpriteShader.fx";
	//���[�U�[�g���f�[�^��ݒ�
	windowBaseInitData.m_expandConstantBuffer = &m_windowDatas;
	windowBaseInitData.m_expandConstantBufferSize = sizeof(m_windowDatas);
	windowBaseInitData.m_expandConstantBuffer = &m_windowDatas;
	windowBaseInitData.m_expandConstantBufferSize = sizeof(m_windowDatas);
	//�䗦��ݒ�
	windowBaseInitData.m_width = static_cast<UINT>(WindowConstants_CPP::WINDOWBASE_SPRITE_W_SIZE);
	windowBaseInitData.m_height = static_cast<UINT>(WindowConstants_CPP::WINDOWBASE_SPRITE_H_SIZE);
	//�u�����h���[�h��ݒ�
	windowBaseInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//�ݒ肵���f�[�^���X�v���C�g�ɐݒ�
	m_window_base.Init(windowBaseInitData);
	
	m_windowTopPos = Vector3::Zero;

	m_windowBottomPos = Vector3::Zero;

	m_windowDatas.SetWipeRatio(0.0);

	m_gameSound = FindGO<GameSound>("gameSound");

	return true;
}

//�A�b�v�f�[�g�֐�
void GameWindow::Update()
{
	//if (g_pad[0]->IsTrigger(enButtonA))
	//{
	//	WindowOpen();
	//}

	WindowStateUpdate();
	
	m_window_base.Update();

	m_window_bottom.Update();

	m_window_top.Update();
}

//�E�B���h�E�̃X�e�[�g���X�V����֐�
void GameWindow::WindowStateUpdate()
{
	switch (m_windowState)
	{
	case GameWindow::en_state_standby:

		m_isWindowCloseCompletion = false;

		break;
	case GameWindow::en_state_windowOpen:

		m_windowTopPos.y = WindowFrameUpdate();

		m_window_top.SetPosition(m_windowTopPos);

		m_windowBottomPos.y = m_windowTopPos.y * -1.0f;

		m_window_bottom.SetPosition(m_windowBottomPos);

		m_windowDatas.SetWipeRatio(WindowBaseWipeCalc());

		break;
	case GameWindow::en_state_openWait:

		//�ҋ@

		//if (g_pad[0]->IsTrigger(enButtonB))
		//{
		//	WindowClose();
		//}

		break;
	case GameWindow::en_state_windowClose:

		m_windowTopPos.y = WindowFrameUpdate();

		m_window_top.SetPosition(m_windowTopPos);

		m_windowBottomPos.y = m_windowTopPos.y * -1.0f;

		m_window_bottom.SetPosition(m_windowBottomPos);

		m_windowDatas.SetWipeRatio(WindowBaseWipeCalc());

		break;
	case GameWindow::en_state_windowCloseCompletion:

		m_isWindowCloseCompletion = true;

		m_isWindowDraw = false;

		m_windowState = WindowState::en_state_standby;

		break;
	default:
		break;
	}

}

//�E�B���h�E�̃t���[���̈ʒu���X�V����֐�
float GameWindow::WindowFrameUpdate()
{
	m_windowFrameRatio += g_gameTime->GetFrameDeltaTime() * 2.0f;

	if (m_windowFrameRatio > 1.0f)
	{
		m_windowFrameRatio = 1.0f;

		if (m_windowState == WindowState::en_state_windowOpen)
		{
			m_windowState = WindowState::en_state_openWait;
		}
		else if(m_windowState == WindowState::en_state_windowClose)
		{
			m_windowState = WindowState::en_state_windowCloseCompletion;
		}
	}

	return Leap(m_windowFrameEasingMin,
		m_windowFrameEasingMax,
		m_windowFrameRatio);
}

//�E�B���h�E�̃x�[�X�̃��C�v�������v�Z����֐�
float GameWindow::WindowBaseWipeCalc()
{
	float finalIndex = 0.0f;

	//������Ək�߂�������y�l�����������Z����
	float windowTopIndex = m_window_top.GetPosition().y - 30.0f;

	//�E�B���h�E�̃t���[���̈ʒu���l�����Čv�Z����
	finalIndex = WindowConstants_CPP::WINDOWBASE_WIPE_MIN
		+ (windowTopIndex / WindowConstants_H::WINDOWTOP_OPEN_POSITION.y)
		* (WindowConstants_CPP::WINDOWBASE_WIPE_MAX - WindowConstants_CPP::WINDOWBASE_WIPE_MIN);

	return finalIndex;
}

//�����_�[�֐�
void GameWindow::Render(RenderContext& rc)
{

	if (m_isWindowDraw == true)
	{
		m_window_base.Draw(rc);

		m_window_bottom.Draw(rc);

		m_window_top.Draw(rc);

	}

	//wchar_t wcsbuf[256] = {};

	//swprintf_s(wcsbuf, 256, L"state: %d,FrameRatio: %.2f, topPosY: %.2f", int(m_windowState), m_windowFrameRatio, m_windowTopPos.y);

	//m_debugFontRender_A.SetText(wcsbuf);

	//m_debugFontRender_A.SetPosition({ -900.0f,-200.0f,0.0f });

	//m_debugFontRender_A.Draw(rc);

	//swprintf_s(wcsbuf, 256, L"WindowRatio: %.2f, BottomPosY: %.2f",m_windowDatas.GetWipeRatio(), m_windowBottomPos.y);

	//m_debugFontRender_B.SetText(wcsbuf);

	//m_debugFontRender_B.SetPosition({ -900.0f,-300.0f,0.0f });

	//m_debugFontRender_B.Draw(rc);

	//m_debugFontRender_C.SetText(m_debugFontValue_C);

	//m_debugFontRender_C.SetPosition({ -900.0f,-400.0f,0.0f });

	//m_debugFontRender_C.Draw(rc);

}


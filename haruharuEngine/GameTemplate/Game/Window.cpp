#include "stdafx.h"
#include "Window.h"

//これを有効にするとデバッグモードになる
//#define DEBUG_MODE

//定数等
namespace {

	static const float WINDOWTOP_SPRITE_W_SIZE = 1508.0f;
	static const float WINDOWTOP_SPRITE_H_SIZE = 50.0f;

	static const float WINDOWBOTTOM_SPRITE_W_SIZE = 1508.0f;
	static const float WINDOWBOTTOM_SPRITE_H_SIZE = 55.0f;

	static const float WINDOWBASE_SPRITE_W_SIZE = 1503.0f;
	static const float WINDOWBASE_SPRITE_H_SIZE = 810.0f;


	static const float WINDOWBASE_WIPE_MAX = 0.0f;
	static const float WINDOWBASE_WIPE_MIN = 450.0f;

}

//スタート関数
bool Window::Start()
{
	//ウィンドウのフレーム上
	m_window_top.Init("Assets/modelData/window/window_sprite_top_1.DDS",
		WINDOWTOP_SPRITE_W_SIZE,
		WINDOWTOP_SPRITE_H_SIZE);

	m_window_top.SetPosition(WINDOWTOP_CLOSE_POSITION);

	//ウィンドウのフレーム下
	m_window_bottom.Init("Assets/modelData/window/window_sprite_bottom_1.DDS",
		WINDOWBOTTOM_SPRITE_W_SIZE,
		WINDOWBOTTOM_SPRITE_H_SIZE);

	m_window_bottom.SetPosition(WINDOWBOTTOM_CLOSE_POSITION);

	//m_window_base.Init("Assets/modelData/window/window_sprite_base_1.DDS",
	//	WINDOWBASE_SPRITE_W_SIZE,
	//	WINDOWBASE_SPRITE_H_SIZE);

	SpriteInitData windowBaseInitData;

	//画像を設定
	windowBaseInitData.m_ddsFilePath[0] = "Assets/modelData/window/window_sprite_base_1.DDS";
	//シェーダーファイルを設定
	windowBaseInitData.m_fxFilePath = "Assets/shader/haruharuWindowSpriteShader.fx";
	//ユーザー拡張データを設定
	windowBaseInitData.m_expandConstantBuffer = &m_windowDatas;
	windowBaseInitData.m_expandConstantBufferSize = sizeof(m_windowDatas);
	//比率を設定
	windowBaseInitData.m_width = static_cast<UINT>(WINDOWBASE_SPRITE_W_SIZE);
	windowBaseInitData.m_height = static_cast<UINT>(WINDOWBASE_SPRITE_H_SIZE);
	//ブレンドモードを設定
	windowBaseInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//設定したデータをスプライトに設定
	m_window_base.Init(windowBaseInitData);


	return true;
}

//アップデート関数
void Window::Update()
{
#ifdef DEBUG_MODE
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		WindowOpen();
	}

	if (IsWindowClose())
	{
		float test1;

		test1 = 1;
	}

	if (IsWindowOpen())
	{
		float test2;

		test2 = 2;
	}

#endif

	WindowStateUpdate();
	
	m_window_base.Update();

	m_window_bottom.Update();

	m_window_top.Update();
}

//ウィンドウのステートを更新する関数
void Window::WindowStateUpdate()
{
	Vector3 windowTopNewPos = { 0.0f,0.0f,0.0f };
	Vector3 windowBottomNewPos = { 0.0f,0.0f,0.0f };

	switch (m_windowState)
	{
	case Window::en_state_standby:

		m_isWindowCloseCompletion = false;

		break;
	case Window::en_state_windowOpen:


		windowTopNewPos.y = WindowFrameUpdate();

		m_window_top.SetPosition(windowTopNewPos);

		windowBottomNewPos.y = windowTopNewPos.y * -1.0f;

		m_window_bottom.SetPosition(windowBottomNewPos);

		m_windowDatas.SetWipeRatio(WindowBaseWipeCalc());

		break;
	case Window::en_state_openWait:

		if (g_pad[0]->IsTrigger(enButtonB))
		{
			WindowClose();
		}

		break;
	case Window::en_state_windowClose:

		windowTopNewPos.y = WindowFrameUpdate();

		m_window_top.SetPosition(windowTopNewPos);

		windowBottomNewPos.y = windowTopNewPos.y * -1.0f;

		m_window_bottom.SetPosition(windowBottomNewPos);

		m_windowDatas.SetWipeRatio(WindowBaseWipeCalc());

		break;
	case Window::en_state_windowCloseCompletion:

		m_isWindowCloseCompletion = true;

		m_isWindowDraw = false;

		m_windowState = WindowState::en_state_standby;

		break;
	default:
		break;
	}

}

//ウィンドウのフレームの位置を更新する関数
const float& Window::WindowFrameUpdate()
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

//ウィンドウのベースのワイプ割合を計算する関数
const float& Window::WindowBaseWipeCalc()
{
	float finalIndex;

	//ちょっと縮めたいからy値を少し引き算する
	float windowTopIndex = m_window_top.GetPosition().y - 10.0f;

	//ウィンドウのフレームの位置を考慮して計算する
	finalIndex = WINDOWBASE_WIPE_MIN 
		+ (windowTopIndex / WINDOWTOP_OPEN_POSITION.y) 
		* (WINDOWBASE_WIPE_MAX - WINDOWBASE_WIPE_MIN);

	return finalIndex;
}

//レンダー関数
void Window::Render(RenderContext& rc)
{
	if (m_isWindowDraw == false)
	{
		return;
	}

	m_window_base.Draw(rc);

	m_window_bottom.Draw(rc);

	m_window_top.Draw(rc);
}


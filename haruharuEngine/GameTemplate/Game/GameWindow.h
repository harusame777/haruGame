#pragma once

//定数等
namespace WindowConstants_H {
	static const Vector3 WINDOWTOP_OPEN_POSITION = { 0.0f,400.0f,0.0f };
	static const Vector3 WINDOWTOP_CLOSE_POSITION = { 0.0f,20.0f,0.0f };
	static const Vector3 WINDOWBOTTOM_OPEN_POSITION = { 0.0f,-400.0f,0.0f };
	static const Vector3 WINDOWBOTTOM_CLOSE_POSITION = { 0.0f,-20.0f,0.0f };
}

class GameWindow : public IGameObject
{
private:
	/// <summary>
	/// ウィンドウステート
	/// </summary>
	enum WindowState {
		//待機
		en_state_standby = 0,
		//ウィンドウ開ける
		en_state_windowOpen = 1,
		//開いた状態で待機
		en_state_openWait = 2,
		//ウィンドウ閉める
		en_state_windowClose = 3,
		//ウィンドウ閉じる処理完了
		en_state_windowCloseCompletion = 4,
		
	};
	WindowState m_windowState = WindowState::en_state_standby;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameWindow(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameWindow(){}
	/// <summary>
	/// ウィンドウオープン
	/// </summary>
	void WindowOpen()
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
	}
	/// <summary>
	/// ウィンドウクローズ
	/// </summary>
	void WindowClose()
	{
		if (m_windowState != WindowState::en_state_openWait)
		{
			return;
		}

		m_windowState = WindowState::en_state_windowClose;

		m_windowFrameEasingMax = WindowConstants_H::WINDOWTOP_CLOSE_POSITION.y;

		m_windowFrameEasingMin = WindowConstants_H::WINDOWTOP_OPEN_POSITION.y;

		m_windowFrameRatio = 0.0f;
	}

	bool IsWindowOpen()const 
	{
		if (m_windowState != WindowState::en_state_openWait)
		{
			return false;
		}

		return true;
	}

	bool IsWindowClose()const 
	{
		return m_isWindowCloseCompletion;
	}
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ウィンドウのステート更新関数
	/// </summary>
	void WindowStateUpdate();
	/// <summary>
	/// ウィンドウ枠更新
	/// </summary>
	float WindowFrameUpdate();
	/// <summary>
	/// ウィンドウベースのワイプ計算関数
	/// </summary>
	float WindowBaseWipeCalc();
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ウィンドウのデータ
	/// </summary>
	struct WindowDatas
	{
	private:
		/// <summary>
		/// ワイプ割合
		/// </summary>
		float m_wipeRatio = 0.0f;
	public:
		/// <summary>
		/// ワイプ割合設定
		/// </summary>
		/// <param name="value"></param>
		void SetWipeRatio(const float value)
		{
			m_wipeRatio = value;
		}
		/// <summary>
		/// ワイプ割合取得
		/// </summary>
		/// <returns></returns>
		float GetWipeRatio() const
		{
			return m_wipeRatio;
		}
	};

	WindowDatas m_windowDatas;
	/// <summary>
	/// ウィンドウを描画するかどうか
	/// </summary>
	bool m_isWindowDraw = false;
	/// <summary>
	/// ウィンドウが閉じきったかどうか
	/// </summary>
	bool m_isWindowCloseCompletion = false;
	/// <summary>
	/// ウィンドウ上部
	/// </summary>
	SpriteRender m_window_top;
	/// <summary>
	/// ウィンドウ下部
	/// </summary>
	SpriteRender m_window_bottom;
	/// <summary>
	/// ウィンドウ上部座標
	/// </summary>
	Vector3 m_windowTopPos = Vector3::Zero;
	/// <summary>
	/// ウィンドウ下部座標
	/// </summary>
	Vector3 m_windowBottomPos = Vector3::Zero;
	/// <summary>
	/// ウィンドウのフレームのイージングに使用する変数
	/// </summary>
	float m_windowFrameRatio = 0.0f;
	float m_windowFrameEasingMax = 0.0f;
	float m_windowFrameEasingMin = 0.0f;
	/// <summary>
	/// ウィンドウベース
	/// </summary>
	SpriteRender m_window_base;
	/// <summary>	
	/// flaot用線形補間
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float& Leap(const float& a, const float& b, const float& t)
	{
		float finalValue = (1.0f - t) * a + t * b;

		return finalValue;
	}
	/// <summary>
	/// デバック用のフォントレンダー
	/// </summary>
	FontRender m_debugFontRender_A;
	/// <summary>
	/// デバック用のフォントレンダー
	/// </summary>
	FontRender m_debugFontRender_B;
	/// <summary>
	/// デバック用のフォントレンダー
	/// </summary>
	FontRender m_debugFontRender_C;
	wchar_t m_debugFontValue_C[256] = {};
};


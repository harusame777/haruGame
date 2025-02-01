#pragma once
#include "GameWindow.h"

class GameWindow;

class GameInformation : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameInformation(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameInformation(){}
	/// <summary>
	/// 起動関数
	/// </summary>
	/// <param name="text"></param>
	void InitAndGoInformation(const wchar_t* text)
	{
		if (m_gameInformationState != GameInformationState::en_standby)
		{
			return;
		}
		//ウィンドウを開ける
		m_gameWindow->WindowOpen();
		//文字列textをm_externalInputFontListにコピー
		swprintf_s(m_externalInputTextList, text);
		//ステートをwindowOpenに変更
		StateChange(GameInformationState::en_windowOpen);
	}

private:
	/// <summary>
	/// 一段落の文字配列のデータ
	/// </summary>
	struct TextOneParagraphData
	{

	};

	/// <summary>
	/// インフォメーションステート
	/// </summary>
	enum GameInformationState
	{
		//待機
		en_standby,
		//ウィンドウオープン
		en_windowOpen,
		//文字表示
		en_textDraw,
		//開いた状態で待機
		en_openWait,
		//ウィンドウクローズ
		en_windowClose,
	};
	/// <summary>
	/// インフォメーションステート変数
	/// </summary>
	GameInformationState m_gameInformationState = GameInformationState::en_standby;
	/// <summary>
	/// ステート変更
	/// </summary>
	/// <param name="changeState"></param>
	void StateChange(const GameInformationState changeState)
	{
		m_gameInformationState = changeState;
	}
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
	/// インフォメーションステートアップデート
	/// </summary>
	void InformationStateUpdate();
	/// <summary>
	/// 遅延関数
	/// </summary>
	/// <returns></returns>
	bool Delay(const float delayTime);
	/// <summary>
	/// 表示文字更新
	/// </summary>
	void DisplayTextUpdate();
	/// <summary>
	/// 表示文字配列更新
	/// </summary>
	void DisplayTextListUpdate();
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ウィンドウのインスタンス
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
	/// <summary>
	/// フォントレンダー
	/// </summary>
	FontRender m_mainFontRender;
	/// <summary>
	/// 外部入力文字配列
	/// </summary>
	wchar_t m_externalInputTextList[256] = {};
	/// <summary>
	/// メインフォントの配列
	/// </summary>
	wchar_t m_displayTextList[256] = {};
	/// <summary>
	/// 現在の文字表示数
	/// </summary>
	int m_nowTextNum = 0;
	/// <summary>
	/// 文字表示遅延
	/// </summary>
	float m_textDelayTime = 0.0f;
};


#pragma once
#include "GameWindow.h"

class GameWindow;
class GameSound;

//定数等
namespace {

	static const int MAX_TEXTDATALIST_EXP = 8;

	static const int MAX_TEXT_SIZE = 256;

	static const Vector3 TEXT_FIXED_POS = { -850.0f,400.0f,0.0f };

}

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
	///	テキストをインフォメーションに設定
	/// </summary>
	/// <param name="text"></param>
	void InitTextData(const wchar_t* text)
	{
		if (m_gameInformationState != GameInformationState::en_standby)
		{
			return;
		}

		for (int listNo = 0;
			listNo < MAX_TEXTDATALIST_EXP;
			listNo++)
		{

			if (m_textDataList[listNo].m_isUse == false)
			{
				m_textDataList[listNo].m_isUse = true;

				m_textDataList[listNo].m_textPos = TEXT_FIXED_POS;

				m_textDataList[listNo].m_textPos.y -= 100 * listNo;

				//文字列textをm_externalInputFontListにコピー
				swprintf_s(m_textDataList[listNo].m_externalInputTextList, text);

				break;
			}

		}
	}
	/// <summary>
	/// 起動関数
	/// </summary>
	/// <param name="text"></param>
	void GoInformation();
	/// <summary>
	/// インフォメーションが起動中かどうか
	/// </summary>
	/// <returns></returns>
	bool IsInformationNow()const 
	{
		if (m_gameInformationState != GameInformationState::en_standby)
		{
			return true;
		}

		return false;
	}
	/// <summary>
	/// インフォメーションが閉まりだした時にtrue
	/// </summary>
	/// <returns></returns>
	bool IsInformationCloseing()const
	{
		return m_isInformationCloseing;
	}
private:
	/// <summary>
	/// 一段落の文字配列のデータ
	/// </summary>
	struct TextOneParagraphData
	{
	public:
		/// <summary>
		/// フォントレンダー
		/// </summary>
		FontRender m_mainFontRender;
		/// <summary>
		/// 外部入力文字配列
		/// </summary>
		wchar_t m_externalInputTextList[MAX_TEXT_SIZE] = {};
		/// <summary>
		/// メインフォントの配列
		/// </summary>
		wchar_t m_displayTextList[MAX_TEXT_SIZE] = {};
		/// <summary>
		/// このコンテナを使用中かどうか
		/// </summary>
		bool m_isUse = false;
		/// <summary>
		/// この段落のテキストを出力し終わったか
		/// </summary>
		bool m_isOneParagrapgTextEnd = false;
		/// <summary>
		/// テキストの位置
		/// </summary>
		Vector3 m_textPos = Vector3::Zero;
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
		//終了処理
		en_end
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
	/// 現在の文字表示数
	/// </summary>
	int m_nowTextNum = 0;
	/// <summary>
	/// 文字表示遅延
	/// </summary>
	float m_textDelayTime = 0.0f;
	/// <summary>
	/// テキストデータの配列
	/// </summary>
	TextOneParagraphData m_textDataList[MAX_TEXTDATALIST_EXP];
	/// <summary>
	/// textDataListの設定されていない要素番号
	/// </summary>
	int m_listEndNum = 0;
	/// <summary>
	/// 現在のtextDataListの要素番号
	/// </summary>
	int m_listNowNum = 0;
	/// <summary>
	/// インフォメーションが閉まりだしたか
	/// </summary>
	bool m_isInformationCloseing = false;
	/// <summary>
	/// 閉じるテキスト
	/// </summary>
	FontRender m_closeButtonText;
	/// <summary>
	/// 閉じるテキストを描画するフラグ
	/// </summary>
	bool m_closeButtonTextDrawFlag = false;
	/// <summary>
	/// ウィンドウのインスタンス
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
	/// <summary>
	/// ゲームサウンドのインスタンス
	/// </summary>
	GameSound* m_gameSound = nullptr;
};


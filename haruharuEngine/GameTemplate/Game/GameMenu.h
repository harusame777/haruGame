#pragma once

class GameWindow;
class GameSound;

//定数等
namespace {

	static const int MAX_TEXTDATALIST_EXP = 8;

	static const int MAX_TEXT_SIZE = 256;

	static const Vector3 TEXT_FIXED_POS = { -200.0f,400.0f,0.0f };

}

class GameMenu : public IGameObject
{
public:

	enum GameMenuState
	{
		//待機
		en_standby,
		//ウィンドウを開く
		en_windowOpen,
		//文字表示
		en_textDraw,
		//メニュー選択
		en_menuSelection,
		//ウィンドウクローズ
		en_windowClose,
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameMenu() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameMenu() {};
	/// <summary>
	/// 命名定義、関数入れ物
	/// </summary>
	using MenuFunction = std::function<bool()>;
	/// <summary>
	/// メニュー作成
	/// </summary>
	/// <param name="func"></param>
	void InitMenuDatas(
		const wchar_t* menuName,
		const wchar_t* menuText,
		const MenuFunction& menuFunc
	)
	{

		for (int listNo = 0;
			listNo < MAX_TEXTDATALIST_EXP;
			listNo++)
		{

			if (m_menuDatas[listNo].m_isUse == false)
			{
				m_menuDatas[listNo].m_isUse = true;

				m_menuDatas[listNo].m_textPos = TEXT_FIXED_POS;

				m_menuDatas[listNo].m_textPos.y -= 100 * listNo;

				//文字列textをm_externalInputFontListにコピー
				swprintf_s(m_menuDatas[listNo].m_externalInputTextList, menuText);

				//メニューの名前を設定
				swprintf_s(m_menuDatas[listNo].m_menuName, menuName);

				//関数を設定
				m_menuDatas->SetMenuFunction(menuFunc);

				//メニューの最大数を記録
				m_maxMenuNum++;

				break;
			}

		}
	}
	/// <summary>
	/// メニューを開いて起動する
	/// </summary>
	void GoMenuOpen();
	/// <summary>
	/// ステート変更
	/// </summary>
	/// <param name="changeState"></param>
	void StateChange(const GameMenuState changeState)
	{
		m_gameMenuState = changeState;
	}
private:
	/// <summary>
	/// ゲームメニューのステート
	/// </summary>
	GameMenuState m_gameMenuState = GameMenuState::en_standby;
	/// <summary>
	/// メニューのデータの構造体
	/// </summary>
	struct MenuDatas
	{
	public:
		/// <summary>
		/// フォントレンダー
		/// </summary>
		FontRender m_fontRender;
		/// <summary>
		/// メニュー実行関数入れ物
		/// </summary>
		MenuFunction m_menuFunction;
		/// <summary>
		/// メニュー識別子
		/// </summary>
		wchar_t m_menuName[MAX_TEXT_SIZE] = {};
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
		/// <summary>
		/// セレクト時に表示するかしないか
		/// </summary>
		bool m_isTextSelectionDraw = false;
	public:
		/// <summary>
		/// 関数をセット
		/// </summary>
		/// <param name="func"></param>
		void SetMenuFunction(const MenuFunction& func)
		{
			m_menuFunction = func;
		}
	};
	/// <summary>
	/// 構造体変数
	/// </summary>
	MenuDatas m_menuDatas[MAX_TEXTDATALIST_EXP];
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
	/// 文字描画更新
	/// </summary>
	void TextDrawUpdate();
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
	/// 現在の文字表示数
	/// </summary>
	int m_nowTextNum = 0;
	/// <summary>
	/// 文字表示遅延
	/// </summary>
	float m_textDelayTime = 0.0f;
	/// <summary>
	/// textDataListの設定されていない要素番号
	/// </summary>
	int m_listEndNum = 0;
	/// <summary>
	/// 現在のtextDataListの要素番号
	/// </summary>
	int m_listNowNum = 0;
	/// <summary>
	/// メニューセレクトアップデート
	/// </summary>
	void MenuSelectionUpdate();
	/// <summary>
	/// 文字選択時の更新
	/// </summary>
	void TextSelectionUpdate();
	/// <summary>
	/// ステート更新
	/// </summary>
	void MenuStateUpdate();
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 今メニュー選択している番号
	/// </summary>
	int m_nowMenuSelectionNum = 0;
	/// <summary>
	/// メニューの最大数
	/// </summary>
	int m_maxMenuNum = -1;
	/// <summary>
	/// どのメニューを起動するかを確定する
	/// </summary>
	int m_confirmedMenuSelectionNum = 0;
	/// <summary>
	/// マウスカーソルスプライトの更新
	/// </summary>
	void MouseCursorSpriteUpdate();
	/// <summary>
	/// マウスカーソル
	/// </summary>
	SpriteRender m_mouseCursor;
	/// <summary>
	/// マウスカーソルを描画するか
	/// </summary>
	bool m_isMouseCorsorDraw = false;
	/// <summary>
	/// ゲームサウンドのインスタンス
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// ゲームウィンドウのインスタンス
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
};


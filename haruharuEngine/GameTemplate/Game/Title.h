#pragma once

class Load;
class GameMenu;

class Title : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Title(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Title() {}
	/// <summary>
	/// ゲームタイトルが終了したか
	/// </summary>
	/// <returns></returns>
	const bool& IsEndGameTitle()
	{
		return m_isGameIn;
	}
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// ゲームスタート
	/// </summary>
	bool GameStart()
	{
		m_isGameIn = true;

		return true;
	}
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// フォントのアップデート
	/// </summary>
	void FontUpdate();
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 背景
	/// </summary>
	SpriteRender m_backSideSprite;
	/// <summary>
	/// メイン文字
	/// </summary>
	FontRender m_mainFont;
	/// <summary>
	/// サブ文字
	/// </summary>
	FontRender m_subFont;
	/// <summary>
	/// タイトル
	/// </summary>
	FontRender m_title;
	/// <summary>
	/// ロード画面のインスタンス
	/// </summary>
	Load* m_load;
	/// <summary>
	/// ゲームメニュー
	/// </summary>
	GameMenu* m_gameMenu = nullptr;
	/// <summary>
	/// タイトル終了してゲームインに入る
	/// </summary>
	bool m_isGameIn = false;
};


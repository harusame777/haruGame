#pragma once
#include "GameMenu.h"
#include "GameSetting.h"

class GameSound;
class Load;

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
	~Title() 
	{
		DeleteGO(m_gameMenu);
	}
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
	/// ゲームサウンドのインスタンス
	/// </summary>
	GameSound* m_gameSound;
	/// <summary>
	/// ゲームメニュー
	/// </summary>
	GameMenu* m_gameMenu = nullptr;
	/// <summary>
	/// ゲーム設定
	/// </summary>
	GameSetting* m_gameSetting = nullptr;
	/// <summary>
	/// タイトル終了してゲームインに入る
	/// </summary>
	bool m_isGameIn = false;

	int test1;

	float test2;
};


#pragma once

namespace GameSettingConstant {

	static const int MAX_TEXT_NUM = 256;

};

class GameWindow;

class GameSetting : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameSetting() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameSetting() {};
private:
	/// <summary>
	/// 設定データ構造体
	/// </summary>
	struct SettingDatas
	{
		/// <summary>
		/// 設定項目名
		/// </summary>
		wchar_t m_settingItemName[GameSettingConstant::MAX_TEXT_NUM] = {};
		/// <summary>
		/// 設定項目名描画要フォントレンダー
		/// </summary>
		FontRender m_settingItemNameFont;
	};
	/// <summary>
	/// 設定データ構造体変数
	/// </summary>
	std::vector<SettingDatas> m_settingDatasList;
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
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ゲームウィンドウのインスタンス
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
};


#pragma once
#include <iostream>
#include <variant>

namespace GameSettingConstant {

	static const int MAX_TEXT_NUM = 256; 

	static const int MAX_SETTING_SPRITE_DRAW_NUM = 2;

	static const float SETTING_BAR_SPRITE_W_SIZE = 1002.0f;
	static const float SETTING_BAR_SPRITE_H_SIZE = 12.0f;

	static const float SETTING_BAR_SLIDER_SPRITE_W_SIZE = 26.0f;
	static const float SETTING_BAR_SLIDER_SPRITE_H_SIZE = 117.0f;

	static const Vector3 SETTING_SPRITE_POS = { 0.0f,200.0f,0.0f };

	static const float MOUSECORSOR_SPRITE_W_SIZE = 34.0f;
	static const float MOUSECORSOR_SPRITE_H_SIZE = 38.0f;

	static const Vector4 MAINTEXT_COLOR = { 1.0f,1.0f,1.0f,1.0f };

	static const float SLIDER_SPRITE_MOVE_MAX = 485.0f;
	static const float SLIDER_SPRITE_MOVE_MIN = -485.0f;
};

class GameWindow;
class GameSound;

class GameSetting : public IGameObject
{
public:
	enum SettingState
	{
		//待機
		en_standby,
		//ウィンドウを開く
		en_windowOpen,
		//設定終了時関数実行
		en_settingEndFuncBoot,
		//メニュー選択
		en_settingSelection,
		//設定中
		en_setting,
		//ウィンドウクローズ
		en_windowClose,
		//終了
		en_end
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameSetting() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameSetting() {};
	/// <summary>
	/// 命名定義、関数入れ物
	/// </summary>
	using SettingFunction = std::function<bool()>;
	/// <summary>
	/// 設定作成
	/// </summary>
	/// <param name="settingName"></param>
	/// <param name="address"></param>
	void InitSetting(
		const wchar_t* settingName,
		int& address,
		int maxValue,
		int minValue,
		const SettingFunction& settingEndFunc
	);
	void InitSetting(
		const wchar_t* settingName,
		float& address,
		float maxValue,
		float minValue,
		const SettingFunction& settingEndFunc
	);
	/// <summary>
	/// 設定メニュー閉じる時に実行する関数
	/// </summary>
void InitMenuEndFunc(const SettingFunction& menuFunc)
{
	m_isInitCloseFunc = true;

	m_settingCloseFunction = menuFunc;
}
/// <summary>
/// 設定メニューを開く
/// </summary>
void GoSettingMenuOpen();
/// <summary>
/// ステート変更
/// </summary>
/// <param name="changeState"></param>
void StateChange(const SettingState changeState)
{
	m_settingState = changeState;
}
/// <summary>
/// 設定が起動中かどうか
/// </summary>
/// <returns></returns>
bool IsSettingOpenNow()const
{
	if (m_settingState != SettingState::en_standby)
	{
		return true;
	}

	return false;
}
private:
	/// <summary>
	/// 設定データ構造体
	/// </summary>
	struct SettingDatas
	{
	private:
		/// <summary>
		/// 設定項目名
		/// </summary>
		wchar_t m_settingItemName[GameSettingConstant::MAX_TEXT_NUM] = {};
		/// <summary>
		/// 設定値アドレス保存要変数
		/// </summary>
		std::variant<int*, float*> m_settingValue;
		/// <summary>
		/// 設定値の最大値
		/// </summary>
		float m_maxSettingValue;
		/// <summary>
		/// 設定値の最小値
		/// </summary>
		float m_minSettingValue;
		/// <summary>
		/// 設定をした時に起動する関数
		/// </summary>
		SettingFunction m_settingEndBootFunc;
	public:
		/// <summary>
		/// セッティングスライダーの位置
		/// </summary>
		Vector3 m_settingSliderPos = Vector3::Zero;
		/// <summary>
		/// 設定値出力数字
		/// </summary>
		int m_settingValueDrawFontInt = 0;
		/// <summary>
		/// 設定値アドレス保存要変数、Int保存
		/// </summary>
		/// <param name="valueInt"></param>
		void SetSettingAddress(int& valueInt)
		{
			m_settingValue = &valueInt;
		}
		void SetSettingAddress(float& valueInt)
		{
			m_settingValue = &valueInt;
		}
		/// <summary>
		/// 設定値アドレスがint型かfloat型かを判定する関数
		/// int型だったらtrueを、float型だったらfalseを返す
		/// </summary>
		/// <returns></returns>
		const bool IsSettingAddressIntOrFloat()
		{
			if (std::get_if<int*>(&m_settingValue))
				return true;
			if (std::get_if<float*>(&m_settingValue))
				return false;

			return true;
		}
		/// <summary>
		/// 設定値の最大値と最小値を設定
		/// </summary>
		void SetSettingValueMaxAndMin(float const maxValue,float const minValue)
		{
			m_maxSettingValue = maxValue;

			m_minSettingValue = minValue;
		}
		const float GetSettingValueMax() const
		{
			return m_maxSettingValue;
		}
		const float GetSettingValueMin() const
		{
			return m_minSettingValue;
		}
		/// <summary>
		/// 設定値変更
		/// </summary>
		/// <param name="settingNum"></param>
		void SetSettingValue(int& valueInt)
		{
			if (auto* valuePtr = std::get_if<int*>(&m_settingValue)) {
				**valuePtr = valueInt;
			}
		}
		void SetSettingValue(float& valueInt)
		{
			if (auto* valuePtr = std::get_if<float*>(&m_settingValue)) {
				**valuePtr = valueInt;
			}
		}
		/// <summary>
		/// アドレス値を取得
		/// </summary>
		/// <returns></returns>
		std::variant<int, float> GetAddressNum()
		{
			if (auto valuePtr = std::get_if<int*>(&m_settingValue)){
				return **valuePtr;
			}
			else if(auto valuePtr = std::get_if<float*>(&m_settingValue)){
				return **valuePtr;
			}
		}
		/// <summary>
		/// 設定名を設定
		/// </summary>
		/// <param name="settingName"></param>
		void SettingName(const wchar_t* settingName)
		{
			swprintf_s(m_settingItemName,settingName);
		}
		wchar_t* GetSettingName()
		{
			return m_settingItemName;
		}
		/// <summary>
		/// 関数を設定
		/// </summary>
		/// <param name="func"></param>
		void SetSettingEndFunction(const SettingFunction& func)
		{
			m_settingEndBootFunc = func;
		}
		/// <summary>
		/// 関数を起動
		/// </summary>
		/// <returns></returns>
		const bool FuncExecute()
		{
			return m_settingEndBootFunc();
		}
	};
	/// <summary>
	/// 設定データ構造体変数
	/// </summary>
	std::vector<SettingDatas*> m_settingDatasList;
	/// <summary>
	/// 描画設定データ
	/// </summary>
	struct DrawSettingData
	{
	public:
		/// <summary>
		/// 設定項目名描画要フォントレンダー
		/// </summary>
		FontRender m_settingItemNameFontRender;
		/// <summary>
		/// セッティングバー
		/// </summary>
		SpriteRender m_settingBar;
		/// <summary>
		/// セッティングスライダー
		/// </summary>
		SpriteRender m_settingSlider;
		/// <summary>
		/// 設定データアドレス
		/// </summary>
		SettingDatas* m_settingDataAddress = nullptr;
		/// <summary>
		/// スプライト原点位置
		/// </summary>
		Vector3 m_spriteOriginPos = Vector3::Zero;
		/// <summary>
		/// スプライトフォント位置
		/// </summary>
		Vector3 m_spriteFontPos = Vector3::Zero;
		/// <summary>
		/// 設定値出力
		/// </summary>
		FontRender m_settingValueDrawFont;
		/// <summary>
		/// 設定値出力位置
		/// </summary>
		Vector3 m_settingValueFontPos = Vector3::Zero;
	public:
		/// <summary>
		/// 原点設定
		/// </summary>
		void SetOriginPos(const int dataNo)
		{
			m_spriteOriginPos = GameSettingConstant::SETTING_SPRITE_POS;

			m_spriteOriginPos.y -= 400 * dataNo;
		}
		/// <summary>
		/// スライダー設定
		/// </summary>
		void SetSliderPos()
		{

			m_settingDataAddress->m_settingSliderPos.y = m_spriteOriginPos.y;

		}
		/// <summary>
		/// 設定名設定
		/// </summary>
		/// <param name="dataNo"></param>
		void SetSettingNameFontPos(const int dataNo)
		{
			m_spriteFontPos = m_spriteOriginPos;

			m_spriteFontPos.y += 200.0f - (dataNo * 100.0f);

			m_spriteFontPos.x -= 800.0f;
		}
		/// <summary>
		/// 設定値表示設定
		/// </summary>
		/// <param name="dataNo"></param>
		void SetSettingValueFontPos(const int dataNo)
		{
			m_settingValueFontPos = m_spriteOriginPos;

			m_settingValueFontPos.y += 60 - (dataNo * 80.0f);

			m_settingValueFontPos.x += 600.0f;
		}
		/// <summary>
		/// 設定名描画更新
		/// </summary>
		void SettingItemNameFontUpdate()
		{
			wchar_t fontBuf[256] = {};

			swprintf_s(fontBuf, 256, m_settingDataAddress->GetSettingName());

			m_settingItemNameFontRender.SetText(fontBuf);

			m_settingItemNameFontRender.SetPosition(m_spriteFontPos);

			m_settingItemNameFontRender.SetColor(GameSettingConstant::MAINTEXT_COLOR);
		}
		/// <summary>
		/// 設定値描画更新
		/// </summary>
		void SettingValueFontUpdate()
		{
			wchar_t fontBuf[256] = {};

			swprintf_s(fontBuf, 256,L"( %d )", m_settingDataAddress
				->m_settingValueDrawFontInt);

			m_settingValueDrawFont.SetText(fontBuf);

			m_settingValueDrawFont.SetPosition(m_settingValueFontPos);

			m_settingValueDrawFont.SetColor(GameSettingConstant::MAINTEXT_COLOR);
		}
		/// <summary>
		/// 設定バー位置設定
		/// </summary>
		void SetSettingBarPosUpdate()
		{
			m_settingBar.SetPosition(m_spriteOriginPos);
		}
		/// <summary>
		/// 設定スライダー位置更新
		/// </summary>
		void SetSettingSliderPosUpdate()
		{
			m_settingSlider.SetPosition(
				m_settingDataAddress->m_settingSliderPos);
		}
	};
	/// <summary>
	/// 描画設定データ変数
	/// </summary>
	DrawSettingData m_settingDrawDatasList[GameSettingConstant
		::MAX_SETTING_SPRITE_DRAW_NUM];
	/// <summary>
	/// 設定ステート
	/// </summary>
	SettingState m_settingState = SettingState::en_standby;
	/// <summary>
	/// 設定メニュー終了時実行関数
	/// </summary>
	SettingFunction m_settingCloseFunction;
	/// <summary>
	/// メニュー終了時実行関数が初期化されているかどうか
	/// </summary>
	bool m_isInitCloseFunc = false;
	/// <summary>
	/// 設定項目数
	/// </summary>
	int m_settingItemNum = 0;
	/// <summary>
	/// 現在選択中の設定項目
	/// </summary>
	int m_settingItemSelectionNum = 0;
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
	/// 設定ステート更新
	/// </summary>
	void SettingStateUpdate();
	/// <summary>
	/// 設定スプライト更新
	/// </summary>
	void SettingSpriteUpdate();
	/// <summary>
	/// 描画データの更新
	/// </summary>
	void UpdateDrawSettingData(const int initNum);
	/// <summary>
	/// セッティング選ぶ関数
	/// </summary>
	void SettingSelection();
	/// <summary>
	/// マウスカーソルスプライトの更新
	/// </summary>
	void MouseCursorSpriteUpdate();
	/// <summary>
	/// 設定実行
	/// </summary>
	void SettingExecute();
	/// <summary>
	/// 設定関数実行
	/// </summary>
	const bool SettingEndFuncExecute();
	/// <summary>
	/// 設定値計算
	/// </summary>
	void SettingValueCalc(const int listNo);
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 設定スプライトが描画できるかどうか
	/// </summary>	
	/// <returns></returns>
	const bool IsSettingSpriteDraw() const
	{
		if (m_settingState != SettingState::en_settingSelection &&
			m_settingState != SettingState::en_setting &&
			m_settingState != SettingState::en_settingEndFuncBoot)
			return false;
		else
			return true;
	}
	/// <summary>
	/// マウスカーソル
	/// </summary>
	SpriteRender m_mouseCursor;
	/// <summary>
	/// ゲームウィンドウのインスタンス
	/// </summary>
	GameWindow* m_gameWindow = nullptr;
	/// <summary>
	/// ゲームサウンドのインスタンス
	/// </summary>
	GameSound* m_gameSound = nullptr;
	/// <summary>
	/// flaot用線形補間
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}

	FontRender m_debugFont;
};


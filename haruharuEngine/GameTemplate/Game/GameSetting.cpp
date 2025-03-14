#include "stdafx.h"
#include "GameSetting.h"
#include "GameWindow.h"
#include "GameSound.h"
#include <iostream>
#include <variant>


bool GameSetting::Start()
{

	//ゲームウィンドウを作成
	m_gameWindow = NewGO<GameWindow>(1,"gameSettingWindow");

	//ゲームサウンドのインスタンスを取得
	m_gameSound = FindGO<GameSound>("gameSound");

	//マウスカーソル
	m_mouseCursor.Init("Assets/modelData/window/mouse_cursor.DDS",
		GameSettingConstant::MOUSECORSOR_SPRITE_W_SIZE,
		GameSettingConstant::MOUSECORSOR_SPRITE_H_SIZE
	);

	return true;
}

void GameSetting::InitSetting(
	const wchar_t* settingName,
	int& address,
	int maxValue,
	int minValue,
	const SettingFunction& settingEndFunc
)
{
	int size = m_settingDatasList.size();

	//int用設定
	SettingDatas* newData = new SettingDatas;

	newData->SetSettingAddress(address);

	newData->SettingName(settingName);

	newData->SetSettingEndFunction(settingEndFunc);

	newData->SetSettingValueMaxAndMin(maxValue, minValue);

	newData->m_settingBar.Init("Assets/modelData/window/settingBar_sprite_1.DDS",
		GameSettingConstant::SETTING_BAR_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_BAR_SPRITE_H_SIZE
	);

	newData->m_settingSlider.Init("Assets/modelData/window/settingBar_sprite_2.DDS",
		GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_H_SIZE
	);

	m_settingDatasList.push_back(newData);

	SettingValueCalc(size);
}

void GameSetting::InitSetting(
	const wchar_t* settingName,
	float& address,
	float maxValue,
	float minValue,
	const SettingFunction& settingEndFunc
)
{

	int size = m_settingDatasList.size();

	//float用設定
	SettingDatas* newData = new SettingDatas;

	newData->SetSettingAddress(address);

	newData->SettingName(settingName);

	newData->SetSettingEndFunction(settingEndFunc);

	newData->SetSettingValueMaxAndMin(maxValue, minValue);

	newData->m_settingBar.Init("Assets/modelData/window/settingBar_sprite_1.DDS",
		GameSettingConstant::SETTING_BAR_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_BAR_SPRITE_H_SIZE
	);

	newData->m_settingSlider.Init("Assets/modelData/window/settingBar_sprite_2.DDS",
		GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_H_SIZE
	);

	m_settingDatasList.push_back(newData);

	SettingValueCalc(size);
}

void GameSetting::GoSettingMenuOpen()
{
	if (m_settingState != SettingState::en_standby)
	{
		return;
	}

	m_settingItemNum = m_settingDatasList.size() - 1;

	m_settingItemSelectionNum = 0;

	m_gameWindow->WindowOpen();

	UpdateDrawSettingData(m_settingItemSelectionNum);

	StateChange(SettingState::en_windowOpen);
}

void GameSetting::Update()
{
	//ステート更新
	SettingStateUpdate();

	//スプライト更新
	SettingSpriteUpdate();
}

void GameSetting::SettingStateUpdate()
{
	
	switch (m_settingState)
	{
	case GameSetting::en_standby:

		//待機

		break;
	case GameSetting::en_windowOpen:

		//ウィンドウ開くまで待機
		if (m_gameWindow->IsWindowOpen() == true)
		{
			//開いたらステート変更
			StateChange(SettingState::en_settingSelection);
		}

		break;
	case GameSetting::en_settingEndFuncBoot:



		break;
	case GameSetting::en_settingSelection:

		//設定項目選択
		SettingSelection();

		break;
	case GameSetting::en_setting:

		SettingExecute();

		break;
	case GameSetting::en_windowClose:

		if (m_gameWindow->IsWindowClose() == true)
		{

			if (m_isInitCloseFunc == true)
				m_settingCloseFunction(true);

			StateChange(SettingState::en_end);

		}

		break;
	case GameSetting::en_closeMenuFuntionGo:
		break;
	case GameSetting::en_end:

		m_settingItemSelectionNum = 0;

		StateChange(SettingState::en_standby);

		break;
	default:
		break;
	}

}

void GameSetting::SettingSelection()
{
	//ウィンドウ開いてなかったら
	if (m_gameWindow->IsWindowOpen() == false)
		//戻す
		return;

	//もし十字上ボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		//現在選択中の項目番号が0以下なら
		if (m_settingItemSelectionNum <= 0)
			//戻す
			return;

		//もしm_settingItemSelectionNumの数が
		// MAX_SETTING_SPRITE_DRAW_NUMの倍数なら
		if (m_settingItemSelectionNum % GameSettingConstant::
			MAX_SETTING_SPRITE_DRAW_NUM == 0)
			//描画データを更新する
			UpdateDrawSettingData(m_settingItemSelectionNum 
				- GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM);

		//変数を1減らす
		m_settingItemSelectionNum--;	
	}
	//もし十字下ボタンが押されたら
	else if(g_pad[0]->IsTrigger(enButtonDown))
	{
		//現在選択中の項目番号が設定最大数以上なら
		if (m_settingItemNum <= m_settingItemSelectionNum)
			//戻す
			return;

		//変数を1増やす
		m_settingItemSelectionNum++;

		//もしm_settingItemSelectionNumの数が
		// MAX_SETTING_SPRITE_DRAW_NUMの倍数なら
		if (m_settingItemSelectionNum % GameSettingConstant::
			MAX_SETTING_SPRITE_DRAW_NUM == 0)
			//描画データを更新する
			UpdateDrawSettingData(m_settingItemSelectionNum);
	}
	else if (g_pad[0]->IsTrigger(enButtonB))
	{
		
		StateChange(SettingState::en_setting);

	}
	else if(g_pad[0]->IsTrigger(enButtonA))
	{
		m_gameWindow->WindowClose();

		StateChange(SettingState::en_windowClose);
	}

	//マウスカーソル更新
	MouseCursorSpriteUpdate();
}

void GameSetting::MouseCursorSpriteUpdate()
{
	//マウスカーソル位置番号
	int ListNo = 0;

	//ゼロ除算しないために、条件文で判定
	if (m_settingItemSelectionNum != 0)
		ListNo = m_settingItemSelectionNum % 2;

	//マウスカーソル位置決定
	Vector3 mousePos;

	mousePos.y = m_settingDrawDatasList[ListNo]
		.m_spriteOriginPos.y + 100.0f - (ListNo * 20);

	mousePos.x -= 700.0f;

	m_mouseCursor.SetPosition(mousePos);

}

void GameSetting::SettingSpriteUpdate()
{
	//設定ステートが下記以外だったら
	if (m_settingState != SettingState::en_settingSelection &&
		m_settingState != SettingState::en_setting)
		//戻す
		return;	

	//位置更新
	for (int drawDataNo = 0;
		drawDataNo < GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM;
		drawDataNo++)
	{
		//アドレスがヌルだったら
		if (m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			== nullptr)
			//飛ばす
			continue;

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingBar.SetPosition(
				m_settingDrawDatasList[drawDataNo].m_spriteOriginPos);

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingSlider.SetPosition(
				m_settingDrawDatasList[drawDataNo].m_settingDataAddress->m_settingSliderPos);

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingBar.Update();
	
		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingSlider.Update();

		//表示文字設定

		wchar_t fontBuf[256] = {};

		swprintf_s(fontBuf, 256, m_settingDrawDatasList[drawDataNo]
			.m_settingDataAddress->GetSettingName());

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingItemNameFontRender.SetText(fontBuf);

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingItemNameFontRender.SetPosition(
				m_settingDrawDatasList[drawDataNo].m_spriteFontPos);

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingItemNameFontRender.SetColor(
				GameSettingConstant::MAINTEXT_COLOR);

		//設定値文字設定

		swprintf_s(fontBuf, 256, L"( %.2f )", m_settingDrawDatasList[drawDataNo]
			.m_settingDataAddress->GetAddressNum());

		m_settingDrawDatasList[drawDataNo].m_settingValueDrawFont
			.SetText(fontBuf);

		m_settingDrawDatasList[drawDataNo].m_settingValueDrawFont
			.SetPosition(m_settingDrawDatasList[drawDataNo].m_settingValueFontPos);

		m_settingDrawDatasList[drawDataNo].m_settingValueDrawFont
			.SetColor(GameSettingConstant::MAINTEXT_COLOR);
	}

	m_mouseCursor.Update();
}

void GameSetting::UpdateDrawSettingData(const int initNum)
{
	//設定指定項目数
	int itemDataNo = initNum;

	//MAX_SETTING_SPRITE_DRAW_NUMの数ぶん繰り返す
	for (int drawDataNo = 0;
		drawDataNo < GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM;
		drawDataNo++)
	{
		//もし設定指定項目数が設定項目数より多かったら
		if (m_settingItemNum < itemDataNo)
		{
			//ヌルにして
			m_settingDrawDatasList[drawDataNo].m_settingDataAddress
				= nullptr;

			//繰り返しから抜ける
			break;
		}

		//描画する設定項目データのアドレスを代入
		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			= m_settingDatasList[itemDataNo];

		//設定項目の原点位置を設定
		m_settingDrawDatasList[drawDataNo].m_spriteOriginPos = GameSettingConstant
			::SETTING_SPRITE_POS;

		m_settingDrawDatasList[drawDataNo].m_spriteOriginPos.y -= 400 * drawDataNo;

		//セッティングスライダーの位置を設定
		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingSliderPos = m_settingDrawDatasList[drawDataNo].m_spriteOriginPos;

		//文字位置を設定
		m_settingDrawDatasList[drawDataNo].m_spriteFontPos
			= m_settingDrawDatasList[drawDataNo].m_spriteOriginPos;

		m_settingDrawDatasList[drawDataNo].m_spriteFontPos.y += 200.0f
			- (drawDataNo * 100.0f);
		m_settingDrawDatasList[drawDataNo].m_spriteFontPos.x -= 800.0f;

		//設定値出力位置を設定

		m_settingDrawDatasList[drawDataNo].m_settingValueFontPos 
			= m_settingDrawDatasList[drawDataNo].m_spriteOriginPos;

		m_settingDrawDatasList[drawDataNo].m_settingValueFontPos.x += 500.0f;

		//設定指定項目数を一増やす
		itemDataNo++;
	}
}

void GameSetting::SettingExecute()
{

	if (g_pad[0]->IsPress(enButtonLeft))
	{
		if (GameSettingConstant::SLIDER_SPRITE_MOVE_MIN
			>= m_settingDatasList[m_settingItemSelectionNum]->m_settingSliderPos.x)
			return;

		m_settingDatasList[m_settingItemSelectionNum]
			->m_settingSliderPos.x -= g_gameTime->GetFrameDeltaTime() * 20.0f;

	}
	else if(g_pad[0]->IsPress(enButtonRight))
	{
		if (GameSettingConstant::SLIDER_SPRITE_MOVE_MAX
			<= m_settingDatasList[m_settingItemSelectionNum]->m_settingSliderPos.x)
			return;

		m_settingDatasList[m_settingItemSelectionNum]
			->m_settingSliderPos.x += g_gameTime->GetFrameDeltaTime() * 20.0f;

	}
	else if(g_pad[0]->IsTrigger(enButtonA))
	{

		StateChange(SettingState::en_settingSelection);

	}

	SettingValueCalc(m_settingItemSelectionNum);
}

void GameSetting::SettingValueCalc(const int listNo)
{
	//まずはスライダーの値を1から0の値に正規化を行う

		//現在数値取得
	float nowValue = m_settingDatasList[listNo]
		->m_settingSliderPos.x;

	//正規化計算最大値最小値設定
	float normalizeMaxValue = GameSettingConstant::SLIDER_SPRITE_MOVE_MAX;
	float normalizeMinValue = GameSettingConstant::SLIDER_SPRITE_MOVE_MIN;

	//数値調整
	if (nowValue > normalizeMaxValue)
		nowValue = normalizeMaxValue;

	if (nowValue < normalizeMinValue)
		nowValue = normalizeMinValue;

	//正規化計算
	float normalize = 1.0 - (nowValue + normalizeMinValue) 
		/ (normalizeMinValue - normalizeMaxValue);

	//線形保管計算最大値最小値設定
	float leapMaxValue = m_settingDatasList[listNo]->GetSettingValueMax();
	float leapMinValue = m_settingDatasList[listNo]->GetSettingValueMin();

	//線形保管を使用して正規化された割合から数値を出す
	float leapValue = Leap(leapMinValue, leapMaxValue, normalize);
	
	float floatFinalValue = 0.0f;
	int	intFinalValue = 0.0f;

	//データ変数の設定値アドレスの方によって処理を変更
	if (m_settingDatasList[listNo]
		->IsSettingAddressIntOrFloat() == true)
	{
		intFinalValue = static_cast<int>(std::round(leapValue));

		m_settingDatasList[listNo]
			->SetSettingValue(intFinalValue);
	}
	else
	{
		floatFinalValue = std::floor(leapValue * 100) / 100;

		m_settingDatasList[listNo]
			->SetSettingValue(floatFinalValue);
	}
}

void GameSetting::Render(RenderContext& rc)
{
	if (m_settingState != SettingState::en_settingSelection &&
		m_settingState != SettingState::en_setting)
		return;

	for (int drawDataNo = 0;
		drawDataNo < GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM;
		drawDataNo++)
	{
		if (m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			== nullptr)
			continue;

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingBar.Draw(rc);

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingSlider.Draw(rc);

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingItemNameFontRender.Draw(rc);

		m_settingDrawDatasList[drawDataNo].m_settingValueDrawFont.Draw(rc);

	}

	wchar_t debugFont[256] = {};

	swprintf_s(debugFont, 256, L"settingSlider_X : %.2f", m_settingDatasList[0]->m_settingSliderPos.x);

	m_debugFont.SetText(debugFont);

	m_debugFont.SetPosition({ 0.0f,500.0f,0.0f });

	m_debugFont.Draw(rc);

	m_mouseCursor.Draw(rc);
}

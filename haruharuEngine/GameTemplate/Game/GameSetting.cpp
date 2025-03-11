#include "stdafx.h"
#include "GameSetting.h"
#include "GameWindow.h"
#include "GameSound.h"

bool GameSetting::Start()
{

	//ゲームウィンドウを作成
	m_gameWindow = NewGO<GameWindow>(1,"gameSettingWindow");

	//ゲームサウンドのインスタンスを取得
	m_gameSound = FindGO<GameSound>("gameSound");

	return true;
}

void GameSetting::InitSetting(
	const wchar_t* settingName,
	int& address,
	const SettingFunction& settingEndFunc
)
{
	//int用設定
	SettingDatas* newData = new SettingDatas;

	newData->SetSettingAddress(address);

	newData->SettingName(settingName);

	newData->SetSettingEndFunction(settingEndFunc);

	newData->m_settingBar.Init("Assets/modelData/window/settingBar_sprite_1.DDS",
		GameSettingConstant::SETTING_BAR_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_BAR_SPRITE_H_SIZE
	);

	newData->m_settingSlider.Init("Assets/modelData/window/settingBar_sprite_2.DDS",
		GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_H_SIZE
	);

	m_settingDatasList.push_back(newData);
}

void GameSetting::InitSetting(
	const wchar_t* settingName,
	float& address,
	const SettingFunction& settingEndFunc
)
{
	//float用設定
	SettingDatas* newData = new SettingDatas;

	newData->SetSettingAddress(address);

	newData->SettingName(settingName);

	newData->SetSettingEndFunction(settingEndFunc);

	newData->m_settingBar.Init("Assets/modelData/window/settingBar_sprite_1.DDS",
		GameSettingConstant::SETTING_BAR_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_BAR_SPRITE_H_SIZE
	);

	newData->m_settingSlider.Init("Assets/modelData/window/settingBar_sprite_2.DDS",
		GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_H_SIZE
	);

	m_settingDatasList.push_back(newData);
}

void GameSetting::GoSettingMenuOpen()
{
	if (m_settingState != SettingState::en_standby)
	{
		return;
	}

	m_settingItemNum = m_settingDatasList.size();

	m_gameWindow->WindowOpen();

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
		break;
	case GameSetting::en_windowClose:
		break;
	case GameSetting::en_closeMenuFuntionGo:
		break;
	case GameSetting::en_end:
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
	}

}

void GameSetting::SettingSpriteUpdate()
{
	//設定ステートが下記以外だったら
	if (m_settingState != SettingState::en_settingSelection &&
		m_settingState != SettingState::en_setting)
		//戻す
		return;

	m_settingDatasList[m_settingItemSelectionNum]
		->m_settingSlider.SetPosition(GameSettingConstant::SETTING_SPRITE_POS);

}

void GameSetting::Render(RenderContext& rc)
{
	if(m_settingState == SettingState::en_settingSelection ||
		m_settingState == SettingState::en_setting)
	{

		m_settingDatasList[m_settingItemSelectionNum]->m_settingSlider.Draw(rc);
		m_settingDatasList[m_settingItemSelectionNum]->m_settingBar.Draw(rc);

	}
}

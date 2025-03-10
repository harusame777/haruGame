#include "stdafx.h"
#include "GameSetting.h"
#include "GameWindow.h"

bool GameSetting::Start()
{

	//ゲームウィンドウを作成
	m_gameWindow = NewGO<GameWindow>(1,"gameSettingWindow");

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

	m_settingState = SettingState::en_windowOpen;
}

void GameSetting::Update()
{
	//ステート更新
	SettingStateUpdate();
}

void GameSetting::SettingStateUpdate()
{

}

void GameSetting::Render(RenderContext& rc)
{

}

#include "stdafx.h"
#include "GameSetting.h"
#include "GameWindow.h"
#include "GameSound.h"

bool GameSetting::Start()
{

	//�Q�[���E�B���h�E���쐬
	m_gameWindow = NewGO<GameWindow>(1,"gameSettingWindow");

	//�Q�[���T�E���h�̃C���X�^���X���擾
	m_gameSound = FindGO<GameSound>("gameSound");

	return true;
}

void GameSetting::InitSetting(
	const wchar_t* settingName,
	int& address,
	const SettingFunction& settingEndFunc
)
{
	//int�p�ݒ�
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
	//float�p�ݒ�
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
	//�X�e�[�g�X�V
	SettingStateUpdate();

	//�X�v���C�g�X�V
	SettingSpriteUpdate();
}

void GameSetting::SettingStateUpdate()
{
	
	switch (m_settingState)
	{
	case GameSetting::en_standby:

		//�ҋ@

		break;
	case GameSetting::en_windowOpen:

		//�E�B���h�E�J���܂őҋ@
		if (m_gameWindow->IsWindowOpen() == true)
		{
			//�J������X�e�[�g�ύX
			StateChange(SettingState::en_settingSelection);
		}

		break;
	case GameSetting::en_settingEndFuncBoot:



		break;
	case GameSetting::en_settingSelection:

		//�ݒ荀�ڑI��
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
	//�E�B���h�E�J���ĂȂ�������
	if (m_gameWindow->IsWindowOpen() == false)
		//�߂�
		return;

	//�����\����{�^���������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		//���ݑI�𒆂̍��ڔԍ���0�ȉ��Ȃ�
		if (m_settingItemSelectionNum <= 0)
			//�߂�
			return;

		//�ϐ���1���炷
		m_settingItemSelectionNum--;
	}
	//�����\�����{�^���������ꂽ��
	else if(g_pad[0]->IsTrigger(enButtonDown))
	{
		//���ݑI�𒆂̍��ڔԍ����ݒ�ő吔�ȏ�Ȃ�
		if (m_settingItemNum <= m_settingItemSelectionNum)
			//�߂�
			return;

		//�ϐ���1���₷
		m_settingItemSelectionNum++;
	}

}

void GameSetting::SettingSpriteUpdate()
{
	//�ݒ�X�e�[�g�����L�ȊO��������
	if (m_settingState != SettingState::en_settingSelection &&
		m_settingState != SettingState::en_setting)
		//�߂�
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

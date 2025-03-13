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

	m_mouseCursor.Init("Assets/modelData/window/mouse_cursor.DDS",
		GameSettingConstant::MOUSECORSOR_SPRITE_W_SIZE,
		GameSettingConstant::MOUSECORSOR_SPRITE_H_SIZE
	);

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

	m_settingItemNum = m_settingDatasList.size() - 1;

	m_settingItemSelectionNum = 0;

	m_gameWindow->WindowOpen();

	UpdateDrawSettingData(m_settingItemSelectionNum);

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

		//����m_settingItemSelectionNum�̐���
		// MAX_SETTING_SPRITE_DRAW_NUM�̔{���Ȃ�
		if (m_settingItemSelectionNum % GameSettingConstant::
			MAX_SETTING_SPRITE_DRAW_NUM == 0)
			//�`��f�[�^���X�V����
			UpdateDrawSettingData(m_settingItemSelectionNum 
				- GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM);

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

		//����m_settingItemSelectionNum�̐���
		// MAX_SETTING_SPRITE_DRAW_NUM�̔{���Ȃ�
		if (m_settingItemSelectionNum % GameSettingConstant::
			MAX_SETTING_SPRITE_DRAW_NUM == 0)
			//�`��f�[�^���X�V����
			UpdateDrawSettingData(m_settingItemSelectionNum);
	}

}

void GameSetting::SettingSpriteUpdate()
{
	//�ݒ�X�e�[�g�����L�ȊO��������
	if (m_settingState != SettingState::en_settingSelection &&
		m_settingState != SettingState::en_setting)
		//�߂�
		return;	

	//�ʒu�X�V
	for (int drawDataNo = 0;
		drawDataNo < GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM;
		drawDataNo++)
	{
		//�A�h���X���k����������
		if (m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			== nullptr)
			//��΂�
			continue;

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingBar.SetPosition(
				m_settingDrawDatasList[drawDataNo].m_spriteOriginPos);

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingSlider.SetPosition(
				m_settingDrawDatasList[drawDataNo].m_spriteOriginPos);

		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingBar.Update();
	
		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			->m_settingSlider.Update();

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
	}
}

void GameSetting::UpdateDrawSettingData(const int initNum)
{
	//�ݒ�w�荀�ڐ�
	int itemDataNo = initNum;

	//MAX_SETTING_SPRITE_DRAW_NUM�̐��Ԃ�J��Ԃ�
	for (int drawDataNo = 0;
		drawDataNo < GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM;
		drawDataNo++)
	{
		//�����ݒ�w�荀�ڐ����ݒ荀�ڐ���葽��������
		if (m_settingItemNum < itemDataNo)
		{
			//�k���ɂ���
			m_settingDrawDatasList[drawDataNo].m_settingDataAddress
				= nullptr;

			//�J��Ԃ����甲����
			break;
		}

		//�`�悷��ݒ荀�ڃf�[�^�̃A�h���X����
		m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			= m_settingDatasList[itemDataNo];

		//�ݒ荀�ڂ̌��_�ʒu��ݒ�
		m_settingDrawDatasList[drawDataNo].m_spriteOriginPos = GameSettingConstant
			::SETTING_SPRITE_POS;

		m_settingDrawDatasList[drawDataNo].m_spriteOriginPos.y -= 400 * drawDataNo;

		//�����ʒu��ݒ�
		m_settingDrawDatasList[drawDataNo].m_spriteFontPos
			= m_settingDrawDatasList[drawDataNo].m_spriteOriginPos;

		m_settingDrawDatasList[drawDataNo].m_spriteFontPos.y += 200.0f
			- (drawDataNo * 100.0f);
		m_settingDrawDatasList[drawDataNo].m_spriteFontPos.x -= 800.0f;

		//�ݒ�w�荀�ڐ����ꑝ�₷
		itemDataNo++;
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

	}
}

#include "stdafx.h"
#include "GameSetting.h"
#include "GameWindow.h"
#include "GameSound.h"
#include <iostream>
#include <variant>


bool GameSetting::Start()
{

	//�Q�[���E�B���h�E���쐬
	m_gameWindow = NewGO<GameWindow>(1,"gameSettingWindow");

	//�Q�[���T�E���h�̃C���X�^���X���擾
	m_gameSound = FindGO<GameSound>("gameSound");

	//�}�E�X�J�[�\��
	m_mouseCursor.Init(
		"Assets/modelData/window/mouse_cursor.DDS",
		GameSettingConstant::MOUSECORSOR_SPRITE_W_SIZE,
		GameSettingConstant::MOUSECORSOR_SPRITE_H_SIZE
	);

	//�E�B���h�E�₶�邵
	m_windowArrowDown.Init(
		"Assets/modelData/window/settingArrow_sprite.DDS",
		GameSettingConstant::SETTING_ARROW_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_ARROW_SPRITE_H_SIZE
	);

	m_windowArrowUp.Init(
		"Assets/modelData/window/settingArrow_sprite.DDS",
		GameSettingConstant::SETTING_ARROW_SPRITE_W_SIZE,
		GameSettingConstant::SETTING_ARROW_SPRITE_H_SIZE
	);

	Quaternion rot;

	rot.SetRotationDegZ(180.0f);

	m_windowArrowUp.SetRotation(rot);

	for (int drawDataNo = 0;
		drawDataNo < GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM;
		drawDataNo++)
	{
		m_settingDrawDatasList[drawDataNo].m_settingBar.Init(
			"Assets/modelData/window/settingBar_sprite_1.DDS",
			GameSettingConstant::SETTING_BAR_SPRITE_W_SIZE,
			GameSettingConstant::SETTING_BAR_SPRITE_H_SIZE
		);

		m_settingDrawDatasList[drawDataNo].m_settingSlider.Init(
			"Assets/modelData/window/settingBar_sprite_2.DDS",
			GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_W_SIZE,
			GameSettingConstant::SETTING_BAR_SLIDER_SPRITE_H_SIZE
		);
	}

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

	//int�p�ݒ�
	SettingDatas* newData = new SettingDatas;

	newData->SetSettingAddress(address);

	newData->SettingName(settingName);

	newData->SetSettingEndFunction(settingEndFunc);

	newData->SetSettingValueMaxAndMin(maxValue, minValue);

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

	//float�p�ݒ�
	SettingDatas* newData = new SettingDatas;

	newData->SetSettingAddress(address);

	newData->SettingName(settingName);

	newData->SetSettingEndFunction(settingEndFunc);

	newData->SetSettingValueMaxAndMin(maxValue, minValue);

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

	for (int listNo = 0;
		listNo < m_settingItemNum ; 
		listNo++)
	{
		if ((listNo + 1) % GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM == 0)
			m_settingPageNum++;
	}

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

		if (SettingEndFuncExecute() == true)
		{
			StateChange(SettingState::en_settingSelection);
		}

		break;
	case GameSetting::en_settingSelection:

		//�ݒ荀�ڑI��
		SettingSelection();

		break;
	case GameSetting::en_setting:

		//�ݒ���s
		SettingExecute();

		break;
	case GameSetting::en_windowClose:

		if (m_gameWindow->IsWindowClose() == true)
		{
			if (m_isInitCloseFunc == true)
				m_settingCloseFunction();

			StateChange(SettingState::en_end);
		}

		break;
	case GameSetting::en_end:

		m_settingItemSelectionNum = 0;

		m_nowSettingPageNum = 0;

		StateChange(SettingState::en_standby);

		break;
	default:
		break;
	}

}

void GameSetting::SettingSelection()
{
	//�E�B���h�E�J���ĂȂ�������
	if (m_gameWindow->IsWindowOpen() == false)
	{
		return;
	}

	//�����\����{�^���������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		//���ݑI�𒆂̍��ڔԍ���0�ȉ��Ȃ�
		if (m_settingItemSelectionNum <= 0)
		{
			return;
		}

		//����m_settingItemSelectionNum�̐���
		// MAX_SETTING_SPRITE_DRAW_NUM�̔{���Ȃ�
		if (m_settingItemSelectionNum % GameSettingConstant::
			MAX_SETTING_SPRITE_DRAW_NUM == 0)
		{
			m_nowSettingPageNum--;

			//�`��f�[�^���X�V����
			UpdateDrawSettingData(m_settingItemSelectionNum
				- GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM);
		}

		m_settingItemSelectionNum--;	
	}
	//�����\�����{�^���������ꂽ��
	else if(g_pad[0]->IsTrigger(enButtonDown))
	{
		//���ݑI�𒆂̍��ڔԍ����ݒ�ő吔�ȏ�Ȃ�
		if (m_settingItemNum <= m_settingItemSelectionNum)
		{
			return;
		}

		m_settingItemSelectionNum++;

		//����m_settingItemSelectionNum�̐���
		// MAX_SETTING_SPRITE_DRAW_NUM�̔{���Ȃ�
		if (m_settingItemSelectionNum % GameSettingConstant::
			MAX_SETTING_SPRITE_DRAW_NUM == 0)
		{
			m_nowSettingPageNum++;

			UpdateDrawSettingData(m_settingItemSelectionNum);
		}
	}
	else if (g_pad[0]->IsTrigger(enButtonB))
	{
		//�ݒ荀�ڐ���0�ȉ��Ȃ�
		if (m_settingItemNum < 0)
		{
			return;
		}
		
		StateChange(SettingState::en_setting);
	}
	else if(g_pad[0]->IsTrigger(enButtonA))
	{
		m_gameWindow->WindowClose();

		StateChange(SettingState::en_windowClose);
	}

	//�}�E�X�J�[�\���X�V
	MouseCursorSpriteUpdate();
}

void GameSetting::MouseCursorSpriteUpdate()
{
	//�}�E�X�J�[�\���ʒu�ԍ�
	int ListNo = 0;

	//�[�����Z���Ȃ����߂ɁA�������Ŕ���
	if (m_settingItemSelectionNum != 0)
		ListNo = m_settingItemSelectionNum % 2;

	//�}�E�X�J�[�\���ʒu����
	Vector3 mousePos;

	mousePos.y = m_settingDrawDatasList[ListNo]
		.m_spriteOriginPos.y + 100.0f - (ListNo * 20);

	mousePos.x -= 700.0f;

	m_mouseCursor.SetPosition(mousePos);

	m_windowArrowDown.SetPosition({ 0.0f,-350.0f,0.0f });

	m_windowArrowUp.SetPosition({ 0.0f,350.0f,0.0f });
}

void GameSetting::SettingSpriteUpdate()
{
	//�ݒ�X�e�[�g�����L�ȊO��������
	if (IsSettingSpriteDraw() == false)
	{
		return;
	}

	//�ʒu�X�V
	for (int drawDataNo = 0;
		drawDataNo < GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM;
		drawDataNo++)
	{
		//�A�h���X���k����������
		if (m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			== nullptr)
		{
			continue;
		}

		//�ݒ�o�[�ʒu�X�V
		m_settingDrawDatasList[drawDataNo].SetSettingBarPosUpdate();

		//�X���C�_�[�ʒu�X�V
		m_settingDrawDatasList[drawDataNo].SetSettingSliderPosUpdate();

		//�ݒ�o�[�X�v���C�g�X�V
		m_settingDrawDatasList[drawDataNo].m_settingBar.Update();
	
		//�X���C�_�[�X�v���C�g�X�V
		m_settingDrawDatasList[drawDataNo].m_settingSlider.Update();

		//�\�������ݒ�
		m_settingDrawDatasList[drawDataNo].SettingItemNameFontUpdate();
		
		//�ݒ�l�����ݒ�
		m_settingDrawDatasList[drawDataNo].SettingValueFontUpdate();

		//�E�B���h�E�₶�邵�X�V
		m_windowArrowUp.Update();
		m_windowArrowDown.Update();
	}

	m_mouseCursor.Update();
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
		m_settingDrawDatasList[drawDataNo].SetOriginPos(drawDataNo);

		//�����ʒu��ݒ�
		m_settingDrawDatasList[drawDataNo].SetSettingNameFontPos(drawDataNo);

		//�ݒ�l�o�͈ʒu��ݒ�
		m_settingDrawDatasList[drawDataNo].SetSettingValueFontPos(drawDataNo);

		//�Z�b�e�B���O�X���C�_�[�̈ʒu��ݒ�
		m_settingDrawDatasList[drawDataNo].SetSliderPos();

		//�ݒ�w�荀�ڐ����ꑝ�₷
		itemDataNo++;
	}
}

void GameSetting::SettingExecute()
{

	if (g_pad[0]->IsPress(enButtonLeft))
	{
		if (GameSettingConstant::SLIDER_SPRITE_MOVE_MIN
			>= m_settingDatasList[m_settingItemSelectionNum]->m_settingSliderPos.x)
		{
			m_settingDatasList[m_settingItemSelectionNum]
				->m_settingSliderPos.x = GameSettingConstant::SLIDER_SPRITE_MOVE_MIN;

			return;
		}

		m_settingDatasList[m_settingItemSelectionNum]
			->m_settingSliderPos.x -= g_gameTime->GetFrameDeltaTime() * 200.0f;

	}
	else if(g_pad[0]->IsPress(enButtonRight))
	{
		if (GameSettingConstant::SLIDER_SPRITE_MOVE_MAX
			<= m_settingDatasList[m_settingItemSelectionNum]->m_settingSliderPos.x)
		{
			m_settingDatasList[m_settingItemSelectionNum]
				->m_settingSliderPos.x = GameSettingConstant::SLIDER_SPRITE_MOVE_MAX;

			return;
		}

		m_settingDatasList[m_settingItemSelectionNum]
			->m_settingSliderPos.x += g_gameTime->GetFrameDeltaTime() * 200.0f;

	}
	else if(g_pad[0]->IsTrigger(enButtonA))
	{

		StateChange(SettingState::en_settingEndFuncBoot);

	}

	SettingValueCalc(m_settingItemSelectionNum);
}

void GameSetting::SettingValueCalc(const int listNo)
{
	//�܂��̓X���C�_�[�̒l��1����0�̒l�ɐ��K�����s��

		//���ݐ��l�擾
	float nowValue = m_settingDatasList[listNo]
		->m_settingSliderPos.x;

	//���K���v�Z�ő�l�ŏ��l�ݒ�
	float normalizeMaxValue = GameSettingConstant::SLIDER_SPRITE_MOVE_MAX;
	float normalizeMinValue = GameSettingConstant::SLIDER_SPRITE_MOVE_MIN;

	//���l����
	if (nowValue > normalizeMaxValue)
		nowValue = normalizeMaxValue;

	if (nowValue < normalizeMinValue)
		nowValue = normalizeMinValue;

	//���K���v�Z
	float normalize = 1.0 - (nowValue + normalizeMinValue) 
		/ (normalizeMinValue - normalizeMaxValue);

	//���`�ۊǌv�Z�ő�l�ŏ��l�ݒ�
	float leapMaxValue = m_settingDatasList[listNo]->GetSettingValueMax();
	float leapMinValue = m_settingDatasList[listNo]->GetSettingValueMin();

	//���`�ۊǂ��g�p���Đ��K�����ꂽ�������琔�l���o��
	float leapValue = Leap(leapMinValue, leapMaxValue, normalize);
	
	float floatFinalValue = 0.0f;
	int	intFinalValue = 0.0f;

	//�f�[�^�ϐ��̐ݒ�l�A�h���X�̕��ɂ���ď�����ύX
	if (m_settingDatasList[listNo]
		->IsSettingAddressIntOrFloat() == true)
	{
		intFinalValue = static_cast<int>(std::round(leapValue));

		m_settingDatasList[listNo]
			->SetSettingValue(intFinalValue);

		m_settingDatasList[listNo]
			->m_settingValueDrawFontInt = intFinalValue;
	}
	else
	{
		floatFinalValue = std::floor(leapValue * 100) / 100;

		m_settingDatasList[listNo]
			->SetSettingValue(floatFinalValue);

		m_settingDatasList[listNo]
			->m_settingValueDrawFontInt = normalize * 100;
	}
}

const bool GameSetting::SettingEndFuncExecute()
{
	bool executeResult 
		= m_settingDatasList[m_settingItemSelectionNum]->FuncExecute();

	return executeResult;
}

void GameSetting::Render(RenderContext& rc)
{
	if (IsSettingSpriteDraw() == false)
		return;

	for (int drawDataNo = 0;
		drawDataNo < GameSettingConstant::MAX_SETTING_SPRITE_DRAW_NUM;
		drawDataNo++)
	{
		if (m_settingDrawDatasList[drawDataNo].m_settingDataAddress
			== nullptr)
			continue;

		m_settingDrawDatasList[drawDataNo].m_settingBar.Draw(rc);

		m_settingDrawDatasList[drawDataNo].m_settingSlider.Draw(rc);

		m_settingDrawDatasList[drawDataNo].m_settingItemNameFontRender.Draw(rc);

		m_settingDrawDatasList[drawDataNo].m_settingValueDrawFont.Draw(rc);

	}

	if (m_nowSettingPageNum > 0)
	{
		m_windowArrowUp.Draw(rc);
	}

	if (m_nowSettingPageNum < m_settingPageNum)
	{
		m_windowArrowDown.Draw(rc);
	}


#ifdef _DEBUG
	if (m_settingItemNum < 0)
		return;

	wchar_t debugFont[256] = {};

	swprintf_s(debugFont, 256, L"settingSlider_X : %.2f", m_settingDatasList[0]->m_settingSliderPos.x);

	m_debugFont.SetText(debugFont);

	m_debugFont.SetPosition({ 0.0f,500.0f,0.0f });

	m_debugFont.Draw(rc);

	m_mouseCursor.Draw(rc);
#endif
}

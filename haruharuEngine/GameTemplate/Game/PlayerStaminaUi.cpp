#include "stdafx.h"
#include "PlayerStaminaUi.h"

//�萔��
namespace {
	//�X�^�~�i�g�̃T�C�YW��H
	static const float STAMINABASE_SPRITE_W_SIZE = 545.0f;
	static const float STAMINABASE_SPRITE_H_SIZE = 157.0f;
	//�X�^�~�i�o�[�̃T�C�YW��H
	static const float STAMINABAR_SPRITE_W_SIZE = 530.0f;
	static const float STAMINABAR_SPRITE_H_SIZE = 142.0f;
	//�X�^�~�i�̈ʒu�A�T�C�Y
	static const Vector3 OXYGENBASE_SPRITE_POSITION = { -0.0f,-350.0f,0.0f };
	static const Vector3 STAMINABASE_SPRITE_SIZE = { 0.2f,0.2f,0.0f };
	//�X�^�~�i�ቺ���C���ƁA��ɂȂ郉�C��
	static const float STAMINA_LOW = 45.0f;
	static const float STAMINA_OUT = 0.0f;
	//�X�^�~�i�o�[�̃A���t�@�l�C�[�W���OA��B
	static const float STAMINABAR_ALPHA_EASING_START = 0.4f;
	static const float STAMINABAR_ALPHA_EASING_END = 0.7f;
}

//�X�^�[�g�֐�
bool PlayerStaminaUi::Start()
{
	//�X�^�~�i�̘g��������
	m_staminaBase.Init("Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gauge_sprite_1.DDS",
		STAMINABASE_SPRITE_W_SIZE,
		STAMINABASE_SPRITE_H_SIZE);
	//�ʒu��ݒ�
	m_staminaBase.SetPosition(OXYGENBASE_SPRITE_POSITION);
	m_staminaBase.Update();

	SpriteInitData staminaBarInitData;
	//�摜��ݒ�
	staminaBarInitData.m_ddsFilePath[0] = "Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gaugebar_sprite_1.DDS";
	//�A���t�@�l����p�̉摜�ݒ�
	m_staminaBarAlphaTexture.InitFromDDSFile(L"Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gaugebar_sprite_2.DDS");
	staminaBarInitData.m_expandShaderResoruceView[0] = &m_staminaBarAlphaTexture;
	staminaBarInitData.m_fxFilePath = "Assets/shader/haruharuStaminaBarSpriteShader.fx";
	//���[�U�[�g���f�[�^��ݒ�
	staminaBarInitData.m_expandConstantBuffer = &m_staminaBarData;
	staminaBarInitData.m_expandConstantBufferSize += sizeof(m_staminaBarData);
	//�䗦��ݒ�
	staminaBarInitData.m_width = static_cast<UINT>(STAMINABAR_SPRITE_W_SIZE);
	staminaBarInitData.m_height = static_cast<UINT>(STAMINABAR_SPRITE_H_SIZE);
	//�u�����h���[�h��ݒ�
	staminaBarInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//�ݒ肵���f�[�^���X�v���C�g�ɐݒ�
	m_staminaBar.Init(staminaBarInitData);
	//�ʒu��ݒ�
	m_staminaBar.SetPosition(OXYGENBASE_SPRITE_POSITION);
	m_staminaBar.Update();

	//m_staminaBar.Init("Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gaugebar_sprite_1.DDS",
	//	STAMINABAR_SPRITE_W_SIZE,
	//	STAMINABAR_SPRITE_H_SIZE);

	return true;
}

//�A�b�v�f�[�g�֐�
void PlayerStaminaUi::Update()
{
	//�v���C���[����X�^�~�i�̒l���󂯎���Ă��Ȃ�������X�V���Ȃ�
	if (m_playerStamina == nullptr)
	{
		return;
	}

	//UI�̃X�^�~�i�l���X�V
	m_mainStamina = *m_playerStamina;
	//�X�^�~�i�̃X�e�[�g���X�V
	StaminaStateUpdate();
	//�X�^�~�i�̓_�ŏ���
	BlinkingBarCalc();
	//�X�^�~�i�o�[�̐��䏈��
	m_staminaBarData.SetDegree(WipeCalc());
	//�X�^�~�i�o�[���X�V
	m_staminaBar.Update();
	//�X�^�~�i�g���X�V
	m_staminaBase.Update();
}

//�X�^�~�i�̃X�e�[�g���X�V����֐�
void PlayerStaminaUi::StaminaStateUpdate()
{
	//�X�^�~�i�̒l���擾
	const float nowStaminaValue = m_mainStamina;

	//�����X�^�~�i���󂾂�����
	if (m_staminaOutFlag == true)
	{
		//�����X�^�~�i��100������������
		if (m_mainStamina < MAX_STAMINA_INDEX)
		{
			//���̌�̏��������Ȃ�
			return;
		}
		//�����X�^�~�i��100�ȏゾ������
		else
		{
			//�X�^�~�i�͋�ł͂Ȃ�
			m_staminaOutFlag = false;
		}
	}

	//�����X�^�~�i��0�ȉ���������
	if (nowStaminaValue <= STAMINA_OUT)
	{
		//�X�e�[�g���X�^�~�i���Ԃ�
		m_staminaState = StaminaUiState::en_staminaOut;
		//�X�^�~�i�͋�ł���
		m_staminaOutFlag = true;
	}
	//�����X�^�~�i��STAMINA_OUT��葽��STAMINA_LOW�ȉ��ł�������
	else if (nowStaminaValue <= STAMINA_LOW
		&& nowStaminaValue > STAMINA_OUT)
	{
		//�X�e�[�g���X�^�~�i�ቺ��Ԃ�
		m_staminaState = StaminaUiState::en_staminaLow;
	}
	//�����X�^�~�i��STAMINA_LOW��葽��MAX_STAMINA_INDEX�ȉ��ł�������
	else if (nowStaminaValue <= MAX_STAMINA_INDEX
		&& nowStaminaValue > STAMINA_LOW)
	{
		//�X�e�[�g���X�^�~�i�ʏ��Ԃ�
		m_staminaState = StaminaUiState::en_staminaHigh;
	}
}

//�X�^�~�i�̓_�Ő���֐�
void PlayerStaminaUi::BlinkingBarCalc()
{
	//�X�^�~�i�X�e�[�g�ɂ���Đ����ω�
	switch (m_staminaState)
	{
		//�X�e�[�g��en_staminaHigh�̏ꍇ
	case PlayerStaminaUi::en_staminaHigh:
		//�A���t�@�l��1.0f�ȉ��ł����
		if (m_staminaBarData.GetAlpha() <= 0.7f)
		{
			//�A���t�@�l��0.1���Z
			m_staminaBarData.AddAlpha(0.1f);

			m_alphaRatio = 0.0f;
		}
		//�o�[�̐F��ʏ�F��
		m_staminaBarData.SetRedAddFlag(false);

		break;
		//�X�e�[�g��en_staminaLow�̏ꍇ
	case PlayerStaminaUi::en_staminaLow:
		//�X�^�~�i��_�ł�����
		m_staminaBarData.SetAlpha(AlphaEasing());
		//�o�[�̐F��ʏ�F��
		m_staminaBarData.SetRedAddFlag(false);

		break;
	case PlayerStaminaUi::en_staminaOut:
		//�X�^�~�i��_�ł�����
		m_staminaBarData.SetAlpha(AlphaEasing());
		//�o�[�̐F��Ԃ�
		m_staminaBarData.SetRedAddFlag(true);

		break;
	default:
		break;
	}

}

//�X�^�~�i�̃��C�v�v�Z�֐�
const float& PlayerStaminaUi::WipeCalc()
{
	float finalValue;

	//�X�^�~�i�̒l�̊����ŃX�^�~�i�o�[�̊����𐧌䂷��v�Z
	finalValue = INIT_DEGREE_VALUE + (m_mainStamina / MAX_STAMINA_INDEX) *
		(MAX_DEGREE_VALUE - INIT_DEGREE_VALUE);

	return finalValue;
}

//�X�^�~�i�̃A���t�@�l�C�[�W���O�֐�
const float& PlayerStaminaUi::AlphaEasing()
{
	//�����A���t�@�l�C�[�W���O������1.0f�ȉ���������
	if (m_alphaRatio >= 1.0f)
	{
		//�A���t�@�l�C�[�W���O������0.0f��
		m_alphaRatio = 0.0f;
	}

	//�C�[�W���O��A��B�̕ϐ�
	float easingStart = 0.0f;
	float easingEnd = 0.0f;

	//�C�[�W���O�����������т�A��B�����ւ���
	if (m_alphaEasingInversionFlag == true)
	{
		easingStart = STAMINABAR_ALPHA_EASING_END;

		easingEnd = STAMINABAR_ALPHA_EASING_START;
	}
	else
	{
		easingStart = STAMINABAR_ALPHA_EASING_START;

		easingEnd = STAMINABAR_ALPHA_EASING_END;
	}

	//�A���t�@�l�C�[�W���O���������Z
	m_alphaRatio += g_gameTime->GetFrameDeltaTime();

	//�A���t�@�l�C�[�W���O������1.0f��葽��������
	if (m_alphaRatio > 1.0f)
	{
		//�A���t�@�l�C�[�W���O������1.0f�ɂ���
		m_alphaRatio = 1.0f;
		//A��B�𔽓]������
		m_alphaEasingInversionFlag = !m_alphaEasingInversionFlag;
	}

	//Leap�Ōv�Z�����l��Ԃ�
	return Leap(easingStart,
		easingEnd,
		m_alphaRatio);
}

//�����_�[�֐�
void PlayerStaminaUi::Render(RenderContext& rc)
{
	m_staminaBar.Draw(rc);

	m_staminaBase.Draw(rc);
}
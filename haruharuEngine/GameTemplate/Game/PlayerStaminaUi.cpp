#include "stdafx.h"
#include "PlayerStaminaUi.h"

//�萔��
namespace {
	static const float STAMINABASE_SPRITE_W_SIZE = 545.0f;
	static const float STAMINABASE_SPRITE_H_SIZE = 157.0f;

	static const float STAMINABAR_SPRITE_W_SIZE = 530.0f;
	static const float STAMINABAR_SPRITE_H_SIZE = 142.0f;

	static const Vector3 STAMINABASE_SPRITE_POSITION = { -0.0f,-350.0f,0.0f };
	static const Vector3 STAMINABASE_SPRITE_SIZE = { 0.2f,0.2f,0.0f };

	static const float STAMINA_LOW = 45.0f;
	static const float STAMINA_OUT = 0.0f;

	static const float STAMINABAR_ALPHA_EASING_START = 0.0f;
	static const float STAMINABAR_ALPHA_EASING_END = 1.0f;
}

//�X�^�[�g�֐�
bool PlayerStaminaUi::Start()
{

	m_staminaBase.Init("Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gauge_sprite_1.DDS",
		STAMINABASE_SPRITE_W_SIZE,
		STAMINABASE_SPRITE_H_SIZE);

	m_staminaBase.SetPosition(STAMINABASE_SPRITE_POSITION);

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

	m_staminaBar.SetPosition(STAMINABASE_SPRITE_POSITION);
	m_staminaBar.Update();

	//m_staminaBar.Init("Assets/modelData/playerUI/PlayerStaminaUi/digital_stamina_gaugebar_sprite_1.DDS",
	//	STAMINABAR_SPRITE_W_SIZE,
	//	STAMINABAR_SPRITE_H_SIZE);

	return true;
}

//�A�b�v�f�[�g�֐�
void PlayerStaminaUi::Update()
{
	if (m_playerStamina == nullptr)
	{
		return;
	}

	//UI�̃X�^�~�i�l���X�V
	m_mainStamina = *m_playerStamina;

	StaminaStateUpdate();

	BlinkingBarCalc();

	m_staminaBarData.SetDegree(WipeCalc());

	m_staminaBar.Update();

	m_staminaBase.Update();
}

//�X�^�~�i�̃X�e�[�g���X�V����֐�
void PlayerStaminaUi::StaminaStateUpdate()
{
	const float nowStaminaValue = m_mainStamina;

	if (m_staminaOutFlag == true)
	{
		if (m_mainStamina < MAX_STAMINA_INDEX)
		{
			return;
		}
		else
		{
			m_staminaOutFlag = false;
		}
	}

	if (nowStaminaValue <= STAMINA_OUT)
	{
		m_staminaState = StaminaUiState::en_staminaOut;

		m_staminaOutFlag = true;
	}
	else if (nowStaminaValue <= STAMINA_LOW
		&& nowStaminaValue > STAMINA_OUT)
	{
		m_staminaState = StaminaUiState::en_staminaLow;
	}
	else if (nowStaminaValue <= MAX_STAMINA_INDEX
		&& nowStaminaValue > STAMINA_LOW)
	{
		m_staminaState = StaminaUiState::en_staminaHigh;
	}
}

//�X�^�~�i�̓_�Ő���֐�
void PlayerStaminaUi::BlinkingBarCalc()
{

	switch (m_staminaState)
	{
	case PlayerStaminaUi::en_staminaHigh:

		if (m_staminaBarData.GetAlpha() <= 1.0f)
		{
			m_staminaBarData.AddAlpha(0.1f);
		}

		m_staminaBarData.SetRedAddFlag(false);

		break;
	case PlayerStaminaUi::en_staminaLow:

		m_staminaBarData.SetAlpha(AlphaEasing());

		m_staminaBarData.SetRedAddFlag(false);

		break;
	case PlayerStaminaUi::en_staminaOut:

		m_staminaBarData.SetAlpha(AlphaEasing());

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

	finalValue = INIT_DEGREE_VALUE + (m_mainStamina / MAX_STAMINA_INDEX) *
		(MAX_DEGREE_VALUE - INIT_DEGREE_VALUE);

	return finalValue;
}

//�X�^�~�i�̃A���t�@�l�C�[�W���O�֐�
const float& PlayerStaminaUi::AlphaEasing()
{
	if (m_alphaRatio >= 1.0f)
	{
		m_alphaRatio = 0.0f;
	}

	float easingStart = 0.0f;
	float easingEnd = 0.0f;

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

	m_alphaRatio += g_gameTime->GetFrameDeltaTime() * 2;

	if (m_alphaRatio > 1.0f)
	{
		m_alphaRatio = 1.0f;

		m_alphaEasingInversionFlag = !m_alphaEasingInversionFlag;
	}

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
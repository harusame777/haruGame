#include "stdafx.h"
#include "PlayerOxygenUi.h"
#include "Game.h"

//�萔��
namespace {
	//�_�f�g�̃T�C�YW��H
	static const float OXYGENBASE_SPRITE_W_SIZE = 141.0f;
	static const float OXYGENBASE_SPRITE_H_SIZE = 281.0f;
	//�_�f�o�[�̃T�C�YW��H
	static const float OXYGENGAUGE_SPRITE_W_SIZE = 126.0f;
	static const float OXYGENGAUGE_SPRITE_H_SIZE = 266.0f;
	//�_�fUi�̈ʒu�A�T�C�Y
	static const Vector3 OXYGENBASE_SPRITE_POSITION = { 720.0f,300.0f,0.0f };

	static const float OXYGEN_LOW_LINE = 150.0f;
	static const float OXYGEN_MIN_LINE = 60.0f;

	static const float MAX_WIPE_INDEX = 20.0f;
	static const float MIN_WIPE_INDEX = 280.0f;

	static const float OXYGENGAUGE_ALPHA_EASING_MAX = 0.7f;
	static const float OXYGENGAUGE_ALPHA_EASING_MIN = 0.3f;
}

//�X�^�[�g�֐�
bool PlayerOxygenUi::Start()
{

	m_oxygenUiBase.Init("Assets/modelData/playerUI/PlayerOxygenUi/digital_oxygen_sprite_2.DDS",
		OXYGENBASE_SPRITE_W_SIZE,
		OXYGENBASE_SPRITE_H_SIZE);

	m_oxygenUiBase.SetPosition(OXYGENBASE_SPRITE_POSITION);

	m_oxygenUiBase.Update();

	SpriteInitData oxygenGaugeUiInitData;

	//�摜��ݒ�
	oxygenGaugeUiInitData.m_ddsFilePath[0] = "Assets/modelData/playerUI/PlayerOxygenUi/digital_oxygengauge_sprite_1.DDS";
	//�A���t�@�l����p�̉摜�ݒ�
	m_m_oxygenGaugeAlphaTexture.InitFromDDSFile(L"Assets/modelData/playerUI/PlayerOxygenUi/digital_oxygengauge_sprite_2.DDS");
	oxygenGaugeUiInitData.m_expandShaderResoruceView[0] = &m_m_oxygenGaugeAlphaTexture;
	//�V�F�[�_�[�t�@�C����ݒ�
	oxygenGaugeUiInitData.m_fxFilePath = "Assets/shader/haruharuOxygenGaugeSpriteShader.fx";
	//���[�U�[�g���f�[�^��ݒ�
	oxygenGaugeUiInitData.m_expandConstantBuffer = &m_oxygenGaugeSpriteData;
	oxygenGaugeUiInitData.m_expandConstantBufferSize = sizeof(m_oxygenGaugeSpriteData);
	//�䗦��ݒ�
	oxygenGaugeUiInitData.m_width = static_cast<UINT>(OXYGENGAUGE_SPRITE_W_SIZE);
	oxygenGaugeUiInitData.m_height = static_cast<UINT>(OXYGENGAUGE_SPRITE_H_SIZE);
	//�u�����h���[�h��ݒ�
	oxygenGaugeUiInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//�ݒ肵���f�[�^���X�v���C�g�ɐݒ�
	m_oxygenUiGauge.Init(oxygenGaugeUiInitData);

	m_oxygenUiGauge.SetPosition(OXYGENBASE_SPRITE_POSITION);

	m_oxygenUiGauge.Update();

	m_oxygenGaugeSpriteData.SetDirction({ 0.0f, 1.0f});

	m_game = FindGO<Game>("game");

	return true;
}

//�A�b�v�f�[�g�֐�
void PlayerOxygenUi::Update()
{
	if (m_gameTimer == nullptr)
	{
		return;
	}

	//Ui���̎c�莞�Ԃ��X�V
	m_mainOxygenIndex = *m_gameTimer;
	//�_�f�Q�[�W�̃X�e�[�g���X�V
	m_oxygenGaugeState = OxygenGaugeStateUpdate();
	//�_�f�Q�[�W�̓_�ŏ��������s
	BlinkingOxygenGaugeCalc();
	//���C�v�X�V
	m_oxygenGaugeSpriteData.SetDegree(WipeCalc());

#ifdef _DEBUG
	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"%06.1ftime",float(m_mainOxygenIndex));

	m_debugFontRender.SetText(wcsbuf);
#endif

	m_oxygenUiBase.Update();

	m_oxygenUiGauge.Update();
}

const PlayerOxygenUi::OxygenGaugeState& PlayerOxygenUi::OxygenGaugeStateUpdate()
{
	const float nowGameTimer = m_mainOxygenIndex;

	if (m_mainOxygenIndex <= OXYGEN_MIN_LINE) 
		return OxygenGaugeState::en_oxygenMin;

	if (m_mainOxygenIndex > OXYGEN_MIN_LINE &&
		m_mainOxygenIndex <= OXYGEN_LOW_LINE)
		return OxygenGaugeState::en_oxygenLow;

	if (m_mainOxygenIndex > OXYGEN_LOW_LINE &&
		m_mainOxygenIndex <= MAX_GAMETIME)
		return OxygenGaugeState::en_oxygenHigh;
}

void PlayerOxygenUi::BlinkingOxygenGaugeCalc()
{
	switch (m_oxygenGaugeState)
	{
	case PlayerOxygenUi::en_oxygenHigh:

		//�A���t�@�l��1.0f�ȉ��ł����
		if (m_oxygenGaugeSpriteData.GetAlpha() <= OXYGENGAUGE_ALPHA_EASING_MAX)
		{
			//�A���t�@�l��0.1���Z
			m_oxygenGaugeSpriteData.AddAlpha(0.1f);

			m_alphaRatio = 0.0f;
		}

		m_oxygenGaugeSpriteData.SetColorState(m_oxygenGaugeState);

		break;
	case PlayerOxygenUi::en_oxygenLow:

		m_oxygenGaugeSpriteData.SetAlpha(AlphaEasing(0.5));

		m_oxygenGaugeSpriteData.SetColorState(m_oxygenGaugeState);

		break;
	case PlayerOxygenUi::en_oxygenMin:

		m_oxygenGaugeSpriteData.SetAlpha(AlphaEasing(3));

		m_oxygenGaugeSpriteData.SetColorState(m_oxygenGaugeState);

		break;
	default:
		break;
	}
}

const float& PlayerOxygenUi::WipeCalc()
{
	float finalValue;

	finalValue = MIN_WIPE_INDEX + (m_mainOxygenIndex / MAX_GAMETIME) *
		(MAX_WIPE_INDEX - MIN_WIPE_INDEX);

	return finalValue;
}

//�X�^�~�i�̃A���t�@�l�C�[�W���O�֐�
const float& PlayerOxygenUi::AlphaEasing(const float& speed)
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
		easingStart = OXYGENGAUGE_ALPHA_EASING_MIN;

		easingEnd = OXYGENGAUGE_ALPHA_EASING_MAX;
	}
	else
	{
		easingStart = OXYGENGAUGE_ALPHA_EASING_MAX;

		easingEnd = OXYGENGAUGE_ALPHA_EASING_MIN;
	}

	//�A���t�@�l�C�[�W���O���������Z
	m_alphaRatio += g_gameTime->GetFrameDeltaTime() * speed;

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
void PlayerOxygenUi::Render(RenderContext& rc)
{
	m_oxygenUiGauge.Draw(rc);

	m_oxygenUiBase.Draw(rc);

#ifdef _DEBUG
	m_debugFontRender.Draw(rc);
#endif
}
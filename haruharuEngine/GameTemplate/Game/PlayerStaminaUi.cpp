#include "stdafx.h"
#include "PlayerStaminaUi.h"

//�萔��
namespace {
	static const float STAMINABASE_SPRITE_W_SIZE = 545.0f;
	static const float STAMINABASE_SPRITE_H_SIZE = 157.0f;

	static const Vector3 STAMINABASE_SPRITE_POSITION = { -0.0f,-350.0f,0.0f };
	static const Vector3 STAMINABASE_SPRITE_SIZE = { 0.2f,0.2f,0.0f };
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
	//�V�F�[�_�[�t�@�C����ݒ�
	staminaBarInitData.m_fxFilePath = "Assets/shader/haruharuWipeSprite.fx";
	//���[�U�[�g���f�[�^��ݒ�
	staminaBarInitData.m_expandConstantBuffer = &m_staminaBarData;
	staminaBarInitData.m_expandConstantBufferSize = sizeof(m_staminaBarData);
	//�䗦��ݒ�
	staminaBarInitData.m_width = static_cast<UINT>(STAMINABASE_SPRITE_W_SIZE);
	staminaBarInitData.m_height = static_cast<UINT>(STAMINABASE_SPRITE_H_SIZE);
	//�u�����h���[�h��ݒ�
	staminaBarInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//�ݒ肵���f�[�^���X�v���C�g�ɐݒ�
	m_staminaBar.Init(staminaBarInitData);

	m_staminaBar.SetPosition(STAMINABASE_SPRITE_POSITION);

	return true;
}

//�A�b�v�f�[�g�֐�
void PlayerStaminaUi::Update()
{
	m_staminaBar.Update();

	m_staminaBase.Update();
}

//�����_�[�֐�
void PlayerStaminaUi::Render(RenderContext& rc)
{
	m_staminaBar.Draw(rc);

	m_staminaBase.Draw(rc);
}
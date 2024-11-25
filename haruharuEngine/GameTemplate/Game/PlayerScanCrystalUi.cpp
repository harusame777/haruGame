#include "stdafx.h"
#include "PlayerScanCrystalUi.h"
#include "Player.h"

//�萔��
namespace {
	/// <summary>
	/// �������X�v���C�g�T�C�Y
	/// </summary>
	static const float SCANLINE_SPRITE_W_SIZE = 1600.0f;
	static const float SCANLINE_SPRITE_H_SIZE = 900.0f;

	static const float SCANLINE_ALPHA_EASING_START = 0.0f;
	static const float SCANLINE_ALPHA_EASING_END = 0.5f;

	static const float SCANLINE_WIPE_START = 450.0f;
	static const float SCANLINE_WIPE_END = -450.0f;
}

//�X�^�[�g�֐�
bool PlayerScanCrystalUi::Start()
{
	SpriteInitData scanLineSpriteInitData;

	//�摜��ݒ�
	scanLineSpriteInitData.m_ddsFilePath[0] = "Assets/modelData/playerUI/PlayerScanCrystalUi/scanline_sprite.DDS";
	//�V�F�[�_�[�t�@�C����ݒ�
	scanLineSpriteInitData.m_fxFilePath = "Assets/shader/haruharuWipeSprite.fx";
	//���[�U�[�g���f�[�^��ݒ�
	scanLineSpriteInitData.m_expandConstantBuffer = &m_scanLineData;
	scanLineSpriteInitData.m_expandConstantBufferSize = sizeof(m_scanLineData);
	//�䗦��ݒ�
	scanLineSpriteInitData.m_width = static_cast<UINT>(SCANLINE_SPRITE_W_SIZE);
	scanLineSpriteInitData.m_height = static_cast<UINT>(SCANLINE_SPRITE_H_SIZE);
	//�u�����h���[�h��ݒ�
	scanLineSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	//�ݒ肵���f�[�^���X�v���C�g�ɐݒ�
	m_scanlineSprite.Init(scanLineSpriteInitData);

	m_scanlineSprite.SetPosition({ 0.0f,0.0f,0.0f });

	m_scanLineData.m_wipeDir.Set(0.0f,1.0f);

	return true;
}

//�A�b�v�f�[�g�֐�
void PlayerScanCrystalUi::Update()
{
	//�����X�L�����t���O��true��������
	if (m_scanFlag == true)
	{
		//�X�v���C�g���X�V����
		SpriteUpdate();

		//�X�v���C�g�X�V
		m_scanlineSprite.Update();
	}

	//����RT�{�^����������Ă���
	//�X�L�����t���O��false��������
	if (g_pad[0]->IsTrigger(enButtonRB2) 
		&& m_scanFlag == false)
	{
		//�X�L�������J�n����
		ScanStart();
	}
}

void PlayerScanCrystalUi::SpriteUpdate()
{

	//�X�e�[�g�ŕ��򂳂���
	switch (m_scanState)
	{
		//���݂��ҋ@��Ԃ�������
	case PlayerScanCrystalUi::en_scanStandby:
		//�������Ȃ�
		break;
		//���݂��A���t�@�l�C�[�W���O��������
	case PlayerScanCrystalUi::en_scanAEasing:
		//�摜�̃A���t�@�l�𑀍삷��
		m_scanLineData.m_paramA = AlphaEasing();
		break;
		//���݂��摜�C�[�W���O��������
	case PlayerScanCrystalUi::en_scanLineEasing:
		//�摜�����C�v����
		m_scanLineData.m_wipeSize = WipeEasing();
		break;
		//���݂��}�[�J�[�h���[��������
	case PlayerScanCrystalUi::en_scanMarkerDraw:
		//�}�[�J�[��`�悷��
		break;
	default:
		break;
	}

}

//�A���t�@�l�C�[�W���O�֐�
const float PlayerScanCrystalUi::AlphaEasing()
{
	float finalEasing;

	m_alphaRatio -= g_gameTime->GetFrameDeltaTime() / 2;

	if (m_alphaRatio <= 0.0f)
	{
		//����������
		m_alphaRatio = 1.0f;
		//�X�e�[�g��ύX
		m_scanState = ScanState::en_scanLineEasing;

	}

	return finalEasing = Leap(SCANLINE_ALPHA_EASING_START
		, SCANLINE_ALPHA_EASING_END, m_alphaRatio);
}

//���C�v�C�[�W���O�֐�
const float PlayerScanCrystalUi::WipeEasing()
{
	float finalEasing;

	m_wipeRatio -= g_gameTime->GetFrameDeltaTime() / 2;

	if (m_wipeRatio <= 0.0f)
	{
		//���������āc
		m_wipeRatio = 1.0f;
		//�X�e�[�g��ύX
		m_scanState = ScanState::en_scanMarkerDraw;
	}

	return finalEasing = Leap(SCANLINE_WIPE_START
		, SCANLINE_WIPE_END, m_wipeRatio);
}

//�h���[�֐�
void PlayerScanCrystalUi::Render(RenderContext& rc)
{
	if (m_scanFlag == true)
	{
		m_scanlineSprite.Draw(rc);
	}
}
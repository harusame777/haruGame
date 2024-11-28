#include "stdafx.h"
#include "PlayerScanCrystalUi.h"
#include "Player.h"
//�����ꂪ�֗��߂��Ă炽��
#include "EnemyAIConWaitTime.h"

//�萔��
namespace {
	/// <summary>
	/// �������X�v���C�g�T�C�Y
	/// </summary>
	static const float SCANLINE_SPRITE_W_SIZE = 1600.0f;
	static const float SCANLINE_SPRITE_H_SIZE = 900.0f;

	static const float INFOMATION_SPRITE_W_SIZE = 400.0f;
	static const float INFOMATION_SPRITE_H_SIZE = 225.0f;

	static const float SCANLINE_ALPHA_EASING_START = 0.3f;
	static const float SCANLINE_ALPHA_EASING_END = 0.5f;

	static const float SCANLINE_WIPE_START = 0.0f;
	static const float SCANLINE_WIPE_END = -900.0f;
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
	
	m_scanLineData.m_wipeDir.Set(0.0f,-1.0f);

	InitInfomationDatas();

	m_waitTime2s = new EnemyAIConWaitTime(2.0f);

	m_waitTime2s->InitData();

	m_waitTime5s = new EnemyAIConWaitTime(5.0f);

	m_waitTime5s->InitData();

	return true;
}

//�C���t�H���[�V�����̃f�[�^�̏������֐�
void PlayerScanCrystalUi::InitInfomationDatas()
{
	//�z��Ԃ��
	for (auto& ptr : m_infoDatas)
	{
		//�X�v���C�g�̃f�[�^���쐬
		
		SpriteInitData infoSpriteInitData;

		//�摜��ݒ�
		infoSpriteInitData.m_ddsFilePath[0] = "Assets/modelData/playerUI/PlayerScanCrystalUi/digital_infomation_sprite_1.DDS";
		//�V�F�[�_�[�t�@�C����ݒ�
		infoSpriteInitData.m_fxFilePath = "Assets/shader/haruharuWipeSprite.fx";
		//���[�U�[�g���f�[�^��ݒ�
		infoSpriteInitData.m_expandConstantBuffer = &ptr.m_easingData;
		infoSpriteInitData.m_expandConstantBufferSize = sizeof(ptr.m_easingData);
		//�䗦��ݒ�
		infoSpriteInitData.m_width = static_cast<UINT>(INFOMATION_SPRITE_W_SIZE);
		infoSpriteInitData.m_height = static_cast<UINT>(INFOMATION_SPRITE_H_SIZE);
		//�u�����h���[�h��ݒ�
		infoSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

		ptr.m_infoPtr.Init(infoSpriteInitData);

		//�`�悵�Ȃ��ݒ��
		ptr.SetIsDraw(false);

	}

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

		for (auto& ptr : m_infoDatas)
		{
			if (ptr.GetIsDraw() == true)
				ptr.m_infoPtr.Update();
		}
	
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
		//�ҋ@��Ԃ������牽�����Ȃ�
	case PlayerScanCrystalUi::en_scanStandby:
		break;
		//���������C�[�W���O����
	case PlayerScanCrystalUi::en_scanLineEasing:

		m_scanLineData.m_wipeSize = WipeEasing();

		break;
		//�������𓧖��ɂ���
	case PlayerScanCrystalUi::en_scanAEasing:

		m_scanLineData.m_paramA = AlphaEasingWeakBlinking();

		if (m_waitTime2s->Execution())
		{
			m_scanLineData.m_paramA = 0.3;

			m_waitTime5s->InitData();

			m_scanState = ScanState::en_scanMarkerDraw;
		}

		break;
		//�}�[�J�[��`�悷��
	case PlayerScanCrystalUi::en_scanMarkerDraw:

		for (auto& ptr : m_infoDatas)
		{
			if (AngleCheck())
			{

			}	
		}

		if (m_waitTime5s->Execution())
		{

		}

		break;
	default:
		break;
	}

}

//�A���t�@�l�C�[�W���O�֐�
const float PlayerScanCrystalUi::AlphaEasingWeakBlinking()
{
	float finalEasing;

	if (m_swapEasing == true)
	{
		m_alphaRatio += g_gameTime->GetFrameDeltaTime() / 2;
	}
	else
	{
		m_alphaRatio += g_gameTime->GetFrameDeltaTime() / 2;
	}

	if (m_alphaRatio > 1.0f)
	{
		//����������
		m_alphaRatio = 0.0f;

		m_waitTime2s->InitData();
		
		m_swapEasing = !m_swapEasing;
	}

	if (m_swapEasing == true)
	{
		return finalEasing = Leap(SCANLINE_ALPHA_EASING_START
			, SCANLINE_ALPHA_EASING_END, m_alphaRatio);
	}
	else
	{
		return finalEasing = Leap(SCANLINE_ALPHA_EASING_END
			, SCANLINE_ALPHA_EASING_START, m_alphaRatio);
	}
}

//���C�v�C�[�W���O�֐�
const float PlayerScanCrystalUi::WipeEasing()
{
	float finalEasing;

	m_wipeRatio += g_gameTime->GetFrameDeltaTime() / 2;

	if (m_wipeRatio > 1.0f)
	{
		//���������āc
		m_wipeRatio = 1.0f;
		//�X�e�[�g��ύX
		m_scanState = ScanState::en_scanAEasing;
	}

	return finalEasing = Leap(SCANLINE_WIPE_START
		, SCANLINE_WIPE_END, m_wipeRatio);
}

//�v���C���[�̃J�������ɂ��邩�ǂ����𒲂ׂ�֐�
const bool PlayerScanCrystalUi::AngleCheck()
{


	return false;
}

//�h���[�֐�
void PlayerScanCrystalUi::Render(RenderContext& rc)
{
	if (m_scanFlag == true)
	{
		m_scanlineSprite.Draw(rc);
	}

}
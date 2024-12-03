#include "stdafx.h"
#include "PlayerScanCrystalUi.h"
#include "Player.h"
#include "ManagerCrystal.h"
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

	static const float SCANINFO_EASING_START = 0.0f;
	static const float SCANINFO_EASING_END = -1600.0f;
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

	m_managerCrystal = FindGO<ManagerCrystal>("CrystalMetaAI");

	m_crystalDataHolder = m_managerCrystal->GetCrystalDataHolder();

	InitInfomationDatas();

	m_playerPtr = FindGO<Player>("player");

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
	for (int infoNum = 0; infoNum < MAX_CRYSTAL_NUM; infoNum++)
	{
		//�X�v���C�g�̃f�[�^���쐬

		SpriteInitData infoSpriteInitData;

		//�摜��ݒ�
		infoSpriteInitData.m_ddsFilePath[0] = "Assets/modelData/playerUI/PlayerScanCrystalUi/digital_infomation_sprite_1.DDS";
		//�V�F�[�_�[�t�@�C����ݒ�
		infoSpriteInitData.m_fxFilePath = "Assets/shader/haruharuWipeSpriteMoveVer.fx";
		//���[�U�[�g���f�[�^��ݒ�
		infoSpriteInitData.m_expandConstantBuffer = &m_infoDatas[infoNum].m_easingData;
		infoSpriteInitData.m_expandConstantBufferSize = sizeof(m_infoDatas[infoNum].m_easingData);
		//�䗦��ݒ�
		infoSpriteInitData.m_width = static_cast<UINT>(INFOMATION_SPRITE_W_SIZE);
		infoSpriteInitData.m_height = static_cast<UINT>(INFOMATION_SPRITE_H_SIZE);
		//�u�����h���[�h��ݒ�
		infoSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

		m_infoDatas[infoNum].m_infoPtr.Init(infoSpriteInitData);

		m_infoDatas[infoNum].m_easingData.m_wipeDir.Set(-1.0f, 0.0);

		m_infoDatas[infoNum].m_infoPtr.SetPivot({0.0f, 0.0f});

		m_infoDatas[infoNum].m_infoPtr.SetScale({0.5f,0.5f,1.0f});

		m_infoDatas[infoNum].m_easingData.m_wipeSize = 0.0f;

		//�`�悵�Ȃ��ݒ��
		m_infoDatas[infoNum].SetIsDraw(false);

		m_infoDatas[infoNum].SetCrystalData(m_crystalDataHolder->GetCrystalDataHolder(infoNum));

	}

}

//�A�b�v�f�[�g�֐�
void PlayerScanCrystalUi::Update()
{
	//�����X�L�����t���O��true��������
	if (m_scanState != ScanState::en_scanStandby)
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
		&& m_scanState == ScanState::en_scanStandby)
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

		for (int infoNum = 0; infoNum < MAX_CRYSTAL_NUM; infoNum++)
		{
			if (AngleCheck(infoNum) 
				&& m_infoDatas[infoNum].GetCrystalData()->GetCollected() == false)
			{
				m_infoDatas[infoNum].SetIsDraw(true);

				m_infoDatas[infoNum].m_easingData.m_wipeSize = InfoWipeEasing(infoNum);

				SetInfoSpritePosition(infoNum);

				m_infoDatas[infoNum].m_infoPtr.Update();
			}	
			else
			{
				m_infoDatas[infoNum].SetIsDraw(false);
			}
		}

		if (m_scanLineData.m_paramA >= 0.0f)
		{
			m_scanLineData.m_paramA -= 0.05f;
		}

		if (m_waitTime5s->Execution())
		{
			for (int infoNum = 0; infoNum < MAX_CRYSTAL_NUM; infoNum++)
			{
				m_infoDatas[infoNum].SetIsDraw(false);
			}

			m_scanState = ScanState::en_scanStandby;
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

const float PlayerScanCrystalUi::InfoWipeEasing(const int infoNo)
{
	float finalEasing;

	float finalWipeRatio = m_infoDatas[infoNo].GetInfoWipeRatio();

	m_infoDatas[infoNo].SetInfoWipeRatio(finalWipeRatio
		+= g_gameTime->GetFrameDeltaTime());

	if (m_infoDatas[infoNo].GetInfoWipeRatio() > 1.0f)
	{
		//����������
		m_infoDatas[infoNo].SetInfoWipeRatio(1.0f);
	}

	return finalEasing = Leap(SCANINFO_EASING_START,
		SCANINFO_EASING_END, m_infoDatas[infoNo].GetInfoWipeRatio());
}

void PlayerScanCrystalUi::SetInfoSpritePosition(const int infoNum)
{
	Vector2 spritePos;

	Vector3 crystalPos;

	crystalPos = m_infoDatas[infoNum].GetCrystalData()->GetPosition();

	g_camera3D->CalcScreenPositionFromWorldPosition(spritePos, crystalPos);

	m_infoDatas[infoNum].m_infoPtr.SetPosition({spritePos.x,spritePos.y,0.0f});
}

//�v���C���[�̃J�������ɂ��邩�ǂ����𒲂ׂ�֐�
const bool PlayerScanCrystalUi::AngleCheck(const int infoNum)
{
	//�G�l�~�[����v���C���[�Ɍ������x�N�g�����v�Z
	Vector3 diff = m_infoDatas[infoNum].GetCrystalData()->GetPosition() - m_playerPtr->GetPosition();

	//�G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K��
	diff.Normalize();
	//�G�l�~�[�̐��ʃx�N�g���ƁA�G����v���C���[�Ɍ������x�N�g����
	//����(cos��)�����߂�B
	float cos = g_camera3D->GetForward().Dot(diff);
	if (cos >= 1)
	{
		cos = 1.0f;
	}
	//����(cos��)����p�x(��)�����߂�
	float angle = acosf(cos);
	//�p�x(��)��90��(����p)��菬�������
	if (angle <= (Math::PI / 180.0f) * 90.f)
	{
		//���������I
		return true;
	}

	return false;
}

//�h���[�֐�
void PlayerScanCrystalUi::Render(RenderContext& rc)
{
	if (m_scanFlag == true)
	{
		m_scanlineSprite.Draw(rc);
	}

	for (int infoNum = 0; infoNum < MAX_CRYSTAL_NUM; infoNum++)
	{
		if (m_infoDatas[infoNum].GetIsDraw() == true)
		{
			m_infoDatas[infoNum].m_infoPtr.Draw(rc);
		}
	}

}
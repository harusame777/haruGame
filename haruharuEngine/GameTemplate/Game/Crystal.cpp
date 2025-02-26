#include "stdafx.h"
#include "Crystal.h"
#include "Player.h"
#include "CrystalGetCommandSprite.h"
#include "ManagerCrystal.h"
#include "PlayerScoreUi.h"

//�N���X�^�����̎悷��Ƃ��ɃN���X�^���ɃJ�����������Ȃ��ƍ̎�ł��Ȃ��悤�ɂ�����
//
//1.�N���X�^������A�J�����ɐL�т�x�N�g��A�����
//
//2.�x�N�g��A�𐳋K������
//
//3.�J�����̐��ʃx�N�g�����擾����
//
//4.�x�N�g��A�ƃJ�����̐��ʒl�̓��ς��v�Z���āA�x�N�g��A�ƃJ�����̐��ʃx�N�g����
//�ǂꂾ�����Ă��邩(������)�𒲂ׂ�
//
//5.���l�����ȉ���������̎�ł���悤�ɂ���

//�萔��
namespace {
	/// <summary>
	/// �擾�����̌v�Z�Ɏg�����
	/// </summary>
	static const float GET_RANGE_CALC = 90.0f;
	/// <summary>
	/// �C���l�P
	/// </summary>
	static const Vector3 CORRE_POSITION = { 0.0f,-60.0f,0.0f };
	/// <summary>
	/// �f�o�b�O�̃t�H���g�̈ʒu
	/// </summary>
	static const Vector3 DEBUG_FONT_POSITION = { 0.0f,100.0f,0.0f };
}

//�R���X�g���N�^
Crystal::Crystal()
{

}

//�f�X�g���N�^
Crystal::~Crystal()
{

}

//�X�^�[�g�֐�
bool Crystal::Start()
{

	//�N���X�^��01�����f���ɐݒ�
	m_crystal_M_Model.Init("Assets/modelData/objects/crystal/crystal01_Model.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_crystalShader);

	m_crystal_R_Model.Init("Assets/modelData/objects/crystal/crystal01_Model_R.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_crystalShader);

	m_crystal_Y_Model.Init("Assets/modelData/objects/crystal/crystal01_Model_Y.tkm", nullptr, 0, enModelUpAxisZ, ModelRender::en_crystalShader);

	m_managerCrystalPtr = FindGO<ManagerCrystal>("CrystalMetaAI");

	//�V���h�E�}�b�v�ɕ`�悷��悤�ɂ���
	m_crystal_M_Model.SetShadowChasterFlag(true);
	m_crystal_R_Model.SetShadowChasterFlag(true);
	m_crystal_Y_Model.SetShadowChasterFlag(true);

	//���W��ݒ�
	m_crystal_M_Model.SetPosition(m_position);
	m_crystal_R_Model.SetPosition(m_position);
	m_crystal_Y_Model.SetPosition(m_position);
	//��]��ݒ�
	m_crystal_M_Model.SetRotation(m_rotation);
	m_crystal_R_Model.SetRotation(m_rotation);
	m_crystal_Y_Model.SetRotation(m_rotation);
	//�g�嗦��ݒ�
	m_crystal_M_Model.SetScale(m_scale);
	m_crystal_R_Model.SetScale(m_scale);
	m_crystal_Y_Model.SetScale(m_scale);
	//�����ݒ���m��
	m_crystal_M_Model.Update();
	m_crystal_R_Model.Update();
	m_crystal_Y_Model.Update();

	//�v���C���[�̃C���X�^���X���擾����
	m_player = FindGO<Player>("player");

	m_scoreUi = FindGO<PlayerScoreUi>("ScoreUI");

	//�N���X�^���̎擾�R�}���h�\���v���O�����̃C���X�^���X���擾����
	m_GetCOMSprite = FindGO<CrystalGetCommandSprite>("comSprite");

	InitBootObject("Assets/modelData/objects/crystal/crystalBootPos.tkl");

	//�R���C�_�[������������
	m_sphereCollider.Create(1.0f);

	return true;
}

//�A�b�v�f�[�g�֐�
void Crystal::Update()
{
	//�N���X�^���擾����
	GetCrystal();
	//���W��ݒ�
	m_crystal_M_Model.SetPosition(m_position);
	m_crystal_R_Model.SetPosition(m_position);
	m_crystal_Y_Model.SetPosition(m_position);
	//��]��ݒ�
	m_crystal_M_Model.SetRotation(m_rotation);
	m_crystal_R_Model.SetRotation(m_rotation);
	m_crystal_Y_Model.SetRotation(m_rotation);
	if (m_GetCOMSprite->GetCollectFlag() == false)
	{
		UpdateBootData();
	}
	//�`��X�V
	m_crystal_M_Model.Update();
	m_crystal_R_Model.Update();
	m_crystal_Y_Model.Update();
}

//�����_�[�֐�
void Crystal::Render(RenderContext& rc)
{
	//�擾����Ă��Ȃ�������
	if (!m_isGetObject)
	{
		//�`�悷��
		switch (m_crystalColorState)
		{
		case Crystal::en_crystal_M:

			m_crystal_M_Model.Draw(rc);

			break;
		case Crystal::en_crystal_R:

			m_crystal_R_Model.Draw(rc);

			break;
		case Crystal::en_crystal_Y:

			m_crystal_Y_Model.Draw(rc);

			break;
		default:
			break;
		}
	}

#ifdef _DEBUG
	m_debugFontRender.Draw(rc);
#endif
}

//�N���X�^�����擾�ł��邩�ǂ������肷��֐�
const bool Crystal::IsLookCrystal()
{
	//�J�����̐��ʃx�N�g�����擾
	Vector3 camForward = g_camera3D->GetForward();

	//�v���C���[�̍��W���擾
	Vector3 playerPos = m_player->GetPosition();

	//�v���C���[�̍��W���玩�g�̍��W��������
	//���g����v���C���[�֐L�т�x�N�g�����v�Z����
	Vector3 diff = playerPos - (m_position + CORRE_POSITION);

	//���K�����ĒP�ʃx�N�g���ɂ���
	diff.Normalize();

	//���ς��v�Z���A�������𑪂�
	float similarity = Dot(camForward, diff);

	//����-0.95������������������������
	if (similarity <= -0.95)
	{
		//true��Ԃ�
		return true;
	}

	return false;
}

const bool Crystal::IsInGetRange()
{
	//�v���C���[�̍��W���擾
	Vector3 playerPos = m_player->GetPosition();

	//�v���C���[�̍��W���玩�g�̍��W��������
	//���g����v���C���[�֐L�т�x�N�g�����v�Z����
	Vector3 diff = playerPos - m_position;

	//���g����v���C���[�֐L�т�x�N�g���̂Q����v�Z����
	float range = diff.LengthSq();
	
	//�����擾�͈͓���������
	if (range <= GET_RANGE_CALC * GET_RANGE_CALC)
	{
		//true��Ԃ�
		return true;
	}

	return false;
}

void Crystal::GetCrystal()
{
	if (m_collectCoolTime <= 0.0f)
	{
		m_collectCoolTime = 0.0f;
	}
	else
	{
		m_collectCoolTime -= g_gameTime->GetFrameDeltaTime();
		return;
	}

	if (m_GetCOMSprite->GetCollectFlag() == true)
	{
		return;
	}

	if (IsObjectBootConditions())
	{
#ifdef _DEBUG
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"GetTrue");

		m_debugFontRender.SetPosition(DEBUG_FONT_POSITION);

		m_debugFontRender.SetText(wcsbuf);
#endif

		//����B�{�^���������ꂽ��
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//�̎���J�n����
			m_GetCOMSprite->CrystalCollectStart(this);
		}
	}
#ifdef _DEBUG
	else
	{
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"GetFalse");

		m_debugFontRender.SetPosition(DEBUG_FONT_POSITION);

		m_debugFontRender.SetText(wcsbuf);
	}
#endif 

}

void Crystal::CrystalCollected()
{
	m_isGetObject = true;

	switch (m_crystalColorState)
	{
	case Crystal::en_crystal_M:

		m_scoreUi->ScoreAdd(m_scoreM);

		break;
	case Crystal::en_crystal_R:

		m_scoreUi->ScoreAdd(m_scoreR);

		break;
	case Crystal::en_crystal_Y:

		m_scoreUi->ScoreAdd(m_scoreY);

		break;
	default:
		break;
	}

	m_managerCrystalPtr->ArrangementDataRefresh(this);
}
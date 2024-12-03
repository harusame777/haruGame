#include "stdafx.h"
#include "Crystal.h"
#include "Player.h"
#include "CrystalGetCommandSprite.h"
#include "ManagerCrystal.h"

//�����L���ɂ���ƃf�o�b�O���[�h�ɂȂ�
//#define DEBUG_MODE

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
	m_mainModel.Init("Assets/modelData/objects/crystal/crystal01_Model.tkm", nullptr, 0, enModelUpAxisZ, true);

	m_managerCrystalPtr = FindGO<ManagerCrystal>("CrystalMetaAI");

	//�V���h�E�}�b�v�ɕ`�悷��悤�ɂ���
	m_mainModel.SetShadowChasterFlag(true);

	//���W��ݒ�
	m_mainModel.SetPosition(m_position);
	//��]��ݒ�
	m_mainModel.SetRotation(m_rotation);
	//�g�嗦��ݒ�
	m_mainModel.SetScale(m_scale);
	//�����ݒ���m��
	m_mainModel.Update();

	//�v���C���[�̃C���X�^���X���擾����
	m_player = FindGO<Player>("player");

	//�N���X�^���̎擾�R�}���h�\���v���O�����̃C���X�^���X���擾����
	m_GetCOMSprite = FindGO<CrystalGetCommandSprite>("object");

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
	m_mainModel.SetPosition(m_position);
	//��]��ݒ�
	m_mainModel.SetRotation(m_rotation);
	//�`��X�V
	m_mainModel.Update();
}

//�����_�[�֐�
void Crystal::Render(RenderContext& rc)
{
	//�擾����Ă��Ȃ�������
	if (!m_isGetObject)
	{
		//�`�悷��
		m_mainModel.Draw(rc);
	}

#ifdef DEBUG_MODE
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

	if (IsInGetRange() && IsLookCrystal())
	{
#ifdef DEBUG_MODE
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"GetTrue");

		m_debugFontRender.SetText(wcsbuf);
#endif

		//����B�{�^���������ꂽ��
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//�̎���J�n����
			m_GetCOMSprite->CrystalCollectStart(this);
		}
	}
#ifdef DEBUG_MODE
	else
	{
		wchar_t wcsbuf[256];

		swprintf_s(wcsbuf, 256, L"GetFalse");

		m_debugFontRender.SetText(wcsbuf);
	}
#endif 

}

void Crystal::CrystalCollected()
{
	m_isGetObject = true;

	m_managerCrystalPtr->ArrangementDataRefresh(this);
}
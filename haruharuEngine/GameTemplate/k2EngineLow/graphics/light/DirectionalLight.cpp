#include "k2EngineLowPreCompile.h"
#include "DirectionalLight.h"

namespace nsK2EngineLow {

	//�R���X�g���N�^
	DirectionalLight::DirectionalLight()
	{
		if (m_directionLight == nullptr)
		{
			//�f�B���N�V�������C�g���쐬���A�|�C���^��o�^
			m_directionLight = g_sceneLight->NewDirectionLight();
		}
	}

	//�f�X�g���N�^
	DirectionalLight::~DirectionalLight()
	{
		g_sceneLight->DeleteDirectionLight(m_directionLight);
	}

	//���C�g�r���[�v���W�F�N�V�����̏���������
	void DirectionalLight::InitLigVP(const Vector3& basepoint)
	{
		m_directionLight->MakeLVP();

		//���̃��C�g�̃r���[�v���W�F�N�V�������쐬���邽�߂̃J����
		Camera m_lVPCam;

		m_lVPCam.SetAspectOneFlag(true);

		//��p��ݒ肷��
		m_lVPCam.SetViewAngle(Math::DegToRad(80.0f));

		// �J�����̒����_��ݒ�B���ꂪ���C�g���Ƃ炵�Ă���ꏊ
		m_lVPCam.SetTarget(basepoint);

		Vector3 ligDir = GetDirection();
		ligDir.y = 0.0f;
		ligDir *= -1.0f;

		ligDir *= 2000.0f;
		ligDir.y += 2000.0f;

		Vector3 ligPos;

		ligPos = ligDir + basepoint;

		m_lVPCam.SetPosition(ligPos);
		
		m_directionLight->SetLVP(m_lVPCam.GetViewProjectionMatrix());
	}

}
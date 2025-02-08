#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow {

	//�R���X�g���N�^
	SceneLight::SceneLight()
	{

	}

	//�f�X�g���N�^
	SceneLight::~SceneLight()
	{
		
	}

	void SceneLight::Init()
	{
		//���z��
		//m_light.m_directionalLight[0].m_color.x = 1.0f;
		//m_light.m_directionalLight[0].m_color.y = 1.0f;
		//m_light.m_directionalLight[0].m_color.z = 1.0f;

		//m_light.m_directionalLight[0].m_direction.x = 1.0f;
		//m_light.m_directionalLight[0].m_direction.y = -1.0f;
		//m_light.m_directionalLight[0].m_direction.z = -1.0f;
		//m_light.m_directionalLight[0].m_direction.Normalize();
		//m_light.m_directionalLight[0].m_castShadow = true;

		m_light.m_ambientLight.x = 0.3f;
		m_light.m_ambientLight.y = 0.3f;
		m_light.m_ambientLight.z = 0.3f;
		m_light.m_eyePos = g_camera3D->GetPosition();

		//�S�Ẵf�B���N�V�������C�g�𖢎g�p�ɂ���
		for (auto& pt : m_light.m_directionalLight)
		{
			pt.UnUse();
		}
		m_light.m_numDirectionLight = 0;

		//�S�Ẵ|�C���g���C�g�𖢎g�p�ɂ���
		for (auto& pt : m_light.m_pointLights) {
			pt.UnUse();
			pt.SetAffectPowParam(1.0f);
		}
		m_light.m_numPointLight = 0;

		//�S�ẴX�|�b�g���C�g�𖢎g�p�ɂ���
		for (auto& pt : m_light.m_spotLights){
			pt.UnUse();
		}
		m_light.m_numSpotLight = 0;
	}

	void SceneLight::Update()
	{
		//�J�����̊e����v�Z
		//�J�����̃r���[�v���W�F�N�V�������擾����
		const auto& lvpMatrix = g_sceneLight->m_light.m_directionalLight[0].GetLightVP();
		//�O�����Ɖ������͂��łɌv�Z�ς݂Ȃ̂ŁA��������������Ă���
		const auto& cameraForward = g_camera3D->GetForward();
		const auto& cameraRight = g_camera3D->GetForward();

		//�J�����̏�����͑O�����ƉE�����̊O�ςŋ��߂�
		Vector3 cameraUp;
		cameraUp.Cross(cameraForward, cameraRight);

		// nearDepth�̓G���A�̍ŏ��[�x�l��\��
		// ��ԋ߂��G���A�̍ŏ��[�x�l�̓J�����̃j�A�N���b�v
		float nearDepth = g_camera3D->GetNear();
		for (int areaNo = 0; areaNo < NUM_SHADOW_MAP; areaNo++)
		{
			// �G���A�̋ߕ��ʂ̒��S����̏�ʁA���ʂ܂ł̋��������߂�
			float nearY = tanf(g_camera3D->GetViewAngle() * 0.5f) * nearDepth;

			// �G���A�̋ߕ��ʂ̒��S����̉E�ʁA���ʂ܂ł̋��������߂�
			float nearX = nearY * g_camera3D->GetAspect();

			// �G���A�̉����ʂ̒��S����̏�ʁA���ʂ܂ł̋��������߂�
			float farY = tanf(g_camera3D->GetViewAngle() * 0.5f) * cascadeAreaTbl[areaNo];

			// �G���A�̉����ʂ̒��S����̉E�ʁA���ʂ܂ł̋��������߂�
			float farX = farY * g_camera3D->GetAspect();

			// �G���A�̋ߕ��ʂ̒��S���W�����߂�
			Vector3 nearPos = g_camera3D->GetPosition() + cameraForward * nearDepth;

			// �G���A�̉����ʂ̒��S���W�����߂�
			Vector3 farPos = g_camera3D->GetPosition() + cameraForward * cascadeAreaTbl[areaNo];

			//8���_�����߂�
			Vector3 vertex[8];

			// �ߕ��ʂ̉E��̒��_
			vertex[0] += nearPos + cameraUp * nearY + cameraRight * nearX;

			// �ߕ��ʂ̍���̒��_
			vertex[1] += nearPos + cameraUp * nearY + cameraRight * -nearX;

			// �ߕ��ʂ̉E���̒��_
			vertex[2] += nearPos + cameraUp * -nearY + cameraRight * nearX;

			// �ߕ��ʂ̍����̒��_
			vertex[3] += nearPos + cameraUp * -nearY + cameraRight * -nearX;

			// �����ʂ̉E��̒��_
			vertex[4] += farPos + cameraUp * farY + cameraRight * farX;

			// �����ʂ̍���̒��_
			vertex[5] += farPos + cameraUp * farY + cameraRight * -farX;

			// �����ʂ̉E���̒��_
			vertex[6] += farPos + cameraUp * -farY + cameraRight * farX;

			// �����ʂ̍����̒��_
			vertex[7] += farPos + cameraUp * -farY + cameraRight * -farX;

			//���_��ϊ����čő�l�A�ŏ��l�����߂�
			Vector3 vMax, vMin;
			vMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
			vMin = { FLT_MAX,  FLT_MAX,  FLT_MAX };
			for (auto& v : vertex)
			{
				lvpMatrix.Apply(v);
				vMax.Max(v);
				vMin.Min(v);
			}

			//�N���b�v�s������߂�
			float xScale = 2.0f / (vMax.x - vMin.x);
			float yScale = 2.0f / (vMax.y - vMin.y);
			float xOffset = (vMax.x + vMin.x) * -0.5f * xScale;
			float yOffset = (vMax.y + vMin.y) * -0.5f * yScale;
			Matrix clopMatrix;
			clopMatrix.m[0][0] = xScale;
			clopMatrix.m[1][1] = yScale;
			clopMatrix.m[3][0] = xOffset;
			clopMatrix.m[3][1] = yOffset;

			
		}

		m_light.m_numDirectionLight = 0;
		for (int i = 0; i < MAX_DIRECTIONAL_LIGHT; i++)
		{
			if (m_light.m_directionalLight[i].GetUse())
			{
				m_light.m_numDirectionLight++;
			}
		}

		m_light.m_numPointLight = 0;
		for (int i = 0; i < MAX_POINT_LIGHT; i++)
		{
			if (m_light.m_pointLights[i].GetUse())
			{
				m_light.m_numPointLight++;
			}
		}

		m_light.m_numSpotLight = 0;
		for (int i = 0; i < MAX_SPOT_LIGHT; i++)
		{
			if (m_light.m_spotLights[i].GetUse())
			{
				m_light.m_numSpotLight++;
			}
		}
	}

	//�V�K�f�B���N�V�������C�g���쐬
	SDirectionLight* SceneLight::NewDirectionLight()
	{
		if (m_light.m_numDirectionLight)
		{
			return nullptr;
		}

		for (int i = 0; i < MAX_DIRECTIONAL_LIGHT; i++)
		{
			if (m_light.m_directionalLight[i].m_isUse != true)
			{
				m_light.m_directionalLight[i].Use();
				return &m_light.m_directionalLight[i];
			}
		}
	}

	void SceneLight::DeleteDirectionLight(SDirectionLight* directionlight)
	{
		//�|�C���^�ɃA�h���X�����������ĂȂ������牽�������ɕԂ�
		if (directionlight == nullptr)
		{
			return;
		}
		//������V�[�����C�g���Ǘ����Ă��Ȃ��f�B���N�V�������C�g�ɑ΂��č폜���������s����ƊǗ����o�O��(���Ɏg�p���̃��C�g�̐�)�̂�
		//�{���ɍ폜���������Ă������m�F���� 
		//�����Ă����|�C���^�ɓ����Ă���A�h���X�ƁA�z��̊e�v�f�̃A�h���X���Ƃ炵���킹�āA
		//�A�h���X���������̂���������A�폜���������s����
		for (int i = 0; i < MAX_DIRECTIONAL_LIGHT; i++)
		{
			if (directionlight == &m_light.m_directionalLight[i])
			{
				//������
				directionlight->UnUse();
				directionlight->SetColor(0.0f, 0.0f, 0.0f);
				directionlight->SetDirection(0.0f, 0.0f, 0.0f);
			}
		}
	}

	//�V�K�|�C���g���C�g���쐬
	SPointLight* SceneLight::NewPointLight()
	{
		if (m_light.m_numPointLight >= MAX_POINT_LIGHT)
		{
			return nullptr;
		}

		for (int i = 0; i < MAX_POINT_LIGHT; i++)
		{
			if (m_light.m_pointLights[i].GetUse() != true)
			{
				m_light.m_pointLights[i].Use();
				return &m_light.m_pointLights[i];
			}
		}
	}

	//�|�C���g���C�g���폜
	void SceneLight::DeletePointLight(SPointLight* m_pointlight)
	{
		//�|�C���^�ɃA�h���X�������ĂȂ������牽�������Ԃ�
		if (m_pointlight == nullptr)
		{
			return;
		}
		//������V�[�����C�g���Ǘ����Ă��Ȃ��|�C���g���C�g�ɑ΂��č폜���������s����ƊǗ����o�O��(���Ɏg�p���̃��C�g�̐�)�̂�
		//�{���ɍ폜���������Ă������m�F���� 
		//�����Ă����|�C���^�ɓ����Ă���A�h���X�ƁA�z��̊e�v�f�̃A�h���X���Ƃ炵���킹�āA
		//�A�h���X���������̂���������A�폜���������s����
		for (int i = 0; i < MAX_POINT_LIGHT; i++)
		{

			if (m_pointlight == &m_light.m_pointLights[i])
			{
				//������
				m_pointlight->UnUse();
				m_pointlight->SetColor(0.0f, 0.0f, 0.0f);
				m_pointlight->SetPosition(0.0f, 0.0f, 0.0f);
				m_pointlight->SetRange(0.0f);
				m_pointlight->SetAffectPowParam(1.0f);
			}
		}
	}

	//�V�K�X�|�b�g���C�g���쐬
	SSpotLight* SceneLight::NewSpotLight()
	{
		if (m_light.m_numSpotLight >= MAX_SPOT_LIGHT)
		{
			return nullptr;
		}

		for (int i = 0; i < MAX_SPOT_LIGHT; i++)
		{
			if (m_light.m_spotLights[i].GetUse() != true)
			{
				m_light.m_spotLights[i].Use();
				return &m_light.m_spotLights[i];
			}
		}
	}

	//�X�|�b�g���C�g���폜
	void SceneLight::DeleteSpotLight(SSpotLight* spotlight)
	{
		if (spotlight == nullptr)
		{
			return;
		}

		for (int i = 0; i < MAX_SPOT_LIGHT; i++)
		{

			if (spotlight == &m_light.m_spotLights[i])
			{
				spotlight->UnUse();
				spotlight->SetColor(0.0f, 0.0f, 0.0f);
				spotlight->SetPosition(0.0f, 0.0f, 0.0f);
				spotlight->SetRange(0.0f);
				spotlight->SetRangeAffectPowParam(1.0f);
				spotlight->SetAngleAffectPowParam(1.0f);
			}
		}
	}
}
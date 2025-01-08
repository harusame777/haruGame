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

			m_vprCam.SetAspectOneFlag(true);

			m_directionLight->SetLightVP(m_vprCam.GetViewProjectionMatrix());
		}
	}

	//�f�X�g���N�^
	DirectionalLight::~DirectionalLight()
	{
		g_sceneLight->DeleteDirectionLight(m_directionLight);
	}

}
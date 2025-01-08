#include "k2EngineLowPreCompile.h"
#include "DirectionalLight.h"

namespace nsK2EngineLow {

	//コンストラクタ
	DirectionalLight::DirectionalLight()
	{
		if (m_directionLight == nullptr)
		{
			//ディレクションライトを作成し、ポインタを登録
			m_directionLight = g_sceneLight->NewDirectionLight();

			m_vprCam.SetAspectOneFlag(true);

			m_directionLight->SetLightVP(m_vprCam.GetViewProjectionMatrix());
		}
	}

	//デストラクタ
	DirectionalLight::~DirectionalLight()
	{
		g_sceneLight->DeleteDirectionLight(m_directionLight);
	}

}
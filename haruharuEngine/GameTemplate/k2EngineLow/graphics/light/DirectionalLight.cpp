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
		}
	}

	//デストラクタ
	DirectionalLight::~DirectionalLight()
	{
		g_sceneLight->DeleteDirectionLight(m_directionLight);
	}

	//ライトビュープロジェクションの初期化処理
	void DirectionalLight::InitLigVP(const Vector3& basepoint)
	{
		m_directionLight->MakeLVP();

		//このライトのビュープロジェクションを作成するためのカメラ
		Camera m_lVPCam;

		m_lVPCam.SetAspectOneFlag(true);

		//画角を設定する
		m_lVPCam.SetViewAngle(Math::DegToRad(80.0f));

		// カメラの注視点を設定。これがライトが照らしている場所
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
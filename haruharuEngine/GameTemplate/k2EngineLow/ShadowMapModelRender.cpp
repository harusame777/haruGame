#include "k2EngineLowPreCompile.h"
#include "ShadowMapModelRender.h"

namespace nsK2EngineLow {

	//コンストラクタ
	ShadowMapModelRender::ShadowMapModelRender()
	{

	}

	//デストラクタ
	ShadowMapModelRender::~ShadowMapModelRender()
	{
		
	}

	void ShadowMapModelRender::InitShadowMapModelRender(
		const char* tkmfilePath,
		EnModelUpAxis enModelUpAxis
	)
	{
		ModelInitData initData;
		initData.m_tkmFilePath = tkmfilePath;
		initData.m_modelUpAxis = enModelUpAxis;

		if (m_animationClips != nullptr)
		{
			//スケルトン指定
			initData.m_skeleton = &m_skeleton;
		}

		initData.m_fxFilePath = "Assets/shader/haruharuDrawDeaphShadowMap.fx";

		ShadowMapParam shadowMapParam;
		shadowMapParam.mLVP = m_light.m_directionalLight[0].GetLightVP();
		shadowMapParam.ligPos = m_light.m_directionalLight[0].GetVPCamPosition();

		initData.m_expandConstantBuffer = (void*)&shadowMapParam;
		initData.m_expandConstantBufferSize = sizeof(shadowMapParam);

		initData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32_FLOAT;/*デプスシャドウ用の設定*/

		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する
		initData.m_vsEntryPointFunc = "VSMain";
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定する
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		m_shadowMapModel.Init(initData);

		m_shadowMapModel.UpdateWorldMatrix(
			m_position,
			m_rotation,
			m_scale
		);
	}

}
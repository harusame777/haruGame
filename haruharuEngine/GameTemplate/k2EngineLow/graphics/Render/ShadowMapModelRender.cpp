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

	const Model& ShadowMapModelRender::InitShadowMapModelRender(
		const char* tkmfilePath,
		EnModelUpAxis enModelUpAxis,
		AnimationClip* animationClips,
		const Light& ligPtr 
	)
	{
		//スケルトンのデータを読み込み。
		std::string skeletonFilePath = tkmfilePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());

		ModelInitData initData;
		initData.m_tkmFilePath = tkmfilePath;
		initData.m_modelUpAxis = enModelUpAxis;

		if (animationClips != nullptr)
		{
			//スケルトン指定
			initData.m_skeleton = &m_skeleton;
		}

		initData.m_fxFilePath = "Assets/shader/haruharuDrawShadowMap.fx";

		ShadowMapParam shadowMapParam;
		shadowMapParam.mLVP = ligPtr.m_directionalLight[0].GetLightVP();
		shadowMapParam.ligPos = ligPtr.m_directionalLight[0].GetVPCamPosition();

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

		return m_shadowMapModel;
	}

}
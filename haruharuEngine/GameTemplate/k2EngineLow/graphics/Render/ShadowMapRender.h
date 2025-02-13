#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {

	class IRenderer;

	enum SHADOW_MAP
	{
		NUM_SHADOW_MAP = 3
	};

	class ShadowMapRender : Noncopyable
	{
	public:

		//シャドウマップ初期化処理
		void Init();

		//描画処理
		void RenderShadowMap(
			RenderContext& rc,
			std::vector<IRenderer*>& renderObjects
		);

		RenderTarget* GetShadowMapRenderTarget(const int listNum)
		{
			return &m_shadowMap[listNum];
		}

		Texture& GetShadowMapBokeTexture(const int listNum)
		{
			return m_shadowMapModelGaussianBlur[listNum].GetBokeTexture();
		}

		void ShadouMapBlurExecute(RenderContext& rc,const int listNum)
		{
			m_shadowMapModelGaussianBlur[listNum].ExecuteOnGPU(rc, 5.0f);
		}

	protected:
		//レンダリングターゲット(影)
		RenderTarget m_shadowMap[NUM_SHADOW_MAP];
		//ガウシアンブラー
		GaussianBlur m_shadowMapModelGaussianBlur[NUM_SHADOW_MAP];
		//分割エリア最大深度値
		float cascadeAreaTbl[NUM_SHADOW_MAP] = {
			500,
			2000,
			g_camera3D->GetFar(),
		};
	};
}


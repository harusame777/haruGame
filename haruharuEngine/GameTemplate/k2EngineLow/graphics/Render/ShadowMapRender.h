#pragma once

namespace nsK2EngineLow {
	class IRenderer;

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

		RenderTarget* GetShadowMapRenderTarget()
		{
			return &m_shadowMap;
		}

	private:
		//レンダリングターゲット(影)
		RenderTarget m_shadowMap;
	};
}


#pragma once

namespace nsK2EngineLow {
	class GaussianBlur;

	class LuminnceRender
	{
	public:

		//初期化処理
		void Init(RenderTarget* mainRenderTarget);

		//輝度抽出
		void LuminnceExtraction(RenderContext& rc);

	private:
		//輝度抽出用のレンダリングターゲット
		RenderTarget m_luminnceRenderTarget;
		//輝度抽出用のスプライト
		Sprite m_luminnceSprite;
		//ガウシアンブラー
		GaussianBlur m_gaussianBlur;
	};

}


#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
	class LuminnceRender
	{
	public:

		//初期化処理
		void Init(RenderTarget* mainRenderTarget);

		//輝度抽出
		void LuminnceExtraction(RenderContext& rc);

		//最終合成のスプライトを描画
		void AddSynthesisSpriteDraw(RenderContext& rc)
		{
			m_luminnceSprite.Draw(rc);
		}

	private:
		//輝度抽出用のレンダリングターゲット
		RenderTarget m_luminnceRenderTarget;
		//輝度抽出用のスプライト
		Sprite m_luminnceSprite;
		//加算合成スプライト
		Sprite m_AddSynthesisSprite;
		//ガウシアンブラー
		GaussianBlur m_gaussianBlur;
	};
}


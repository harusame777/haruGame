#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
	class IRenderer;

	class DepthMapRender : Noncopyable
	{
	public:

		//Z値取得用レンダリングターゲット初期化関数
		void Init(RenderTarget& rt);
		//深度抽出
		void DepthExtraction(
			RenderContext& rc,
			std::vector<IRenderer*>& renderObjects
		);
		//合成描画
		void AddSynthesisSpriteDraw(RenderContext& rc)
		{
			m_depthCombineBokeImageSprite.Draw(rc);
		}
	protected:
		enum {
			//マルチレンダリングターゲット最大数
			MAX_MRT = 2,
		};
		//レンダリングターゲット(影)
		RenderTarget m_depthMap;
		//マルチレンダリングターゲット
		RenderTarget* m_depthMapMRT[MAX_MRT];
		//ガウシアンブラー
		GaussianBlur m_depthMapModelGaussianBlur;
		//ボケ画像合成用スプライト
		Sprite m_depthCombineBokeImageSprite;
	};

}

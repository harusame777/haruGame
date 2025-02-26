#include "k2EngineLowPreCompile.h"
#include "DepthMapRender.h"

namespace nsK2EngineLow {

	void DepthMapRender::Init(RenderTarget& rt)
	{
		//フレームバッファーの横幅、高さを取得
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();

		//シーンのカメラ空間でのZ値を書き込むレンダリングターゲットを作成
		m_depthMap.Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);

		m_depthMapModelGaussianBlur.Init(
			&rt.GetRenderTargetTexture()
		);

		//ボケ画像合成用のスプライトを初期化する
		SpriteInitData combineBokeImageSpriteInitData;

		//使用するテクスチャは二枚
		//こっちはガウシアンブラー
		combineBokeImageSpriteInitData.m_textures[0] 
			= &m_depthMapModelGaussianBlur.GetBokeTexture();
		//こっちはデプス
		combineBokeImageSpriteInitData.m_textures[1]
			= &m_depthMap.GetRenderTargetTexture();

		//高さ幅指定
		combineBokeImageSpriteInitData.m_width = frameBuffer_w;
		combineBokeImageSpriteInitData.m_height = frameBuffer_h;

		//合成用のシェーダーを指定する
		combineBokeImageSpriteInitData.m_fxFilePath 
			= "Assets/shader/haruharuDepthMapPostEffect.fx";
		combineBokeImageSpriteInitData.m_colorBufferFormat[0] 
			= DXGI_FORMAT_R32G32B32A32_FLOAT;

		//距離を利用してボケ画像をアルファブレンディングするので、半透明合成モードにする
		combineBokeImageSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

		//初期化オブジェクトを利用してスプライトを初期化する
		m_depthCombineBokeImageSprite.Init(combineBokeImageSpriteInitData);

		//マルチレンダリングターゲット初期化
		m_depthMapMRT[0] = &rt;
		m_depthMapMRT[1] = &m_depthMap;
	} 

	//輝度抽出
	void DepthMapRender::DepthExtraction(RenderContext& rc, std::vector<IRenderer*>& renderObjects)
	{

		//使用できるまで待ち
		rc.WaitUntilToPossibleSetRenderTargets(MAX_MRT, m_depthMapMRT);

		//レンダリングターゲットを設定
		rc.SetRenderTargetsAndViewport(MAX_MRT, m_depthMapMRT);

		//レンダリングターゲットをクリア
		rc.ClearRenderTargetViews(MAX_MRT, m_depthMapMRT);

		for (auto& renderObj : renderObjects)
		{
			renderObj->OnRenderModel(rc);
		}

		rc.WaitUntilFinishDrawingToRenderTargets(MAX_MRT, m_depthMapMRT);

		m_depthMapModelGaussianBlur.ExecuteOnGPU(rc, 5);
	}

}
#include "k2EngineLowPreCompile.h"
#include "LuminnceRender.h"
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {

	//初期化処理
	void LuminnceRender::Init(RenderTarget* mainRenderTarget)
	{
		//フレームバッファーの横幅、高さを取得
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();

		//輝度抽出用のレンダリングターゲットを作成
		m_luminnceRenderTarget.Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//輝度抽出用のスプライトを初期化
		//初期化情報作成
		SpriteInitData luminnceSpriteInitData;

		//輝度抽出用のシェーダーのファイルパスを指定する
		luminnceSpriteInitData.m_fxFilePath = "";

		//頂点シェーダーのエントリーポイントを指定
		luminnceSpriteInitData.m_vsEntryPointFunc = "";

		//ピクセルシェーダーのエントリーポイントを指定
		luminnceSpriteInitData.m_psEntryPoinFunc = "";

		//スプライトの高さ幅と高さを設定
		luminnceSpriteInitData.m_width = frameBuffer_w;
		luminnceSpriteInitData.m_width = frameBuffer_h;

		//テクスチャはメインレンダリングターゲットのバッファー
		luminnceSpriteInitData.m_textures[0] = &mainRenderTarget->GetRenderTargetTexture();

		//書き込むレンダリングターゲットのフォーマットを指定する
		luminnceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//ガウシアンブラーを初期化
		m_gaussianBlur.Init(&m_luminnceRenderTarget.GetRenderTargetTexture());
	}

	//輝度抽出
	void LuminnceRender::LuminnceExtraction(RenderContext& rc)
	{
		//輝度抽出用のレンダリングターゲットに変更
		rc.WaitUntilToPossibleSetRenderTarget(m_luminnceRenderTarget);

		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_luminnceRenderTarget);

		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_luminnceRenderTarget);

		//輝度抽出を行う
		m_luminnceSprite.Draw(rc);

		//レンダリングターゲットの書き込み終了待ち
		rc.WaitUntilToPossibleSetRenderTarget(m_luminnceRenderTarget);

	}
}
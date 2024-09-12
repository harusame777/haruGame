#include "k2EngineLowPreCompile.h"
#include "ShadowMapRender.h"

namespace nsK2EngineLow {

	//初期化処理
	void ShadowMapRender::Init()
	{
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };

		//シャドウマップ用のレンダリングターゲットを作成
		m_shadowMap.Create(
			1024,
			1024,
			1,
			1,
			//DXGI_FORMAT_R32_FLOAT,デプスシャドウ用の設定
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	//シャドウマップ描画
	void ShadowMapRender::RenderShadowMap(
		RenderContext& renderContext,
		std::vector<IRenderer*>& renderObjects
	)
	{
		//シャドウマップ用レンダリングターゲットが使用可能になるまで待機
		renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		//レンダリングターゲットをシャドウマップに変更
		renderContext.SetRenderTargetAndViewport(m_shadowMap);
		//レンダリングターゲットをクリア
		renderContext.ClearRenderTargetView(m_shadowMap);

		Camera lightCamera;

		lightCamera.SetAspectOneFlag(true);

		lightCamera.SetViewAngle(Math::DegToRad(80.0f));

		//カメラの位置を設定。(ライトから考える必要があるのでライトと同じ位置)
		lightCamera.SetPosition(-2000, 2000, 2000);

		//カメラの注視点を設定。(光の方向)
		lightCamera.SetTarget(0.0f, 0.0f, 0.0f);

		// 上方向を設定。今回はライトが真下を向いているので、X方向を上にしている
		//lightCamera.SetUp(1, 0, 0);

		//ライトビュープロジェクション
		lightCamera.Update();

		for (auto& renderObj : renderObjects)
		{
			renderObj->OnRenderShadowMap(renderContext, lightCamera.GetViewProjectionMatrix());
		}

		renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
	}
}
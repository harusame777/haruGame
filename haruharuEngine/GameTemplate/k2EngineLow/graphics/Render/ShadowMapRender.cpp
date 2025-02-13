#include "k2EngineLowPreCompile.h"
#include "ShadowMapRender.h"
#include "graphics/light/SceneLight.h"

namespace nsK2EngineLow {


	//初期化処理
	void ShadowMapRender::Init()
	{
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };


		//シャドウマップ用のレンダリングターゲットを作成
		//近影用のシャドウマップ
		m_shadowMap[0].Create(
			2048,
			2048,
			1,
			1,
			//DXGI_FORMAT_R32_FLOAT,デプスシャドウ用の設定
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);

		//中影用
		m_shadowMap[1].Create(
			1024,
			1024,
			1,
			1,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);

		//遠影用
		m_shadowMap[2].Create(
			512,
			512,
			1,
			1,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
		
		for (int No = 0; No < NUM_SHADOW_MAP; No++)
		{
			m_shadowMapModelGaussianBlur[No].Init(
				&m_shadowMap[No].GetRenderTargetTexture()
			);
		}

	}

	//シャドウマップ描画
	void ShadowMapRender::RenderShadowMap(
		RenderContext& renderContext,
		std::vector<IRenderer*>& renderObjects
	)
	{
		//カメラの各種情報計算
		//カメラのビュープロジェクションを取得する
		const auto& lvpMatrix = g_sceneLight->m_light.m_directionalLight[0].GetLightVP();
		//前方向と横方向はすでに計算済みなので、それを引っ張ってくる
		const auto& cameraForward = g_camera3D->GetForward();
		const auto& cameraRight = g_camera3D->GetForward();

		//カメラの上方向は前方向と右方向の外積で求める
		Vector3 cameraUp;
		cameraUp.Cross(cameraForward, cameraRight);

		// nearDepthはエリアの最小深度値を表す
		// 一番近いエリアの最小深度値はカメラのニアクリップ
		float nearDepth = g_camera3D->GetNear();
		for (int areaNo = 0; areaNo < NUM_SHADOW_MAP; areaNo++)
		{
			// エリアの近平面の中心からの上面、下面までの距離を求める
			float nearY = tanf(g_camera3D->GetViewAngle() * 0.5f) * nearDepth;

			// エリアの近平面の中心からの右面、左面までの距離を求める
			float nearX = nearY * g_camera3D->GetAspect();

			// エリアの遠平面の中心からの上面、下面までの距離を求める
			float farY = tanf(g_camera3D->GetViewAngle() * 0.5f) * cascadeAreaTbl[areaNo];

			// エリアの遠平面の中心からの右面、左面までの距離を求める
			float farX = farY * g_camera3D->GetAspect();

			// エリアの近平面の中心座標を求める
			Vector3 nearPos = g_camera3D->GetPosition() + cameraForward * nearDepth;

			// エリアの遠平面の中心座標を求める
			Vector3 farPos = g_camera3D->GetPosition() + cameraForward * cascadeAreaTbl[areaNo];

			//8頂点を求める
			Vector3 vertex[8];

			// 近平面の右上の頂点
			vertex[0] += nearPos + cameraUp * nearY + cameraRight * nearX;

			// 近平面の左上の頂点
			vertex[1] += nearPos + cameraUp * nearY + cameraRight * -nearX;

			// 近平面の右下の頂点
			vertex[2] += nearPos + cameraUp * -nearY + cameraRight * nearX;

			// 近平面の左下の頂点
			vertex[3] += nearPos + cameraUp * -nearY + cameraRight * -nearX;

			// 遠平面の右上の頂点
			vertex[4] += farPos + cameraUp * farY + cameraRight * farX;

			// 遠平面の左上の頂点
			vertex[5] += farPos + cameraUp * farY + cameraRight * -farX;

			// 遠平面の右下の頂点
			vertex[6] += farPos + cameraUp * -farY + cameraRight * farX;

			// 遠平面の左下の頂点
			vertex[7] += farPos + cameraUp * -farY + cameraRight * -farX;

			//頂点を変換して最大値、最小値を求める
			Vector3 vMax, vMin;
			vMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
			vMin = { FLT_MAX,  FLT_MAX,  FLT_MAX };
			for (auto& v : vertex)
			{
				lvpMatrix.Apply(v);
				vMax.Max(v);
				vMin.Min(v);
			}

			//クロップ行列を求める
			float xScale = 2.0f / (vMax.x - vMin.x);
			float yScale = 2.0f / (vMax.y - vMin.y);
			float xOffset = (vMax.x + vMin.x) * -0.5f * xScale;
			float yOffset = (vMax.y + vMin.y) * -0.5f * yScale;
			Matrix clopMatrix;
			clopMatrix.m[0][0] = xScale;
			clopMatrix.m[1][1] = yScale;
			clopMatrix.m[3][0] = xOffset;
			clopMatrix.m[3][1] = yOffset;

			//ライトビュープロジェクション行列にクロップ行列を乗算する
			g_sceneLight->m_light.m_lvpcMatrix[areaNo] = lvpMatrix * clopMatrix;

			//シャドウマップ用レンダリングターゲットが使用可能になるまで待機
			renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap[areaNo]);
			//レンダリングターゲットをシャドウマップに変更
			renderContext.SetRenderTargetAndViewport(m_shadowMap[areaNo]);
			//レンダリングターゲットをクリア
			renderContext.ClearRenderTargetView(m_shadowMap[areaNo]);

			//影モデル描画
			for (auto& renderObj : renderObjects)
			{
				renderObj->OnRenderShadowMap(renderContext);
			}

			//書き込み終了待ち
			renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap[areaNo]);
			//シャドウマップにブラーを入れる
			ShadouMapBlurExecute(renderContext,areaNo);

			//次のエリアの近平面までの距離を代入する
			nearDepth = cascadeAreaTbl[areaNo];
		}


		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
	}
}
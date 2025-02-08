#pragma once
#include "graphics/Render/ShadowMapRender.h"
#include "graphics/Render/GBufferRender.h"
#include "graphics/Render/LuminnceRender.h"

namespace nsK2EngineLow {
	class RenderingEngine : Noncopyable //コピー不可のクラス
	{
	public:

		//コンストラクタ
		RenderingEngine();
		//デストラクタ
		~RenderingEngine();

		void Init();

		//描画オブジェクトを追加
		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}

		//3Dモデルの描画
		void Render3DModel(RenderContext& rc);

		//2D描画
		void Render2DSprite(RenderContext& rc);

		//実行
		void Execute(RenderContext& rc);

		Texture& GetShadowMapRenderBokeTexture(const int listNum)
		{
			return m_shadowMapRender.GetShadowMapBokeTexture(listNum);
		}

		RenderTarget* GetShadowMapRenderTarget(const int listNum)
		{
			return m_shadowMapRender.GetShadowMapRenderTarget(listNum);
		}

	private:
		//メインレンダリングターゲット
		RenderTarget mainRenderTargert;
		//描画オブジェクトのリスト
		std::vector<IRenderer*> m_renderObjects;
		//シャドウマップレンダー
		ShadowMapRender m_shadowMapRender;
		//GBufferレンダー
		GBufferRender m_gBufferRender;
		//輝度抽出レンダー
		LuminnceRender m_luminnceRender;
		//テクスチャを張り付けるためのスプライト
		Sprite m_copyToFrameBufferSprite;
	};
}


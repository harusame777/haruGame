#pragma once
#include "graphics/Render/ModelRender.h"
#include "graphics/Render/ShadowMapRender.h"


namespace nsK2EngineLow {

	class ShadowMapModelRender :
		public ModelRender,
		public ShadowMapRender,
		Noncopyable
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		ShadowMapModelRender();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~ShadowMapModelRender();
		/// <summary>
		/// シャドウマップのモデルを初期化
		/// </summary>
		void InitShadowMapModelRender(
			const char* tkmfilePath,
			EnModelUpAxis enModelUpAxis
		);
	private:
		/// <summary>
		/// シャドウマップのパラメーター構造体
		/// </summary>
		struct ShadowMapParam
		{
			Matrix mLVP;
			Vector3 ligPos;
		};
	};

}
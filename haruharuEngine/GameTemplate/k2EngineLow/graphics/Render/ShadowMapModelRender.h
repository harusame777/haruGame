#pragma once
#include "graphics/Render/ShadowMapRender.h"

namespace nsK2EngineLow {

	class ShadowMapModelRender :
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
		const Model& InitShadowMapModelRender(
			const char* tkmfilePath,
			EnModelUpAxis enModelUpAxis,
			AnimationClip* animationClips,
			const Light& ligPtr
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
		/// <summary>
		/// スケルトン
		/// </summary>
		Skeleton m_skeleton;
		/// <summary>
		/// シャドウマップのモデル
		/// </summary>
		Model m_shadowMapModel;
		/// <summary>
		/// ポジション
		/// </summary>
		Vector3 m_position = Vector3::Zero;
		/// <summary>
		/// 回転
		/// </summary>
		Quaternion m_rotation = Quaternion::Identity;
		/// <summary>
		/// 拡大率
		/// </summary>
		Vector3 m_scale = Vector3::One;
	};
}
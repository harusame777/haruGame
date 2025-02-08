#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {

	namespace {

		static const int NUM_SHADOW_MAP = 3;

	}

	class IRenderer;

	class ShadowMapRender : Noncopyable
	{
	public:

		//�V���h�E�}�b�v����������
		void Init();

		//�`�揈��
		void RenderShadowMap(
			RenderContext& rc,
			std::vector<IRenderer*>& renderObjects
		);

		RenderTarget* GetShadowMapRenderTarget(const int listNum)
		{
			return &m_shadowMap[listNum];
		}

		Texture& GetShadowMapBokeTexture(const int listNum)
		{
			return m_shadowMapModelGaussianBlur[listNum].GetBokeTexture();
		}

		void ShadouMapBlurExecute(RenderContext& rc)
		{
			m_shadowMapModelGaussianBlur.ExecuteOnGPU(rc, 5.0f);
		}

	protected:
		//�����_�����O�^�[�Q�b�g(�e)
		RenderTarget m_shadowMap[NUM_SHADOW_MAP];
		//�K�E�V�A���u���[
		GaussianBlur m_shadowMapModelGaussianBlur[NUM_SHADOW_MAP];
		//�����G���A�ő�[�x�l
		float cascadeAreaTbl[NUM_SHADOW_MAP] = {
			500,
			2000,
			g_camera3D->GetFar(),
		};
	};
}


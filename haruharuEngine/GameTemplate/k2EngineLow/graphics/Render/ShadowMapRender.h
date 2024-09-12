#pragma once

namespace nsK2EngineLow {
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

		RenderTarget* GetShadowMapRenderTarget()
		{
			return &m_shadowMap;
		}

	private:
		//�����_�����O�^�[�Q�b�g(�e)
		RenderTarget m_shadowMap;
	};
}


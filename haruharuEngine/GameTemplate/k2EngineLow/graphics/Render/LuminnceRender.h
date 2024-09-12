#pragma once

namespace nsK2EngineLow {
	class GaussianBlur;

	class LuminnceRender
	{
	public:

		//����������
		void Init(RenderTarget* mainRenderTarget);

		//�P�x���o
		void LuminnceExtraction(RenderContext& rc);

	private:
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g
		RenderTarget m_luminnceRenderTarget;
		//�P�x���o�p�̃X�v���C�g
		Sprite m_luminnceSprite;
		//�K�E�V�A���u���[
		GaussianBlur m_gaussianBlur;
	};

}


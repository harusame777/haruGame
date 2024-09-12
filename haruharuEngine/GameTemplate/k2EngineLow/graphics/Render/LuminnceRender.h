#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
	class LuminnceRender
	{
	public:

		//����������
		void Init(RenderTarget* mainRenderTarget);

		//�P�x���o
		void LuminnceExtraction(RenderContext& rc);

		//�ŏI�����̃X�v���C�g��`��
		void AddSynthesisSpriteDraw(RenderContext& rc)
		{
			m_luminnceSprite.Draw(rc);
		}

	private:
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g
		RenderTarget m_luminnceRenderTarget;
		//�P�x���o�p�̃X�v���C�g
		Sprite m_luminnceSprite;
		//���Z�����X�v���C�g
		Sprite m_AddSynthesisSprite;
		//�K�E�V�A���u���[
		GaussianBlur m_gaussianBlur;
	};
}


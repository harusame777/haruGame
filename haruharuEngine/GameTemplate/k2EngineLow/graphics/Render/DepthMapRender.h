#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
	class IRenderer;

	class DepthMapRender : Noncopyable
	{
	public:

		//Z�l�擾�p�����_�����O�^�[�Q�b�g�������֐�
		void Init(RenderTarget& rt);
		//�[�x���o
		void DepthExtraction(
			RenderContext& rc,
			std::vector<IRenderer*>& renderObjects
		);
		//�����`��
		void AddSynthesisSpriteDraw(RenderContext& rc)
		{
			m_depthCombineBokeImageSprite.Draw(rc);
		}
	protected:
		enum {
			//�}���`�����_�����O�^�[�Q�b�g�ő吔
			MAX_MRT = 2,
		};
		//�����_�����O�^�[�Q�b�g(�e)
		RenderTarget m_depthMap;
		//�}���`�����_�����O�^�[�Q�b�g
		RenderTarget* m_depthMapMRT[MAX_MRT];
		//�K�E�V�A���u���[
		GaussianBlur m_depthMapModelGaussianBlur;
		//�{�P�摜�����p�X�v���C�g
		Sprite m_depthCombineBokeImageSprite;
	};

}

#include "k2EngineLowPreCompile.h"
#include "LuminnceRender.h"
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {

	//����������
	void LuminnceRender::Init(RenderTarget* mainRenderTarget)
	{
		//�t���[���o�b�t�@�[�̉����A�������擾
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();

		//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬
		m_luminnceRenderTarget.Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//�P�x���o�p�̃X�v���C�g��������
		//���������쐬
		SpriteInitData luminnceSpriteInitData;

		//�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		luminnceSpriteInitData.m_fxFilePath = "";

		//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��
		luminnceSpriteInitData.m_vsEntryPointFunc = "";

		//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w��
		luminnceSpriteInitData.m_psEntryPoinFunc = "";

		//�X�v���C�g�̍������ƍ�����ݒ�
		luminnceSpriteInitData.m_width = frameBuffer_w;
		luminnceSpriteInitData.m_width = frameBuffer_h;

		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃o�b�t�@�[
		luminnceSpriteInitData.m_textures[0] = &mainRenderTarget->GetRenderTargetTexture();

		//�������ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
		luminnceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//�K�E�V�A���u���[��������
		m_gaussianBlur.Init(&m_luminnceRenderTarget.GetRenderTargetTexture());
	}

	//�P�x���o
	void LuminnceRender::LuminnceExtraction(RenderContext& rc)
	{
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
		rc.WaitUntilToPossibleSetRenderTarget(m_luminnceRenderTarget);

		//�����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(m_luminnceRenderTarget);

		//�����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(m_luminnceRenderTarget);

		//�P�x���o���s��
		m_luminnceSprite.Draw(rc);

		//�����_�����O�^�[�Q�b�g�̏������ݏI���҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_luminnceRenderTarget);

	}
}